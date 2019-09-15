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

#ifndef _PLLOADCLONEMSG_H
#define _PLLOADCLONEMSG_H

#include "plMessage.h"

class PLASMA_DLL plLoadCloneMsg : public plMessage
{
    CREATABLE(plLoadCloneMsg, kLoadCloneMsg, plMessage)

protected:
    plKey fCloneKey, fRequestorKey;
    unsigned char fValidMsg, fIsLoading;
    unsigned int fUserData, fOriginatingPlayerID;
    plMessage* fTriggerMsg;

public:
    plLoadCloneMsg()
        : fValidMsg(), fIsLoading(), fUserData(), fOriginatingPlayerID(),
          fTriggerMsg()
    {
        fBCastFlags |= kNetPropagate;
    }

    ~plLoadCloneMsg();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getCloneKey() const { return fCloneKey; }
    plKey getRequestor() const { return fRequestorKey; }
    unsigned char getValidMsg() const { return fValidMsg; }
    unsigned char getIsLoading() const { return fIsLoading; }
    unsigned int getUserData() const { return fUserData; }
    unsigned int getOriginatingPlayerID() const { return fOriginatingPlayerID; }
    plMessage* getTriggerMsg() const { return fTriggerMsg; }

    void setCloneKey(plKey key) { fCloneKey = std::move(key); }
    void setRequestor(plKey key) { fRequestorKey = std::move(key); }
    void setValidMsg(unsigned char validMsg) { fValidMsg = validMsg; }
    void setIsLoading(unsigned char isLoading) { fIsLoading = isLoading; }
    void setUserData(unsigned int userData) { fUserData = userData; }
    void setOriginatingPlayerID(unsigned int playerID) { fOriginatingPlayerID = playerID; }

    void setTriggerMsg(plMessage* TriggerMsg);
};

#endif
