#ifndef _PLPARTICLESYSTEM_H
#define _PLPARTICLESYSTEM_H

#include "PRP/Object/plSynchedObject.h"
#include "PRP/Animation/plController.h"
#include "plParticleEmitter.h"

DllClass plParticleSystem : public plSynchedObject {
public:
    enum EffectType {
        kEffectForce = 0x1,
        kEffectMisc = 0x2,
        kEffectConstraint = 0x4
    };

    enum MiscFlags {
        kParticleSystemAlwaysUpdate = 0x1
    };

protected:
    plKey fMaterial;
    unsigned int fXTiles, fYTiles;
    hsVector3 fAccel;
    float fPreSim, fDrag, fWindMult;
    unsigned int fMaxTotalParticles, fNumValidEmitters, fMaxEmitters;
    plParticleEmitter** fEmitters;
    hsTArray<plKey> fForces, fEffects, fConstraints;
    hsTArray<plKey> fPermaLights;
    plController* fAmbientCtl;
    plController* fDiffuseCtl;
    plController* fOpacityCtl;
    plController* fWidthCtl;
    plController* fHeightCtl;

public:
    plParticleSystem();
    virtual ~plParticleSystem();

    DECLARE_CREATABLE(plParticleSystem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
