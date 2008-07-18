#ifndef _PLPARTICLEEFFECT_H
#define _PLPARTICLEEFFECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "plBoundInterface.h"

DllClass plParticleEffect : public hsKeyedObject {
public:
    plParticleEffect();
    virtual ~plParticleEffect();

    DECLARE_CREATABLE(plParticleEffect)
};

DllClass plParticleCollisionEffect : public plParticleEffect {
protected:
    plKey fSceneObj;

public:
    plParticleCollisionEffect();
    virtual ~plParticleCollisionEffect();

    DECLARE_CREATABLE(plParticleCollisionEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleCollisionEffectBeat : public plParticleCollisionEffect {
public:
    plParticleCollisionEffectBeat();
    virtual ~plParticleCollisionEffectBeat();

    DECLARE_CREATABLE(plParticleCollisionEffectBeat)
};

DllClass plParticleCollisionEffectBounce : public plParticleCollisionEffect {
protected:
    float fBounce, fFriction;

public:
    plParticleCollisionEffectBounce();
    virtual ~plParticleCollisionEffectBounce();

    DECLARE_CREATABLE(plParticleCollisionEffectBounce)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleCollisionEffectDie : public plParticleCollisionEffect {
public:
    plParticleCollisionEffectDie();
    virtual ~plParticleCollisionEffectDie();

    DECLARE_CREATABLE(plParticleCollisionEffectDie)
};

DllClass plParticleFadeOutEffect : public plParticleEffect {
protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeOutEffect();
    virtual ~plParticleFadeOutEffect();

    DECLARE_CREATABLE(plParticleFadeOutEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleFadeVolumeEffect : public plParticleEffect {
protected:
    hsVector3 fMax, fMin, fNorm;
    float fLength, fIgnoreZ;

public:
    plParticleFadeVolumeEffect();
    virtual ~plParticleFadeVolumeEffect();

    DECLARE_CREATABLE(plParticleFadeVolumeEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleFlockEffect : public plParticleEffect {
protected:
    hsVector3 fTargetOffset, fDissenterTarget;
    float fInfAvgRadSq, fInfRepRadSq, fAvgVelStr, fRepDirStr;
    float fGoalOrbitStr, fGoalChaseStr, fGoalDistSq;
    float fFullChaseDistSq, fMaxOrbitSpeed, fMaxChaseSpeed;
    float fMaxParticles, fDistSq;

public:
    plParticleFlockEffect();
    virtual ~plParticleFlockEffect();

    DECLARE_CREATABLE(plParticleFlockEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleFollowSystemEffect : public plParticleEffect {
public:
    plParticleFollowSystemEffect();
    virtual ~plParticleFollowSystemEffect();

    DECLARE_CREATABLE(plParticleFollowSystemEffect)
};

DllClass plParticleWindEffect : public plParticleEffect {
protected:
    float fStrength, fConstancy, fSwirl;
    bool fHorizontal;
    hsVector3 fRefDir, fWindVec, fRandDir, fDir;
    double fLastDirSecs;

public:
    plParticleWindEffect();
    virtual ~plParticleWindEffect();

    DECLARE_CREATABLE(plParticleWindEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleLocalWind : public plParticleWindEffect {
protected:
    hsVector3 fScale;
    float fSpeed;
    hsVector3 fPhase, fInvScale;
    double fLastPhaseSecs;

public:
    plParticleLocalWind();
    virtual ~plParticleLocalWind();

    DECLARE_CREATABLE(plParticleLocalWind)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plParticleUniformWind : public plParticleWindEffect {
protected:
    float fFreqMin, fFreqMax, fFreqCurr, fFreqRate;
    double fCurrPhase, fLastFreqSecs;
    float fCurrentStrength;

public:
    plParticleUniformWind();
    virtual ~plParticleUniformWind();

    DECLARE_CREATABLE(plParticleUniformWind)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
