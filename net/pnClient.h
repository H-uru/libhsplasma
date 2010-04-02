#ifndef _PNCLIENT_H
#define _PNCLIENT_H

#include "PlasmaDefs.h"
#include "Protocol.h"
#include "Sys/hsThread.h"

DllClass pnClient {
public:
    pnClient() { }
    virtual ~pnClient() { }

    virtual ENetError connect(const char* host, short port = 14617) = 0;
    virtual ENetError connect(int sockFd) = 0;
    virtual bool isConnected() const = 0;

    virtual void signalStatus() = 0;
    virtual void waitForStatus() = 0;

protected:
    hsUint32 nextTransId();
};

#endif
