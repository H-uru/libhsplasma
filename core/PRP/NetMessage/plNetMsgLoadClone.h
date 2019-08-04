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

#ifndef _PLNETMSGLOADCLONE_H
#define _PLNETMSGLOADCLONE_H

#include "plNetMsgGameMessage.h"
#include "plNetMsgObject.h"

class PLASMA_DLL plNetMsgLoadClone : public plNetMsgGameMessage
{
    CREATABLE(plNetMsgLoadClone, kNetMsgLoadClone, plNetMsgGameMessage)

private:
    plUoid fObject;
    bool fIsPlayer, fIsLoading, fIsInitialState;

public:
    plNetMsgLoadClone()
        : fIsPlayer(), fIsLoading(), fIsInitialState() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plUoid getObject() const { return fObject; }
    bool isPlayer() const { return fIsPlayer; }
    bool isLoading() const { return fIsLoading; }
    bool isInitialState() const { return fIsInitialState; }

    void setObject(const plUoid& obj) { fObject = obj; }
    void setIsPlayer(bool isPlayer) { fIsPlayer = isPlayer; }
    void setIsLoading(bool isLoading) { fIsLoading = isLoading; }
    void setIsInitialState(bool isInitialState) { fIsInitialState = isInitialState; }
};

#endif
