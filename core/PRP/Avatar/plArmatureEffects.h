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

DllClass plArmatureEffect : public virtual hsKeyedObject {
    CREATABLE(plArmatureEffect, kArmatureEffect, hsKeyedObject)
};


DllClass plArmatureEffectFootSound : public virtual plArmatureEffect {
    CREATABLE(plArmatureEffectFootSound, kArmatureEffectFootSound, plArmatureEffect)

protected:
    hsTArray<plKey> fMods;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plArmatureEffectsMgr : public virtual hsKeyedObject {
    CREATABLE(plArmatureEffectsMgr, kArmatureEffectsMgr, hsKeyedObject)

public:
    enum {
        kFootDirt, kFootPuddle, kFootWater, kFootTile, kFootMetal,
        kFootWoodBridge, kFootRopeLadder, kFootGrass, kFootBrush, kFootHardWood,
        kFootRug, kFootStone, kFootMud, kFootMetalLadder, kFootWoodLadder,
        kFootDeepWater, kFootMaintainerGlass, kFootMaintainerStone,
        kFootSwimming, kFootNoSurface, kMaxSurface = kFootNoSurface
    };
    static const char* const SurfaceStrings[];

protected:
    hsTArray<plKey> fEffects;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
