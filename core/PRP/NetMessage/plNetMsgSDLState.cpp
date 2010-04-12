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

#include "plNetMsgSDLState.h"
#include "SDL/plStateDataRecord.h"

/* plNetMsgSDLState */
plNetMsgSDLState::plNetMsgSDLState()
                : fIsInitialState(false), fPersistOnServer(false),
                  fIsAvatarState(false), fDescriptor(NULL) { }

void plNetMsgSDLState::read(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::read(S, mgr);

    fIsInitialState = S->readBool();
    fPersistOnServer = S->readBool();
    fIsAvatarState = S->readBool();
}

void plNetMsgSDLState::write(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::write(S, mgr);

    S->writeBool(fIsInitialState);
    S->writeBool(fPersistOnServer);
    S->writeBool(fIsAvatarState);
}

void plNetMsgSDLState::IPrcWrite(pfPrcHelper* prc) {
    if (fDescriptor != NULL) {
        // We have a loaded descriptor, so we can output actual
        // PRC data, instead of just a hex stream
        plNetMsgObject::IPrcWrite(prc);

        hsStream* blob = getStream();
        plStateDataRecord rec;
        rec.setDescriptor(fDescriptor);
        rec.read(blob, NULL);
        prc->startTag("SDLStateDefinitions");
        prc->writeParam("DescName", fDescriptor->getName());
        prc->writeParam("DescVersion", fDescriptor->getVersion());
        prc->endTag();
        rec.prcWrite(prc);
        prc->closeTag();
    } else {
        // No loaded descriptor, so just output the hex stream
        plNetMsgStreamedObject::IPrcWrite(prc);
    }

    prc->startTag("SDLStateParams");
    prc->writeParam("IsInitialState", fIsInitialState);
    prc->writeParam("PersistOnServer", fPersistOnServer);
    prc->writeParam("IsAvatarState", fIsAvatarState);
    prc->endTag(true);
}

void plNetMsgSDLState::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SDLStateParams") {
        fIsInitialState = tag->getParam("IsInitialState", "false").toBool();
        fPersistOnServer = tag->getParam("PersistOnServer", "false").toBool();
        fIsAvatarState = tag->getParam("IsAvatarState", "false").toBool();
    } else {
        if (fDescriptor != NULL)
            //TODO: Parse SDL as PRC
            plNetMsgObject::IPrcParse(tag, mgr);
        else
            plNetMsgStreamedObject::IPrcParse(tag, mgr);
    }
}

bool plNetMsgSDLState::findDescriptor(plSDLMgr* sdl) {
    hsStream* blob = getStream();
    plString descName;
    int descVersion = -1;
    plStateDataRecord::ReadStreamHeader(blob, descName, descVersion, NULL);
    fDescriptor = sdl->GetDescriptor(descName, descVersion);
    return (fDescriptor != NULL);
}
