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

#ifndef _PLNETMSGGAMEMESSAGE_H
#define _PLNETMSGGAMEMESSAGE_H

#include "plNetMsgStream.h"
#include "Sys/plUnifiedTime.h"
#include "PRP/Message/plMessage.h"

class PLASMA_DLL plNetMsgGameMessage : public plNetMsgStream
{
    CREATABLE(plNetMsgGameMessage, kNetMsgGameMessage, plNetMsgStream)

private:
    plUnifiedTime fDeliveryTime;
    plMessage* fMessage;

public:
    plNetMsgGameMessage() : fMessage() { }
    ~plNetMsgGameMessage();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plUnifiedTime getDeliveryTime() const { return fDeliveryTime; }
    plMessage* getMessage() const { return fMessage; }

    void setDeliveryTime(const plUnifiedTime& deliveryTime) { fDeliveryTime = deliveryTime; }
    void setMessage(plMessage* Message);
};


class PLASMA_DLL plNetMsgGameMessageDirected : public plNetMsgGameMessage
{
    CREATABLE(plNetMsgGameMessageDirected, kNetMsgGameMessageDirected,
              plNetMsgGameMessage)

private:
    std::vector<unsigned int> fReceivers;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<unsigned int>& getReceivers() const { return fReceivers; }
    void setReceivers(const std::vector<unsigned int>& receivers) { fReceivers = receivers; }
};

#endif
