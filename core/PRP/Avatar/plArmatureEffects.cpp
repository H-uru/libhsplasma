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

#include "plArmatureEffects.h"
#include "Debug/plDebug.h"

void plArmatureEffectFootSound::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    unsigned char count = S->readByte();
    if (count > plArmatureEffectsMgr::kMaxSurface)
        plDebug::Warning("Too many SoundMods");
    fMods.resize(count);
    for (size_t i=0; i<count; i++)
        fMods[i] = mgr->readKey(S);
}

void plArmatureEffectFootSound::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    if (fMods.size() > plArmatureEffectsMgr::kMaxSurface)
        throw hsOutOfBoundsException(__FILE__, __LINE__);
    S->writeByte(fMods.size());
    for (size_t i=0; i<fMods.size(); i++)
        mgr->writeKey(S, fMods[i]);
}

void plArmatureEffectFootSound::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("SoundMods");
    for (size_t i=0; i<fMods.size(); i++)
        plResManager::PrcWriteKey(prc, fMods[i]);
    prc->closeTag();
}

void plArmatureEffectFootSound::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundMods") {
        fMods.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMods.size(); i++) {
            fMods[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plArmatureEffectsMgr */
const char* const plArmatureEffectsMgr::SurfaceStrings[] = {
    "Dirt", "Puddle", "Water", "Tile", "Metal", "WoodBridge", "RopeLadder",
    "Grass", "Brush", "HardWood", "Rug", "Stone", "Mud", "MetalLadder",
    "WoodLadder", "DeepWater", "Maintainer(Glass)", "Maintainer(Stone)",
    "Swimming", "(none)"
};

void plArmatureEffectsMgr::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fEffects.resize(S->readInt());
    for (size_t i=0; i<fEffects.size(); i++)
        fEffects[i] = mgr->readKey(S);
}

void plArmatureEffectsMgr::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fEffects.size());
    for (size_t i=0; i<fEffects.size(); i++)
        mgr->writeKey(S, fEffects[i]);
}

void plArmatureEffectsMgr::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Effects");
    for (size_t i=0; i<fEffects.size(); i++)
        plResManager::PrcWriteKey(prc, fEffects[i]);
    prc->closeTag();
}

void plArmatureEffectsMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Effects") {
        fEffects.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEffects.size(); i++) {
            fEffects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
