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

#include "plFogEnvironment.h"

const char* const plFogEnvironment::FogTypeNames[] = {
    "Linear", "Exp", "Exp2", "None"
};

void plFogEnvironment::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);
    fType = S->readByte();
    fStart = S->readFloat();
    fEnd = S->readFloat();
    fDensity = S->readFloat();
    fColor.read(S);
}

void plFogEnvironment::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);
    S->writeByte(fType);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);
    S->writeFloat(fDensity);
    fColor.write(S);
}

void plFogEnvironment::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("FogParams");
    prc->writeParam("Type", FogTypeNames[fType]);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->writeParam("Density", fDensity);
    prc->endTag(true);

    prc->writeSimpleTag("Color");
    fColor.prcWrite(prc);
    prc->closeTag();
}

void plFogEnvironment::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FogParams") {
        ST::string fogTypeName = tag->getParam("Type", "");
        fType = kNoFog;
        for (size_t i=0; i<=kNoFog; i++) {
            if (fogTypeName == FogTypeNames[i])
                fType = i;
        }
        fStart = tag->getParam("Start", "0").to_float();
        fEnd = tag->getParam("End", "0").to_float();
        fDensity = tag->getParam("Density", "0").to_float();
    } else if (tag->getName() == "Color") {
        if (tag->hasChildren())
            fColor.prcParse(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
