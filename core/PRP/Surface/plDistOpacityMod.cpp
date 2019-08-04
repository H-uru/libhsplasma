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

#include "plDistOpacityMod.h"

void plDistOpacityMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);
    for (size_t i=0; i<4; i++)
        fDists[i] = S->readFloat();
}

void plDistOpacityMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);
    for (size_t i=0; i<4; i++)
        S->writeFloat(fDists[i]);
}

void plDistOpacityMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("DistOpacity");
    prc->writeParam("NearTrans", fDists[0]);
    prc->writeParam("NearOpaq", fDists[1]);
    prc->writeParam("FarOpaq", fDists[2]);
    prc->writeParam("FarTrans", fDists[3]);
    prc->endTag(true);
}

void plDistOpacityMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DistOpacity") {
        fDists[0] = tag->getParam("NearTrans", "0").to_float();
        fDists[1] = tag->getParam("NearOpaq", "0").to_float();
        fDists[2] = tag->getParam("FarOpaq", "0").to_float();
        fDists[3] = tag->getParam("FarTrans", "0").to_float();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
