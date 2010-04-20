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
    virtual void disconnect();

    virtual bool isConnected() const
    { return (fSock != NULL) && fSock->isConnected(); }

    virtual void signalStatus() { fSock->signalStatus(); }
    virtual void waitForStatus() { fSock->waitForStatus(); }

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

    private:
        virtual void run();

        pnGateKeeperClient* fReceiver;
        pnRC4Socket* fSock;
    } *fDispatch;

    ENetError performConnect(pnSocket* sock);
};

#endif
