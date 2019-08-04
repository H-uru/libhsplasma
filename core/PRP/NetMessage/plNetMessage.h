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

#ifndef _PLNETMESSAGE_H
#define _PLNETMESSAGE_H

#include "PRP/plCreatable.h"
#include "Sys/plUnifiedTime.h"
#include "Sys/plUuid.h"

class PLASMA_DLL plNetMessage : public plCreatable
{
    CREATABLE(plNetMessage, kNetMessage, plCreatable)

public:
    enum ContentFlags
    {
        kHasTimeSent = 0x1,
        kHasGameMsgRecvrs = 0x2,
        kEchoBackToSender = 0x4,
        kRequestP2P = 0x8,
        kAllowTimeOut = 0x10,
        kIndirectMember = 0x20,
        kPublicIPClient = 0x40,
        kHasContext = 0x80,
        kAskVaultForGameState = 0x100,
        kHasTransactionID = 0x200,
        kNewSDLState = 0x400,
        kInitialAgeStateRequest = 0x800,
        kHasPlayerID = 0x1000,
        kUseRelevanceRegions = 0x2000,
        kHasAcctUuid = 0x4000,
        kInterAgeRouting = 0x8000,
        kHasVersion = 0x10000,
        kIsSystemMessage = 0x20000,
        kNeedsReliableSend = 0x40000,
        kRouteToAllPlayers = 0x80000
    };

private:
    unsigned int fFlags;
    unsigned char fProtocolVerMaj, fProtocolVerMin;
    plUnifiedTime fTimeSent;
    unsigned int fContext, fTransID, fPlayerID;
    plUuid fAcctUuid;

public:
    plNetMessage()
        : fFlags(), fProtocolVerMaj(12), fProtocolVerMin(6), fContext(),
          fTransID(), fPlayerID() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getFlags() const { return fFlags; }
    unsigned char getProtocolVerMaj() const { return fProtocolVerMaj; }
    unsigned char getProtocolVerMin() const { return fProtocolVerMin; }
    plUnifiedTime getTimeSent() const { return fTimeSent; }
    unsigned int getContext() const { return fContext; }
    unsigned int getTransID() const { return fTransID; }
    unsigned int getPlayerID() const { return fPlayerID; }
    plUuid getAcctUuid() const { return fAcctUuid; }

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setTimeSent(const plUnifiedTime& timeSent) { fTimeSent = timeSent; }
    void setContext(unsigned int context) { fContext = context; }
    void setTransID(unsigned int transID) { fTransID = transID; }
    void setPlayerID(unsigned int playerID) { fPlayerID = playerID; }
    void setAcctUuid(const plUuid& acctUuid) { fAcctUuid = acctUuid; }

    void setProtocolVer(unsigned char maj, unsigned char min)
    {
        fProtocolVerMaj = maj;
        fProtocolVerMin = min;
    }
};


class PLASMA_DLL plNetMsgServerToClient : public plNetMessage
{
    CREATABLE(plNetMsgServerToClient, kNetMsgServerToClient, plNetMessage)
};

#endif
