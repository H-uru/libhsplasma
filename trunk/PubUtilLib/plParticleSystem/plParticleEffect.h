#ifndef _PLPARTICLEEFFECT_H
#define _PLPARTICLEEFFECT_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
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
    //plConvexVolume* fBounds;

public:
    plParticleCollisionEffect();
    virtual ~plParticleCollisionEffect();

    DECLARE_CREATABLE(plParticleCollisionEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plParticleFadeVolumeEffect : public plParticleEffect {
protected:
    hsPoint3 fMax, fMin, fNorm;
    float fLength, fIgnoreZ;

public:
    plParticleFadeVolumeEffect();
    virtual ~plParticleFadeVolumeEffect();

    DECLARE_CREATABLE(plParticleFadeVolumeEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plParticleFlockEffect : public plParticleEffect {
protected:
    hsPoint3 fTargetOffset, fDissenterTarget;
    float fInfAvgRadSq, fInfRepRadSq, fAvgVelStr, fRepDirStr;
    float fGoalOrbitStr, fGoalChaseStr, fGoalDistSq;
    float fFullChaseDistSq, fMaxOrbitSpeed, fMaxChaseSpeed;
    unsigned short fMaxParticles;
    float fDistSq;
    //plParticleInfluenceInfo* fInfluences;

public:
    plParticleFlockEffect();
    virtual ~plParticleFlockEffect();

    DECLARE_CREATABLE(plParticleFlockEffect)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plParticleFollowSystemEffect : public plParticleEffect {
protected:
    //hsMatrix44 fOldW2L;
    //bool fEvalThisFrame;

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
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
