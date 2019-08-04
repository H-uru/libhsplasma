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

#include "plCursorChangeMsg.h"

void plCursorChangeMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fType = S->readInt();
    fPriority = S->readInt();
}

void plCursorChangeMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeInt(fType);
    S->writeInt(fPriority);
}

void plCursorChangeMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);
    prc->startTag("CursorChange");
    prc->writeParam("Type", fType);
    prc->writeParam("Priority", fPriority);
    prc->endTag(true);
}

void plCursorChangeMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CursorChange") {
        fType = tag->getParam("Type", "0").to_int();
        fPriority = tag->getParam("Priority", "0").to_int();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
