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

#include "plServerReplyMsg.h"
#include "Debug/plDebug.h"

void plServerReplyMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fType = S->readInt();
}

void plServerReplyMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeInt(fType);
}

void plServerReplyMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("ReplyType");
    prc->writeParamHex("value", (unsigned int)fType);
    prc->endTag(true);
}

void plServerReplyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ReplyType") {
        fType = tag->getParam("value", "0").to_int();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
