#ifndef _PLARMATUREEFFECTS_H
#define _PLARMATUREEFFECTS_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plArmatureEffect : public hsKeyedObject {
    CREATABLE(plArmatureEffect, kArmatureEffect, hsKeyedObject)
};


DllClass plArmatureEffectFootSound : public plArmatureEffect {
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


DllClass plArmatureEffectsMgr : public hsKeyedObject {
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
