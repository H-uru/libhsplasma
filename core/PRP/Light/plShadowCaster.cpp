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

#include "plShadowCaster.h"

void plShadowCaster::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);

    fCastFlags = S->readByte();
    fBoost = S->readFloat();
    fAttenScale = S->readFloat();
    fBlurScale = S->readFloat();
}

void plShadowCaster::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);

    S->writeByte(fCastFlags);
    S->writeFloat(fBoost);
    S->writeFloat(fAttenScale);
    S->writeFloat(fBlurScale);
}

void plShadowCaster::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("CastParams");
    prc->writeParamHex("Flags", fCastFlags);
    prc->writeParam("Boost", fBoost);
    prc->writeParam("AttenScale", fAttenScale);
    prc->writeParam("BlurScale", fBlurScale);
    prc->endTag(true);
}

void plShadowCaster::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CastParams") {
        fCastFlags = tag->getParam("Flags", "0").to_uint();
        fBoost = tag->getParam("Boost", "0").to_float();
        fAttenScale = tag->getParam("AttenScale", "0").to_float();
        fBlurScale = tag->getParam("BlurScale", "0").to_float();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
