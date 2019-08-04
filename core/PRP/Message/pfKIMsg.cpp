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

#include "pfKIMsg.h"

void pfKIMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fCommand = S->readByte();
    fUser = S->readSafeStr();
    fPlayerID = S->readInt();
    fString = S->readSafeWStr();
    fFlags = S->readInt();
    fDelay = S->readFloat();
    fValue = S->readInt();
}

void pfKIMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeByte(fCommand);
    S->writeSafeStr(fUser);
    S->writeInt(fPlayerID);
    S->writeSafeWStr(fString);
    S->writeInt(fFlags);
    S->writeFloat(fDelay);
    S->writeInt(fValue);
}

void pfKIMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("Parameters");
    prc->writeParam("Command", fCommand);
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Delay", fDelay);
    prc->writeParam("Value", fValue);
    prc->endTag(true);

    prc->startTag("Player");
    prc->writeParam("ID", fPlayerID);
    prc->writeParam("User", fUser);
    prc->endTag(true);

    prc->startTag("Message");
    prc->writeParam("value", fString);
    prc->endTag(true);
}

void pfKIMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Parameters") {
        fCommand = (uint8_t)tag->getParam("Command", "0").to_uint();
        fFlags = tag->getParam("Flags", "0").to_uint();
        fDelay = tag->getParam("Delay", "0").to_float();
        fValue = tag->getParam("Value", "0").to_int();
    } else if (tag->getName() == "Player") {
        fUser = tag->getParam("User", "");
        fPlayerID = tag->getParam("ID", "0").to_uint();
    } else if (tag->getName() == "Message") {
        fString = tag->getParam("value", "");
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
