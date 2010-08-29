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

#include "plNotifyMsg.h"

plNotifyMsg::plNotifyMsg() : fType(0), fID(0), fState(0.0f) {
    fBCastFlags |= kNetPropagate;
}

plNotifyMsg::~plNotifyMsg() {
    for (size_t i=0; i<fEvents.getSize(); i++)
        delete fEvents[i];
}

void plNotifyMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fType = S->readInt();
    fState = S->readFloat();
    if (S->getVer().isNewPlasma())
        fID = S->readByte();
    else
        fID = S->readInt();

    clearEvents();
    fEvents.setSizeNull(S->readInt());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i] = proEventData::Read(S, mgr);
}

void plNotifyMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeInt(fType);
    S->writeFloat(fState);
    if (S->getVer().isNewPlasma())
        S->writeByte(fID);
    else
        S->writeInt(fID);

    S->writeInt(fEvents.getSize());
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i]->write(S, mgr);
}

void plNotifyMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("NotifyParams");
    prc->writeParam("Type", fType);
    prc->writeParam("State", fState);
    prc->writeParam("ID", fID);
    prc->endTag(true);

    prc->writeSimpleTag("Events");
    for (size_t i=0; i<fEvents.getSize(); i++)
        fEvents[i]->prcWrite(prc);
    prc->closeTag();
}

void plNotifyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "NotifyParams") {
        fType = tag->getParam("Type", "0").toInt();
        fState = tag->getParam("State", "0").toFloat();
        fID = tag->getParam("ID", "0").toInt();
    } else if (tag->getName() == "Events") {
        clearEvents();
        fEvents.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEvents.getSize(); i++) {
            fEvents[i] = proEventData::PrcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

void plNotifyMsg::delEvent(size_t idx) {
    delete fEvents[idx];
    fEvents.remove(idx);
}

void plNotifyMsg::clearEvents() {
    for (size_t i=0; i<fEvents.getSize(); i++)
        delete fEvents[i];
    fEvents.clear();
}
