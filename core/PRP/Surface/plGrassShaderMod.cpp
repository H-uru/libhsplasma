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

#include "plGrassShaderMod.h"

/* plGrassWave */
void plGrassWave::read(hsStream* S) {
    fDistX = S->readFloat();
    fDistY = S->readFloat();
    fDistZ = S->readFloat();
    fDirX = S->readFloat();
    fDirY = S->readFloat();
    fSpeed = S->readFloat();
}

void plGrassWave::write(hsStream* S) {
    S->writeFloat(fDistX);
    S->writeFloat(fDistY);
    S->writeFloat(fDistZ);
    S->writeFloat(fDirX);
    S->writeFloat(fDirY);
    S->writeFloat(fSpeed);
}

void plGrassWave::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGrassWave");
    prc->writeParam("DistX", fDistX);
    prc->writeParam("DistY", fDistY);
    prc->writeParam("DistZ", fDistZ);
    prc->writeParam("DirX", fDirX);
    prc->writeParam("DirY", fDirY);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plGrassWave::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plGrassWave")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDistX = tag->getParam("DistX", "0").toFloat();
    fDistY = tag->getParam("DistY", "0").toFloat();
    fDistZ = tag->getParam("DistZ", "0").toFloat();
    fDirX = tag->getParam("DirX", "0").toFloat();
    fDirY = tag->getParam("DirY", "0").toFloat();
    fSpeed = tag->getParam("Speed", "0").toFloat();
}


/* plGrassShaderMod */
void plGrassShaderMod::read(hsStream* S, plResManager* mgr) {
    plModifier::read(S, mgr);

    fMaterial = mgr->readKey(S);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].read(S);
}

void plGrassShaderMod::write(hsStream* S, plResManager* mgr) {
    plModifier::write(S, mgr);

    mgr->writeKey(S, fMaterial);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].write(S);
}

void plGrassShaderMod::IPrcWrite(pfPrcHelper* prc) {
    plModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Material");
    fMaterial->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Waves");
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].prcWrite(prc);
    prc->closeTag();
}

void plGrassShaderMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Waves") {
        if (tag->countChildren() != kNumWaves)
            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of waves");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<kNumWaves; i++) {
            fWaves[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plModifier::IPrcParse(tag, mgr);
    }
}
