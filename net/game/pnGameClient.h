#ifndef _PNGAMECLIENT_H
#define _PNGAMECLIENT_H

#include "pnClient.h"
#include "Sys/plUuid.h"
#include "PRP/plCreatable.h"
#include "pnNetMsg.h"
#include "crypt/pnRC4.h"

DllClass pnGameClient : public pnClient {
public:
    pnGameClient();
    virtual ~pnGameClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN);
    void setClientInfo(hsUint32 buildId, hsUint32 buildType, hsUint32 branchId,
                       const plUuid& productId);
    void setJoinInfo(const plUuid& accountId, const plUuid& ageId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual bool isConnected() const;

    virtual void signalStatus();
    virtual void waitForStatus();

    /* Outgoing Protocol */
    void sendPingRequest(hsUint32 pingTimeMs);
    hsUint32 sendJoinAgeRequest(hsUint32 ageMcpId, const plUuid& accountUuid,
                hsUint32 playerId);
    void propagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(hsUint32 pingTimeMs);
    virtual void onJoinAgeReply(hsUint32 transId, ENetError result);
    virtual void onPropagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

protected:
    pnRC4Socket* fSock;
    plResManager fResMgr;
    hsMutex fResMgrMutex;

    hsUint32 fBuildId, fBuildType, fBranchId;
    plUuid fProductId;
    plUuid fAccountId, fAgeId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];

    class Dispatch : public hsThread {
    public:
        Dispatch(pnRC4Socket* sock, pnGameClient* self);
        virtual ~Dispatch();

    private:
        virtual void run();

        pnGameClient* fReceiver;
        pnRC4Socket* fSock;
    } *fDispatch;

    ENetError performConnect(pnSocket* sock);
};

#endif
