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

#include "hsGMatState.h"

hsGMatState::hsGMatState(unsigned int blend, unsigned int clamp,
                         unsigned int shade, unsigned int Z,
                         unsigned int misc)
{
    fBlendFlags = blend;
    fClampFlags = clamp;
    fShadeFlags = shade;
    fZFlags = Z;
    fMiscFlags = misc;
}

void hsGMatState::read(hsStream* S)
{
    fBlendFlags = S->readInt();
    fClampFlags = S->readInt();
    fShadeFlags = S->readInt();
    fZFlags = S->readInt();
    fMiscFlags = S->readInt();
}

void hsGMatState::write(hsStream* S)
{
    S->writeInt(fBlendFlags);
    S->writeInt(fClampFlags);
    S->writeInt(fShadeFlags);
    S->writeInt(fZFlags);
    S->writeInt(fMiscFlags);
}

void hsGMatState::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsGMatState");
    prc->writeParamHex("BlendFlags", fBlendFlags);
    prc->writeParamHex("ClampFlags", fClampFlags);
    prc->writeParamHex("ShadeFlags", fShadeFlags);
    prc->writeParamHex("ZFlags", fZFlags);
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);
}

void hsGMatState::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsGMatState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fBlendFlags = tag->getParam("BlendFlags", "0").to_uint();
    fClampFlags = tag->getParam("ClampFlags", "0").to_uint();
    fShadeFlags = tag->getParam("ShadeFlags", "0").to_uint();
    fZFlags = tag->getParam("ZFlags", "0").to_uint();
    fMiscFlags = tag->getParam("MiscFlags", "0").to_uint();
}
