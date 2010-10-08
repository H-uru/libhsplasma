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

#ifndef _PNGAMECLIENT_H
#define _PNGAMECLIENT_H

#include "pnClient.h"
#include "Sys/plUuid.h"
#include "PRP/plCreatable.h"
#include "pnNetMsg.h"
#include "crypt/pnRC4.h"
#include "pnSocketInterface.h"

DllClass pnGameClient : public pnClient {
public:
    pnGameClient(plResManager* mgr, bool deleteMsgs = true, bool threaded = true);
    virtual ~pnGameClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN);
    void setClientInfo(hsUint32 buildId, hsUint32 buildType, hsUint32 branchId,
                       const plUuid& productId);
    void setJoinInfo(const plUuid& accountId, const plUuid& ageId);
    virtual ENetError connect(const char* host, short port = 14617);
    virtual ENetError connect(int sockFd);
    virtual void disconnect();

    virtual bool isConnected() const
    { return (fSock != NULL) && fSock->isConnected(); }

//     virtual void signalStatus() { fSock->signalStatus(); }
//     virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    void sendPingRequest(hsUint32 pingTimeMs);
    hsUint32 sendJoinAgeRequest(hsUint32 ageMcpId, const plUuid& accountUuid,
                hsUint32 playerId);
    virtual void propagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(hsUint32 pingTimeMs);
    virtual void onJoinAgeReply(hsUint32 transId, ENetError result);
    virtual void onPropagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

protected:
    pnRC4Socket* fSock;
    plResManager* fResMgr;
    bool fThreaded;

    hsUint32 fBuildId, fBuildType, fBranchId;
    plUuid fProductId;
    plUuid fAccountId, fAgeId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];
    bool fDeleteMsgs;

    class Dispatch : public pnDispatcher {
    public:
        Dispatch(pnGameClient* self, bool deleteMsgs);
        virtual ~Dispatch();
        virtual bool dispatch(pnSocket* sock);

    private:
        pnGameClient* fReceiver;
        bool fDeleteMsgs;
    } *fDispatch;

    ENetError performConnect();
};

#endif
