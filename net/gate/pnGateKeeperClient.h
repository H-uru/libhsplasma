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
#include "pnSocketInterface.h"


class PLASMANET_DLL pnGateKeeperClient : public pnClient
{
public:
    pnGateKeeperClient(bool threaded = true)
         : fSock(), fThreaded(threaded), fKeyG(4), fDispatch() { }
    ~pnGateKeeperClient();

    void setKeys(const unsigned char* keyX, const unsigned char* keyN,
                 bool littleEndian = true);
    void setKeyG(int g) { fKeyG = g; }
    void setClientInfo(uint32_t buildId, uint32_t buildType, uint32_t branchId,
                       const plUuid& productId);
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
    uint32_t sendPingRequest(uint32_t pingTimeMs);
    uint32_t sendFileSrvIpAddressRequest(uint8_t which);
    uint32_t sendAuthSrvIpAddressRequest();

    /* Incoming Protocol - To be implemented by subclasses */
    virtual void onPingReply(uint32_t transId, uint32_t pingTimeMs);
    virtual void onFileSrvIpAddressReply(uint32_t transId, const ST::string& addr);
    virtual void onAuthSrvIpAddressReply(uint32_t transId, const ST::string& addr);

protected:
    pnRC4Socket* fSock;
    bool fThreaded;

    uint32_t fBuildId, fBuildType, fBranchId;
    plUuid fProductId;

private:
    unsigned char fKeyX[64];
    unsigned char fKeyN[64];
    bool fLittleEndianKeys;
    int fKeyG;

    class Dispatch : public pnDispatcher
    {
    public:
        Dispatch(pnGateKeeperClient* self) : fReceiver(self) { }
        ~Dispatch() { }
        bool dispatch(pnSocket* sock) HS_OVERRIDE;

    private:
        pnGateKeeperClient* fReceiver;
    } *fDispatch;

    ENetError performConnect();
};

#endif
