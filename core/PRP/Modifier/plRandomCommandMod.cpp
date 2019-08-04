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

#include "plRandomCommandMod.h"

void plRandomCommandMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fMode = S->readByte();
    fState = S->readByte();
    fMinDelay = S->readFloat();
    fMaxDelay = S->readFloat();
}

void plRandomCommandMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeByte(fMode);
    S->writeByte(fState);
    S->writeFloat(fMinDelay);
    S->writeFloat(fMaxDelay);
}

void plRandomCommandMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("RandomCommandParams");
    prc->writeParam("Mode", fMode);
    prc->writeParam("State", fState);
    prc->writeParam("MinDelay", fMinDelay);
    prc->writeParam("MaxDelay", fMaxDelay);
    prc->endTag(true);
}

void plRandomCommandMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "RandomCommandParams") {
        fMode = tag->getParam("Mode", "0").to_uint();
        fState = tag->getParam("State", "0").to_uint();
        fMinDelay = tag->getParam("MinDelay", "0").to_float();
        fMaxDelay = tag->getParam("MaxDelay", "0").to_float();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
