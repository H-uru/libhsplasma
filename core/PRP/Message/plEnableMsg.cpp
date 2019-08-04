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

#include "plEnableMsg.h"

plEnableMsg::plEnableMsg()
{
    fCmd.setName(kDisable, "kDisable");
    fCmd.setName(kEnable, "kEnable");
    fCmd.setName(kDrawable, "kDrawable");
    fCmd.setName(kPhysical, "kPhysical");
    fCmd.setName(kAudible, "kAudible");
    fCmd.setName(kAll, "kAll");
    fCmd.setName(kByType, "kByType");
}

void plEnableMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fCmd.read(S);
    fTypes.read(S);
}

void plEnableMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    fCmd.write(S);
    fTypes.write(S);
}

void plEnableMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Types");
    fTypes.prcWrite(prc);
    prc->closeTag();
}

void plEnableMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Types") {
        if (tag->hasChildren())
            fTypes.prcParse(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
