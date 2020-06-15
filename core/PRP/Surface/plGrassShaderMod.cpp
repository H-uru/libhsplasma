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
void plGrassWave::read(hsStream* S)
{
    fDist.read(S);
    fDirX = S->readFloat();
    fDirY = S->readFloat();
    fSpeed = S->readFloat();
}

void plGrassWave::write(hsStream* S)
{
    fDist.write(S);
    S->writeFloat(fDirX);
    S->writeFloat(fDirY);
    S->writeFloat(fSpeed);
}

void plGrassWave::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plGrassWave");
    prc->writeParam("DistX", fDist.X);
    prc->writeParam("DistY", fDist.Y);
    prc->writeParam("DistZ", fDist.Z);
    prc->writeParam("DirX", fDirX);
    prc->writeParam("DirY", fDirY);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plGrassWave::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plGrassWave")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDist.X = tag->getParam("DistX", "0").to_float();
    fDist.Y = tag->getParam("DistY", "0").to_float();
    fDist.Z = tag->getParam("DistZ", "0").to_float();
    fDirX = tag->getParam("DirX", "0").to_float();
    fDirY = tag->getParam("DirY", "0").to_float();
    fSpeed = tag->getParam("Speed", "0").to_float();
}


/* plGrassShaderMod */
void plGrassShaderMod::read(hsStream* S, plResManager* mgr)
{
    plModifier::read(S, mgr);

    fMaterial = mgr->readKey(S);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].read(S);
}

void plGrassShaderMod::write(hsStream* S, plResManager* mgr)
{
    plModifier::write(S, mgr);

    mgr->writeKey(S, fMaterial);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].write(S);
}

void plGrassShaderMod::IPrcWrite(pfPrcHelper* prc)
{
    plModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Material");
    plResManager::PrcWriteKey(prc, fMaterial);
    prc->closeTag();

    prc->writeSimpleTag("Waves");
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].prcWrite(prc);
    prc->closeTag();
}

void plGrassShaderMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
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

plGrassWave& plGrassShaderMod::getWave(size_t idx)
{
    if (idx < kNumWaves)
        return fWaves[idx];
    throw hsOutOfBoundsException(__FILE__, __LINE__);
}

const plGrassWave& plGrassShaderMod::getWave(size_t idx) const
{
    if (idx < kNumWaves)
        return fWaves[idx];
    throw hsOutOfBoundsException(__FILE__, __LINE__);
}
