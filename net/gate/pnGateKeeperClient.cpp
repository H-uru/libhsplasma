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
#include "Debug/plDebug.h"
#include "crypt/pnBigInteger.h"
#include "crypt/pnSha1.h"

/* Dispatch */
pnGateKeeperClient::Dispatch::Dispatch(pnRC4Socket* sock, pnGateKeeperClient* self)
                  : fReceiver(self), fSock(sock)
{ }

void pnGateKeeperClient::Dispatch::run()
{
    hsUint16 msgId;
    while (fSock->isConnected()) {
        if (!fSock->waitForData()) {
            // Got an error
            break;
        }

        fSock->recv(&msgId, sizeof(hsUint16));
        const pnNetMsg* msgDesc = GET_GateKeeper2Cli(msgId);
        if (msgDesc == NULL) {
            plDebug::Error("Got invalid message ID (%u)", msgId);
            break;
        }

        msgparm_t* msgbuf = fSock->recvMsg(msgDesc);
        switch (msgId) {
        case kGateKeeper2Cli_PingReply:
            fReceiver->onPingReply(msgbuf[1].fUint, msgbuf[0].fUint);
            if (msgbuf[2].fUint != 0)
                plDebug::Debug("Got non-zero payload");
            break;
        case kGateKeeper2Cli_FileSrvIpAddressReply:
            fReceiver->onFileSrvIpAddressReply(msgbuf[0].fUint,
                                NCstrToString(msgbuf[1].fString));
            break;
        case kGateKeeper2Cli_AuthSrvIpAddressReply:
            fReceiver->onAuthSrvIpAddressReply(msgbuf[0].fUint,
                                NCstrToString(msgbuf[1].fString));
            break;
        }
        NCFreeMessage(msgbuf, msgDesc);
        fSock->signalStatus();
    } /* while connected */
}


/* pnGateKeeperClient */
pnGateKeeperClient::pnGateKeeperClient() : fSock(NULL), fDispatch(NULL)
{ }

pnGateKeeperClient::~pnGateKeeperClient()
{
    if (fSock != NULL)
        fSock->close();
    delete fDispatch;
    delete fSock;
}

void pnGateKeeperClient::setKeys(const unsigned char* keyX, const unsigned char* keyN)
{
    memcpy(fKeyX, keyX, 64);
    memcpy(fKeyN, keyN, 64);
}

void pnGateKeeperClient::setClientInfo(hsUint32 buildId, hsUint32 buildType,
                                 hsUint32 branchId, const plUuid& productId)
{
    fBuildId = buildId;
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

ENetError pnGateKeeperClient::connect(const char* host, short port)
{
    pnSocket* sock = new pnSocket();
    if (!sock->connect(host, port)) {
        plDebug::Error("Error connecting to auth server\n");
        delete sock;
        return kNetErrConnectFailed;
    }
    return performConnect(sock);
}

ENetError pnGateKeeperClient::connect(int sockFd)
{
    pnSocket* sock = new pnSocket(sockFd);
    return performConnect(sock);
}

ENetError pnGateKeeperClient::performConnect(pnSocket* sock)
{
    fSock = new pnRC4Socket(sock);

    hsUbyte connectHeader[51];  // ConnectHeader + GateKeeperConnectHeader
    /* Begin ConnectHeader */
    *(hsUbyte* )(connectHeader     ) = kConnTypeCliToGateKeeper;
    *(hsUint16*)(connectHeader +  1) = 31;
    *(hsUint32*)(connectHeader +  3) = fBuildId;
    *(hsUint32*)(connectHeader +  7) = fBuildType;
    *(hsUint32*)(connectHeader + 11) = fBranchId;
    fProductId.write(connectHeader + 15);
    /* Begin GateKeeperConnectHeader */
    *(hsUint32*)(connectHeader + 31) = 20;
    memset(connectHeader + 35, 0, 16);
    fSock->send(connectHeader, 51);

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error establishing GateKeeper connection");
        return kNetErrConnectFailed;
    }

    /* Set up encryption */
    hsUbyte y_data[64];
    pnBigInteger clientSeed;
    {
        pnBigInteger X(fKeyX, 64);
        pnBigInteger N(fKeyN, 64);
        pnBigInteger b = pnBigInteger::Random(512);
        clientSeed = X.PowMod(b, N);
        pnBigInteger serverSeed = pnBigInteger(4).PowMod(b, N);
        serverSeed.getData(y_data, 64);
    }

    hsUbyte cryptHeader[66];
    *(hsUbyte*)(cryptHeader    ) = kNetCliCli2SrvConnect;
    *(hsUbyte*)(cryptHeader + 1) = 66;
    memcpy(cryptHeader + 2, y_data, 64);
    fSock->send(cryptHeader, 66);

    hsUbyte msg, len;
    if (fSock->recv(&msg, 1) <= 0 || fSock->recv(&len, 1) <= 0) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error negotiating GateKeeper connection");
        return kNetErrConnectFailed;
    }

    if (msg == kNetCliSrv2CliEncrypt) {
        hsUbyte serverSeed[7];
        fSock->recv(serverSeed, 7);
        hsUbyte seedData[64];
        clientSeed.getData(seedData, 64);
        for (size_t i=0; i<7; i++)
            serverSeed[i] ^= seedData[i];
        fSock->init(7, serverSeed);
    } else if (msg == kNetCliSrv2CliError) {
        hsUint32 errorCode;
        fSock->recv(&errorCode, sizeof(hsUint32));
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error connecting to GateKeeper server: %s",
                       GetNetErrorString(errorCode));
        return (ENetError)errorCode;
    } else {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Got junk response from server");
        return kNetErrConnectFailed;
    }
    fDispatch = new Dispatch(fSock, this);
    fDispatch->start();
    return kNetSuccess;
}

hsUint32 pnGateKeeperClient::sendPingRequest(hsUint32 pingTimeMs)
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_PingRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = pingTimeMs;
    msg[1].fUint = transId;
    msg[2].fUint = 0;
    msg[3].fData = NULL;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnGateKeeperClient::sendFileSrvIpAddressRequest(hsUbyte which)
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_FileSrvIpAddressRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = which;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

hsUint32 pnGateKeeperClient::sendAuthSrvIpAddressRequest()
{
    const pnNetMsg* desc = GET_Cli2GateKeeper(kCli2GateKeeper_AuthSrvIpAddressRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnGateKeeperClient::onPingReply(hsUint32 transId, hsUint32 pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_PingReply");
}

void pnGateKeeperClient::onFileSrvIpAddressReply(hsUint32 transId, const plString& addr)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_FileSrvIpAddressReply");
}

void pnGateKeeperClient::onAuthSrvIpAddressReply(hsUint32 transId, const plString& addr)
{
    plDebug::Warning("Warning: Ignoring GateKeeper2Cli_AuthSrvIpAddressReply");
}
