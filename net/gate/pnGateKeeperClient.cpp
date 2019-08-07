/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pnGateKeeperClient.h"
#include "GateKeeperMessages.h"
#include "Stream/hsRAMStream.h"
#include "Debug/plDebug.h"
#include "crypt/pnBigInteger.h"
#include "crypt/pnSha1.h"
#include <cstring>

/* Dispatch */
bool pnGateKeeperClient::Dispatch::dispatch(pnSocket* sock)
{
    uint16_t msgId;
    sock->recv(&msgId, sizeof(uint16_t));
    const pnNetMsg* msgDesc = GET_GateKeeper2Cli(msgId);
    if (msgDesc == nullptr) {
        plDebug::Error("Got invalid message ID ({})", msgId);
        return false;
    }

    msgparm_t* msgbuf = sock->recvMsg(msgDesc);
    switch (msgId) {
    case kGateKeeper2Cli_PingReply:
        fReceiver->onPingReply(msgbuf[1].fUint, msgbuf[0].fUint);
        if (msgbuf[2].fUint != 0)
            plDebug::Debug("Got non-zero payload");
        break;
    case kGateKeeper2Cli_FileSrvIpAddressReply:
        fReceiver->onFileSrvIpAddressReply(msgbuf[0].fUint,
                ST::string::from_utf16(msgbuf[1].fString));
        break;
    case kGateKeeper2Cli_AuthSrvIpAddressReply:
        fReceiver->onAuthSrvIpAddressReply(msgbuf[0].fUint,
                ST::string::from_utf16(msgbuf[1].fString));
        break;
    }
    NCFreeMessage(msgbuf, msgDesc);
    return true;
}


/* pnGateKeeperClient */
pnGateKeeperClient::~pnGateKeeperClient()
{
    delete fIface;
    delete fDispatch;
    delete fSock;
}

void pnGateKeeperClient::setKeys(const unsigned char* keyX, const unsigned char* keyN, bool littleEndian)
{
    fLittleEndianKeys = littleEndian;
    memcpy(fKeyX, keyX, 64);
    memcpy(fKeyN, keyN, 64);
}

void pnGateKeeperClient::setClientInfo(uint32_t buildId, uint32_t buildType,
                                 uint32_t branchId, const plUuid& productId)
{
    fBuildId = buildId;
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

ENetError pnGateKeeperClient::connect(const char* host, short port)
{
    fSock = new pnRC4Socket();
    if (!fSock->connect(host, port)) {
        plDebug::Error("Error connecting to auth server\n");
        delete fSock;
        return kNetErrConnectFailed;
    }
    return performConnect();
}

ENetError pnGateKeeperClient::connect(int sockFd)
{
    fSock = new pnRC4Socket(sockFd);
    return performConnect();
}

void pnGateKeeperClient::disconnect()
{
    delete fIface;
    delete fDispatch;
    delete fSock;
    fIface = nullptr;
    fSock = nullptr;
    fDispatch = nullptr;
}

ENetError pnGateKeeperClient::performConnect()
{
    hsRAMStream connectHeader;
    /* Begin ConnectHeader */
    connectHeader.writeByte(kConnTypeCliToGateKeeper);
    connectHeader.writeShort(31);
    connectHeader.writeInt(fBuildId);
    connectHeader.writeInt(fBuildType);
    connectHeader.writeInt(fBranchId);
    fProductId.write(&connectHeader);
    /* Begin GateKeeperConnectHeader */
    connectHeader.writeInt(20);
    plUuid::Null.write(&connectHeader);
    fSock->send(connectHeader.data(), connectHeader.size());

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = nullptr;
        plDebug::Error("Error establishing GateKeeper connection");
        return kNetErrConnectFailed;
    }

    /* Set up encryption */
    uint8_t y_data[64];
    pnBigInteger clientSeed;
    {
        pnBigInteger X(fKeyX, 64, fLittleEndianKeys);
        pnBigInteger N(fKeyN, 64, fLittleEndianKeys);
        pnBigInteger b = pnBigInteger::Random(512);
        clientSeed = X.PowMod(b, N);
        pnBigInteger serverSeed = pnBigInteger(fKeyG).PowMod(b, N);
        serverSeed.getData(y_data, 64);
    }

    hsRAMStream cryptHeader;
    cryptHeader.writeByte(kNetCliCli2SrvConnect);
    cryptHeader.writeByte(66);
    cryptHeader.write(64, y_data);
    fSock->send(cryptHeader.data(), cryptHeader.size());

    uint8_t msg, len;
    if (fSock->recv(&msg, 1) <= 0 || fSock->recv(&len, 1) <= 0) {
        delete fSock;
        fSock = nullptr;
        plDebug::Error("Error negotiating GateKeeper connection");
        return kNetErrConnectFailed;
    }

    if (msg == kNetCliSrv2CliEncrypt) {
        uint8_t serverSeed[7];
        fSock->recv(serverSeed, 7);
        uint8_t seedData[64];
        clientSeed.getData(seedData, 64);
        for (size_t i=0; i<7; i++)
            serverSeed[i] ^= seedData[i];
        fSock->init(7, serverSeed);
    } else if (msg == kNetCliSrv2CliError) {
        uint32_t errorCode;
        fSock->recv(&errorCode, sizeof(uint32_t));
        delete fSock;
        fSock = nullptr;
        plDebug::Error("Error connecting to GateKeeper server: {}",
                       GetNetErrorString(errorCode));
        return (ENetError)errorCode;
    } else {
        delete fSock;
        fSock = nullptr;
        plDebug::Error("Got junk response from server");
        return kNetErrConnectFailed;
    }
    fDispatch = new Dispatch(this);
    if (fThreaded)
        fIface = new pnThreadedSocket(fDispatch, fSock);
    else
        fIface = new pnPolledSocket(fDispatch, fSock);
    fIface->run();
    return kNetSuccess;
}

uint32_t pnGateKeeperClient::sendPingRequest(uint32_t pingTimeMs)
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_PingRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = pingTimeMs;
    msg[1].fUint = transId;
    msg[2].fUint = 0;
    msg[3].fData = nullptr;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnGateKeeperClient::sendFileSrvIpAddressRequest(uint8_t which)
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_FileSrvIpAddressRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = which;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

uint32_t pnGateKeeperClient::sendAuthSrvIpAddressRequest()
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_AuthSrvIpAddressRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    uint32_t transId = nextTransId();
    msg[0].fUint = transId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnGateKeeperClient::onPingReply(uint32_t transId, uint32_t pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_PingReply");
}

void pnGateKeeperClient::onFileSrvIpAddressReply(uint32_t transId, const ST::string& addr)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_FileSrvIpAddressReply");
}

void pnGateKeeperClient::onAuthSrvIpAddressReply(uint32_t transId, const ST::string& addr)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_AuthSrvIpAddressReply");
}
