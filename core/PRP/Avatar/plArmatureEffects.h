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

#ifndef _PLARMATUREEFFECTS_H
#define _PLARMATUREEFFECTS_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plArmatureEffect : public hsKeyedObject
{
    CREATABLE(plArmatureEffect, kArmatureEffect, hsKeyedObject)
};


class PLASMA_DLL plArmatureEffectFootSound : public plArmatureEffect
{
    CREATABLE(plArmatureEffectFootSound, kArmatureEffectFootSound, plArmatureEffect)

protected:
    std::vector<plKey> fMods;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plArmatureEffectsMgr : public hsKeyedObject
{
    CREATABLE(plArmatureEffectsMgr, kArmatureEffectsMgr, hsKeyedObject)

public:
    enum
    {
        kFootDirt, kFootPuddle, kFootWater, kFootTile, kFootMetal,
        kFootWoodBridge, kFootRopeLadder, kFootGrass, kFootBrush, kFootHardWood,
        kFootRug, kFootStone, kFootMud, kFootMetalLadder, kFootWoodLadder,
        kFootDeepWater, kFootMaintainerGlass, kFootMaintainerStone,
        kFootSwimming, kFootNoSurface, kMaxSurface = kFootNoSurface
    };
    static const char* const SurfaceStrings[];

protected:
    std::vector<plKey> fEffects;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
