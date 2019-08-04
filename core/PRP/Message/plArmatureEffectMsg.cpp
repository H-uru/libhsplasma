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

#include "plArmatureEffectMsg.h"

void plArmatureEffectStateMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fSurface = S->readByte();
    fAddSurface = S->readBool();
}

void plArmatureEffectStateMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeByte(fSurface);
    S->writeBool(fAddSurface);
}

void plArmatureEffectStateMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("ArmatureEffectState");
    prc->writeParam("Surface", fSurface);
    prc->writeParam("Add", fAddSurface);
    prc->endTag(true);
}

void plArmatureEffectStateMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ArmatureEffectState") {
        fSurface = tag->getParam("Surface", "0").to_int();
        fAddSurface = tag->getParam("AddSurface", "false").to_bool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
