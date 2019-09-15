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

#ifndef _PLAVBRAINCOOP_H
#define _PLAVBRAINCOOP_H

#include "plAvBrainGeneric.h"

class PLASMA_DLL plAvBrainCoop : public plAvBrainGeneric
{
    CREATABLE(plAvBrainCoop, kAvBrainCoop, plAvBrainGeneric)

private:
    unsigned int fInitiatorID;
    unsigned short fInitiatorSerial;
    bool fWaitingForClick;
    plKey fHostKey, fGuestKey;
    std::vector<plKey> fRecipients;

public:
    plAvBrainCoop()
        : fInitiatorID(), fInitiatorSerial(), fWaitingForClick() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getRecipients() const { return fRecipients; }
    std::vector<plKey>& getRecipients() { return fRecipients; }
    void addRecipeient(plKey recp) { fRecipients.emplace_back(std::move(recp)); }
    void delRecipient(size_t idx) { fRecipients.erase(fRecipients.begin() + idx); }
    void clearRecipients() { fRecipients.clear(); }

    unsigned int getInitiatorID() const { return fInitiatorID; }
    unsigned short getInitiatorSerial() const { return fInitiatorSerial; }
    bool isWaitingForClick() const { return fWaitingForClick; }
    plKey getHostKey() const { return fHostKey; }
    plKey getGuestKey() const { return fGuestKey; }

    void setInitiatorID(unsigned int id) { fInitiatorID = id; }
    void setInitiatorSerial(unsigned short serial) { fInitiatorSerial = serial; }
    void setWaitingForClick(bool waiting) { fWaitingForClick = waiting; }
    void setHostKey(plKey host) { fHostKey = std::move(host); }
    void setGuestKey(plKey guest) { fGuestKey = std::move(guest); }
};

#endif
