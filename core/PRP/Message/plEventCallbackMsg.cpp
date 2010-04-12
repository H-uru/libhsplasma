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

#include "plEventCallbackMsg.h"

plEventCallbackMsg::plEventCallbackMsg()
                  : fEventTime(0.0f), fEvent((CallbackEvent)0), fIndex(0),
                    fRepeats(0), fUser(0) { }

void plEventCallbackMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fEventTime = S->readFloat();
    fEvent = (CallbackEvent)S->readShort();
    fIndex = S->readShort();
    fRepeats = S->readShort();
    fUser = S->readShort();
}

void plEventCallbackMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeFloat(fEventTime);
    S->writeShort(fEvent);
    S->writeShort(fIndex);
    S->writeShort(fRepeats);
    S->writeShort(fUser);
}

void plEventCallbackMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("EventCallback");
    prc->writeParam("EventTime", fEventTime);
    prc->writeParam("Event", fEvent);
    prc->writeParam("Index", fIndex);
    prc->writeParam("Repeats", fRepeats);
    prc->writeParam("User", fUser);
    prc->endTag(true);
}

void plEventCallbackMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "EventCallback") {
        fEventTime = tag->getParam("EventTime", "0").toFloat();
        fEvent = (CallbackEvent)tag->getParam("Event", "0").toInt();
        fIndex = tag->getParam("Index", "0").toInt();
        fRepeats = tag->getParam("Repeats", "0").toInt();
        fUser = tag->getParam("User", "0").toInt();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
