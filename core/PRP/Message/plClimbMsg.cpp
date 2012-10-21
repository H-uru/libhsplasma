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

#include "plClimbMsg.h"

void plClimbMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCommand = S->readInt();
    fDirection = S->readInt();
    fStatus = S->readBool();
    fTarget = mgr->readKey(S);
}

void plClimbMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fCommand);
    S->writeInt(fDirection);
    S->writeBool(fStatus);
    mgr->writeKey(S, fTarget);
}

void plClimbMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("ClimbMsgParams");
    prc->writeParamHex("Command", fCommand);
    prc->writeParamHex("Direction", fDirection);
    prc->writeParam("Status", fStatus);
    prc->endTag(true);

    prc->writeSimpleTag("Target");
    fTarget->prcWrite(prc);
    prc->closeTag();
}

void plClimbMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ClimbMsgParams") {
        fCommand = tag->getParam("Command", "0").toUint();
        fDirection = tag->getParam("Direction", "0").toUint();
        fStatus = tag->getParam("Status", "false").toBool();
    } else if (tag->getName() == "Target") {
        if (tag->hasChildren())
            fTarget = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
