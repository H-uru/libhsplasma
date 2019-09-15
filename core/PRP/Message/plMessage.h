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

#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "PRP/plCreatable.h"
#include "PRP/KeyedObject/plKey.h"
#include "ResManager/plResManager.h"

class PLASMA_DLL plMessage : public plCreatable
{
    CREATABLE(plMessage, kMessage, plCreatable)

public:
    enum plBCastFlags
    {
        kBCastNone = 0x0,
        kBCastByType = 0x1,
        kBCastUNUSED_0 = 0x2,
        kPropagateToChildren = 0x4,
        kBCastByExactType = 0x8,
        kPropagateToModifiers = 0x10,
        kClearAfterBCast = 0x20,
        kNetPropagate = 0x40,
        kNetSent = 0x80,
        kNetUseRelevanceRegions = 0x100,
        kNetForce = 0x200,
        kNetNonLocal = 0x400,
        kLocalPropagate = 0x800,
        kNetNonDeterministic = 0x200,
        kMsgWatch = 0x1000,
        kNetStartCascade = 0x2000,
        kNetAllowInterAge = 0x4000,
        kNetSendUnreliable = 0x8000,
        kCCRSendToAllPlayers = 0x10000,
        kNetCreatedRemotely = 0x20000
    };

protected:
    plKey fSender;
    std::vector<plKey> fReceivers;
    double fTimeStamp;
    unsigned int fBCastFlags;

public:
    plMessage() : fTimeStamp(), fBCastFlags(kLocalPropagate) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE { IMsgRead(S, mgr); }
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE { IMsgWrite(S, mgr); }

protected:
    void IMsgRead(hsStream* S, plResManager* mgr);
    void IMsgWrite(hsStream* S, plResManager* mgr);
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSender() const { return fSender; }
    double getTimeStamp() const { return fTimeStamp; }
    unsigned int getBCastFlags() const { return fBCastFlags; }

    void setSender(plKey sender) { fSender = std::move(sender); }
    void setTimeStamp(double timestamp) { fTimeStamp = timestamp; }
    void setBCastFlags(unsigned int flags) { fBCastFlags = flags; }

    const std::vector<plKey>& getReceivers() const { return fReceivers; }
    std::vector<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey receiver) { fReceivers.emplace_back(std::move(receiver)); }
    void delReceiver(size_t idx) { fReceivers.erase(fReceivers.begin() + idx); }
    void clearReceivers() { fReceivers.clear(); }
};

#endif
