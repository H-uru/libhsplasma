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

#include "plConsoleMsg.h"

void plConsoleMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fCmd = S->readInt();
    unsigned short len = S->readShort();
    fString = S->readStr(len);
}

void plConsoleMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeInt(fCmd);
    S->writeShort(fString.size());
    S->writeStr(fString);
}

void plConsoleMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("Command");
    prc->writeParam("Type", fCmd);
    prc->writeParam("String", fString);
    prc->endTag(true);
}

void plConsoleMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Command") {
        fCmd = tag->getParam("Type", "0").to_uint();
        fString = tag->getParam("String", "");
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
