#ifndef _PLPARTICLESYSTEM_H
#define _PLPARTICLESYSTEM_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "PubUtilLib/plInterp/plController.h"
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
    plKey fTarget, fMaterial;
    unsigned int fXTiles, fYTiles;
    double fCurrTime, fLastTime;
    hsVector3 fAccel;
    float fPreSim, fDrag, fWindMult;
    unsigned int fMaxTotalParticles, fMaxTotalParticlesLeft;
    unsigned int fNumValidEmitters, fMaxEmitters, fNextEmitter;
    plParticleEmitter** fEmitters;
    hsTArray<plKey> fForces, fEffects, fConstraints;
    //plParticleContext fContext;
    hsTArray<plKey> fPermaLights;
    plController* fAmbientCtl;
    plController* fDiffuseCtl;
    plController* fOpacityCtl;
    plController* fWidthCtl;
    plController* fHeightCtl;
    //plParticleSDLMod* fParticleSDLMod;

public:
    plParticleSystem();
    virtual ~plParticleSystem();

    DECLARE_CREATABLE(plParticleSystem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
