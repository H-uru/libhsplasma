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

#include "plNetMsgLoadClone.h"

void plNetMsgLoadClone::read(hsStream* S, plResManager* mgr)
{
    plNetMsgGameMessage::read(S, mgr);

    fObject.read(S);
    fIsPlayer = S->readBool();
    fIsLoading = S->readBool();
    fIsInitialState = S->readBool();
}

void plNetMsgLoadClone::write(hsStream* S, plResManager* mgr)
{
    plNetMsgGameMessage::write(S, mgr);

    fObject.write(S);
    S->writeBool(fIsPlayer);
    S->writeBool(fIsLoading);
    S->writeBool(fIsInitialState);
}

void plNetMsgLoadClone::IPrcWrite(pfPrcHelper* prc)
{
    plNetMsgGameMessage::IPrcWrite(prc);

    prc->startTag("LoadCloneParams");
    prc->writeParam("IsPlayer", fIsPlayer);
    prc->writeParam("IsLoading", fIsLoading);
    prc->writeParam("IsInitialState", fIsInitialState);
    prc->endTag(true);

    prc->startTag("Object");
    fObject.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgLoadClone::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LoadCloneParams") {
        fIsPlayer = tag->getParam("IsPlayer", "false").to_bool();
        fIsLoading = tag->getParam("IsLoading", "false").to_bool();
        fIsInitialState = tag->getParam("IsInitialState", "false").to_bool();
    } else if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fObject.prcParse(tag->getFirstChild());
    } else {
        plNetMsgGameMessage::IPrcParse(tag, mgr);
    }
}
