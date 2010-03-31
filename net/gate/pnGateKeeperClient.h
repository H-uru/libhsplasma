#ifndef _PNGATEKEEPERCLIENT_H
#define _PNGATEKEEPERCLIENT_H

#include "pnClient.h"
#include "Sys/plUuid.h"
#include "pnNetMsg.h"
#include "crypt/pnRC4.h"

DllClass pnGateKeeperClient : public pnClient {
public:
    pnGateKeeperClient();
    virtual ~pnGateKeeperClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN);
    void setClientInfo(hsUint32 buildId, hsUint32 buildType, hsUint32 branchId,
                       const plUuid& productId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual bool isConnected() const;

    virtual void signalStatus();
    virtual void waitForStatus();

    /* Outgoing Protocol */
    hsUint32 sendPingRequest(hsUint32 pingTimeMs);
    hsUint32 sendFileSrvIpAddressRequest(hsUbyte which);
    hsUint32 sendAuthSrvIpAddressRequest();

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(hsUint32 transId, hsUint32 pingTimeMs);
    virtual void onFileSrvIpAddressReply(hsUint32 transId, const plString& addr);
    virtual void onAuthSrvIpAddressReply(hsUint32 transId, const plString& addr);

protected:
    pnRC4Socket* fSock;

    hsUint32 fBuildId, fBuildType, fBranchId;
    plUuid fProductId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];

    class Dispatch : public hsThread {
    public:
        Dispatch(pnRC4Socket* sock, pnGateKeeperClient* self);
        virtual ~Dispatch();

    private:
        virtual void run();

        pnGateKeeperClient* fReceiver;
        pnRC4Socket* fSock;
    } *fDispatch;

    ENetError performConnect(pnSocket* sock);
};

#endif
