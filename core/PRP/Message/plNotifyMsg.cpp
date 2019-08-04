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

plNotifyMsg::~plNotifyMsg()
{
    for (auto event = fEvents.begin(); event != fEvents.end(); ++event)
        delete *event;
}

void plNotifyMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fType = S->readInt();
    fState = S->readFloat();
    if (S->getVer().isNewPlasma())
        fID = S->readByte();
    else
        fID = S->readInt();

    clearEvents();
    fEvents.resize(S->readInt());
    for (size_t i=0; i<fEvents.size(); i++)
        fEvents[i] = proEventData::Read(S, mgr);
}

void plNotifyMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeInt(fType);
    S->writeFloat(fState);
    if (S->getVer().isNewPlasma())
        S->writeByte(fID);
    else
        S->writeInt(fID);

    S->writeInt(fEvents.size());
    for (size_t i=0; i<fEvents.size(); i++)
        fEvents[i]->write(S, mgr);
}

void plNotifyMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("NotifyParams");
    prc->writeParam("Type", fType);
    prc->writeParam("State", fState);
    prc->writeParam("ID", fID);
    prc->endTag(true);

    prc->writeSimpleTag("Events");
    for (size_t i=0; i<fEvents.size(); i++)
        fEvents[i]->prcWrite(prc);
    prc->closeTag();
}

void plNotifyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "NotifyParams") {
        fType = tag->getParam("Type", "0").to_int();
        fState = tag->getParam("State", "0").to_float();
        fID = tag->getParam("ID", "0").to_int();
    } else if (tag->getName() == "Events") {
        clearEvents();
        fEvents.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEvents.size(); i++) {
            fEvents[i] = proEventData::PrcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

void plNotifyMsg::delEvent(size_t idx)
{
    delete fEvents[idx];
    fEvents.erase(fEvents.begin() + idx);
}

void plNotifyMsg::clearEvents()
{
    for (auto event = fEvents.begin(); event != fEvents.end(); ++event)
        delete *event;
    fEvents.clear();
}
