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

class PLASMANET_DLL pnGameClient : public pnClient
{
public:
    pnGameClient(plResManager* mgr, bool deleteMsgs = true, bool threaded = true)
        : fSock(), fResMgr(mgr), fThreaded(threaded), fKeyG(73),
          fDeleteMsgs(deleteMsgs), fDispatch() { }
    ~pnGameClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN,
                 bool littleEndian = true);
    void setKeyG(int g) { fKeyG = g; }
    void setClientInfo(uint32_t buildId, uint32_t buildType, uint32_t branchId,
                       const plUuid& productId);
    void setJoinInfo(const plUuid& accountId, const plUuid& ageId);
    ENetError connect(const char* host, short port = 14617) HS_OVERRIDE;
    ENetError connect(int sockFd) HS_OVERRIDE;
    void disconnect() HS_OVERRIDE;

    bool isConnected() const HS_OVERRIDE
    {
        return fSock && fSock->isConnected();
    }

//     virtual void signalStatus() { fSock->signalStatus(); }
//     virtual void waitForStatus() { fSock->waitForStatus(); }

    /* Outgoing Protocol */
    void sendPingRequest(uint32_t pingTimeMs);
    uint32_t sendJoinAgeRequest(uint32_t ageMcpId, const plUuid& accountUuid,
                uint32_t playerId);
    virtual void propagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(uint32_t pingTimeMs);
    virtual void onJoinAgeReply(uint32_t transId, ENetError result);
    virtual void onPropagateMessage(plCreatable* msg);
    // TODO: GameMgrMsg

protected:
    pnRC4Socket* fSock;
    plResManager* fResMgr;
    bool fThreaded;

    uint32_t fBuildId, fBuildType, fBranchId;
    plUuid fProductId;
    plUuid fAccountId, fAgeId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];
    bool fLittleEndianKeys;
    int fKeyG;
    bool fDeleteMsgs;

    class Dispatch : public pnDispatcher
    {
    public:
        Dispatch(pnGameClient* self, bool deleteMsgs)
            : fReceiver(self), fDeleteMsgs(deleteMsgs) { }
        ~Dispatch() { }
        bool dispatch(pnSocket* sock) HS_OVERRIDE;

    private:
        pnGameClient* fReceiver;
        bool fDeleteMsgs;
    } *fDispatch;

    ENetError performConnect();
};

#endif
