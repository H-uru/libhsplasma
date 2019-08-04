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

#ifndef _PLNETMSGSDLSTATE_H
#define _PLNETMSGSDLSTATE_H

#include "plNetMsgStreamedObject.h"
#include "SDL/plSDLMgr.h"

class PLASMA_DLL plNetMsgSDLState : public plNetMsgStreamedObject
{
    CREATABLE(plNetMsgSDLState, kNetMsgSDLState, plNetMsgStreamedObject)

private:
    bool fIsInitialState, fPersistOnServer, fIsAvatarState;
    // The stream is an SDL blob that will need to be parsed from
    // an SDL Manager with the correct descriptors loaded
    plStateDescriptor* fDescriptor;

public:
    plNetMsgSDLState()
        : fIsInitialState(), fPersistOnServer(), fIsAvatarState(), fDescriptor() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    bool findDescriptor(plSDLMgr* sdl);
    plStateDescriptor* getDescriptor() const { return fDescriptor; }

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool isInitialState() const { return fIsInitialState; }
    bool getPersistOnServer() const { return fPersistOnServer; }
    bool isAvatarState() const { return fIsAvatarState; }

    void setInitialState(bool initialState) { fIsInitialState = initialState; }
    void setPersistOnServer(bool persist) { fPersistOnServer = persist; }
    void setIsAvatarState(bool avState) { fIsAvatarState = avState; }
};


class PLASMA_DLL plNetMsgSDLStateBCast : public plNetMsgSDLState
{
    CREATABLE(plNetMsgSDLStateBCast, kNetMsgSDLStateBCast, plNetMsgSDLState)
};

#endif
