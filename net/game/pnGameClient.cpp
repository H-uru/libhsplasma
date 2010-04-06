#include "pnGameClient.h"
#include "GameMessages.h"
#include "Debug/plDebug.h"
#include "Stream/hsRAMStream.h"
#include "crypt/pnBigInteger.h"
#include "crypt/pnSha1.h"

/* Dispatch */
pnGameClient::Dispatch::Dispatch(pnRC4Socket* sock, pnGameClient* self)
            : fReceiver(self), fSock(sock)
{ }

void pnGameClient::Dispatch::run()
{
    hsUint16 msgId;
    while (fSock->isConnected()) {
        if (!fSock->waitForData()) {
            // Got an error
            break;
        }

        fSock->recv(&msgId, sizeof(hsUint16));
        const pnNetMsg* msgDesc = GET_Game2Cli(msgId);
        if (msgDesc == NULL) {
            plDebug::Error("Got invalid message ID (%u)", msgId);
            break;
        }

        msgparm_t* msgbuf = fSock->recvMsg(msgDesc);
        switch (msgId) {
        case kGame2Cli_PingReply:
            fReceiver->onPingReply(msgbuf[0].fUint);
            break;
        case kGame2Cli_JoinAgeReply:
            fReceiver->onJoinAgeReply(msgbuf[0].fUint, (ENetError)msgbuf[1].fUint);
            break;
        case kGame2Cli_PropagateBuffer:
            {
                hsRAMStream rs(pvLive);
                rs.copyFrom(msgbuf[2].fData, msgbuf[1].fUint);
                fReceiver->fResMgrMutex.lock();
                plCreatable* pCre = NULL;
                try {
                    pCre = fReceiver->fResMgr.ReadCreatable(&rs, true, msgbuf[1].fUint);
                } catch (hsException& ex) {
                    plDebug::Error("Error reading propagated message: %s\n", ex.what());
                    if (pCre != NULL)
                        delete pCre;
                    pCre = NULL;
                }
                fReceiver->fResMgrMutex.unlock();
                if (pCre != NULL) {
                    fReceiver->onPropagateMessage(pCre);
                    delete pCre;
                } else {
                    plDebug::Error("Ignored propagated message [%04X]%s",
                                   pdUnifiedTypeMap::PlasmaToMapped(msgbuf[0].fUint, pvLive),
                                   pdUnifiedTypeMap::ClassName(msgbuf[0].fUint, pvLive));
                }
            }
            break;
        case kGame2Cli_GameMgrMsg:
            plDebug::Warning("Warning: Skipping GameMgrMsg");
            break;
        }
        NCFreeMessage(msgbuf, msgDesc);
        fSock->signalStatus();
    } /* while connected */
}


/* pnGameClient */
pnGameClient::pnGameClient() : fSock(NULL), fDispatch(NULL)
{ }

pnGameClient::~pnGameClient()
{
    if (fSock != NULL)
        fSock->close();
    if (fDispatch != NULL)
        delete fDispatch;
    if (fSock != NULL)
        delete fSock;
}

void pnGameClient::setKeys(const unsigned char* keyX, const unsigned char* keyN)
{
    memcpy(fKeyX, keyX, 64);
    memcpy(fKeyN, keyN, 64);
}

void pnGameClient::setClientInfo(hsUint32 buildId, hsUint32 buildType,
                                 hsUint32 branchId, const plUuid& productId)
{
    fBuildId = buildId;
    fBuildType = buildType;
    fBranchId = branchId;
    fProductId = productId;
}

void pnGameClient::setJoinInfo(const plUuid& accountId, const plUuid& ageId)
{
    fAccountId = accountId;
    fAgeId = ageId;
}

ENetError pnGameClient::connect(const char* host, short port)
{
    pnSocket* sock = new pnSocket();
    if (!sock->connect(host, port)) {
        plDebug::Error("Error connecting to game server\n");
        delete sock;
        return kNetErrConnectFailed;
    }
    return performConnect(sock);
}

ENetError pnGameClient::connect(int sockFd)
{
    pnSocket* sock = new pnSocket(sockFd);
    return performConnect(sock);
}

ENetError pnGameClient::performConnect(pnSocket* sock)
{
    fSock = new pnRC4Socket(sock);

    hsUbyte connectHeader[67];  // ConnectHeader + GameConnectHeader
    /* Begin ConnectHeader */
    *(hsUbyte* )(connectHeader     ) = kConnTypeCliToGame;
    *(hsUint16*)(connectHeader +  1) = 31;
    *(hsUint32*)(connectHeader +  3) = fBuildId;
    *(hsUint32*)(connectHeader +  7) = fBuildType;
    *(hsUint32*)(connectHeader + 11) = fBranchId;
    fProductId.write(connectHeader + 15);
    /* Begin GameConnectHeader */
    *(hsUint32*)(connectHeader + 31) = 36;
    fAccountId.write(connectHeader + 35);
    fAgeId.write(connectHeader + 51);
    fSock->send(connectHeader, 67);

    if (!fSock->isConnected()) {
        delete fSock;
        fSock = NULL;
        plDebug::Error("Error establishing Game connection");
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
        plDebug::Error("Error negotiating Game connection");
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
        plDebug::Error("Error connecting to Game server: %s",
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

void pnGameClient::sendPingRequest(hsUint32 pingTimeMs)
{
    const pnNetMsg* desc = GET_Cli2Game(kCli2Game_PingRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = pingTimeMs;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

hsUint32 pnGameClient::sendJoinAgeRequest(hsUint32 ageMcpId,
                const plUuid& accountUuid, hsUint32 playerId)
{
    const pnNetMsg* desc = GET_Cli2Game(kCli2Game_JoinAgeRequest);
    msgparm_t* msg = NCAllocMessage(desc);
    hsUint32 transId = nextTransId();
    msg[0].fUint = transId;
    msg[1].fUint = ageMcpId;
    accountUuid.write(msg[2].fData);
    msg[3].fUint = playerId;
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
    return transId;
}

void pnGameClient::propagateMessage(plCreatable* pCre)
{
    const pnNetMsg* desc = GET_Cli2Game(kCli2Game_PropagateBuffer);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = pCre->ClassIndex(pvLive);
    hsRAMStream rs(pvLive);
    fResMgrMutex.lock();
    fResMgr.WriteCreatable(&rs, pCre);
    fResMgrMutex.unlock();
    msg[1].fUint = rs.size();
    msg[2].fData = new hsUbyte[msg[1].fUint];
    rs.copyTo(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}

void pnGameClient::onPingReply(hsUint32 pingTimeMs)
{
    plDebug::Warning("Warning: Ignoring Game2Cli_PingReply");
}

void pnGameClient::onJoinAgeReply(hsUint32 transId, ENetError result)
{
    plDebug::Warning("Warning: Ignoring Game2Cli_JoinAgeReply");
}

void pnGameClient::onPropagateMessage(plCreatable* msg)
{
    plDebug::Warning("Warning: Ignoring Game2Cli_PropagateBuffer");
}
