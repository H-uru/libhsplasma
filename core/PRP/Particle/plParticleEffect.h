#ifndef _PLPARTICLEEFFECT_H
#define _PLPARTICLEEFFECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "plBoundInterface.h"

DllClass plParticleEffect : public hsKeyedObject {
    CREATABLE(plParticleEffect, kParticleEffect, hsKeyedObject)
};


DllClass plParticleCollisionEffect : public plParticleEffect {
    CREATABLE(plParticleCollisionEffect, kParticleCollisionEffect,
              plParticleEffect)

protected:
    plKey fSceneObj;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleCollisionEffectBeat : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectBeat, kParticleCollisionEffectBeat,
              plParticleCollisionEffect)
};


DllClass plParticleCollisionEffectBounce : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectBounce, kParticleCollisionEffectBounce,
              plParticleCollisionEffect)

protected:
    float fBounce, fFriction;

public:
    plParticleCollisionEffectBounce();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleCollisionEffectDie : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectDie, kParticleCollisionEffectDie,
              plParticleCollisionEffect)
};


DllClass plParticleFadeOutEffect : public plParticleEffect {
    CREATABLE(plParticleFadeOutEffect, kParticleFadeOutEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeOutEffect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleFadeVolumeEffect : public plParticleEffect {
    CREATABLE(plParticleFadeVolumeEffect, kParticleFadeVolumeEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeVolumeEffect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleFlockEffect : public plParticleEffect {
    CREATABLE(plParticleFlockEffect, kParticleFlockEffect, plParticleEffect)

protected:
    hsVector3 fTargetOffset, fDissenterTarget;
    float fInfAvgRadSq, fInfRepRadSq, fAvgVelStr, fRepDirStr;
    float fGoalOrbitStr, fGoalChaseStr, fGoalDistSq;
    float fFullChaseDistSq, fMaxOrbitSpeed, fMaxChaseSpeed;
    float fMaxParticles;

public:
    plParticleFlockEffect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleFollowSystemEffect : public plParticleEffect {
    CREATABLE(plParticleFollowSystemEffect, kParticleFollowSystemEffect,
              plParticleEffect)
};


DllClass plParticleWindEffect : public plParticleEffect {
    CREATABLE(plParticleWindEffect, kParticleWindEffect, plParticleEffect)

protected:
    float fStrength, fConstancy, fSwirl;
    bool fHorizontal;
    hsVector3 fRefDir, fDir;

public:
    plParticleWindEffect();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleLocalWind : public plParticleWindEffect {
    CREATABLE(plParticleLocalWind, kParticleLocalWind, plParticleWindEffect)

protected:
    hsVector3 fScale;
    float fSpeed;

public:
    plParticleLocalWind();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plParticleUniformWind : public plParticleWindEffect {
    CREATABLE(plParticleUniformWind, kParticleUniformWind, plParticleWindEffect)

protected:
    float fFreqMin, fFreqMax, fFreqRate;

public:
    plParticleUniformWind();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
