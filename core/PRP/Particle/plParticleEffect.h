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

#ifndef _PLPARTICLEEFFECT_H
#define _PLPARTICLEEFFECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "plBoundInterface.h"

DllClass plParticleEffect : public virtual hsKeyedObject {
    CREATABLE(plParticleEffect, kParticleEffect, hsKeyedObject)
};


DllClass plParticleCollisionEffect : public virtual plParticleEffect {
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


DllClass plParticleCollisionEffectBounce : public virtual plParticleCollisionEffect {
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


DllClass plParticleCollisionEffectDie : public virtual plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectDie, kParticleCollisionEffectDie,
              plParticleCollisionEffect)
};


DllClass plParticleFadeOutEffect : public virtual plParticleEffect {
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


DllClass plParticleFadeVolumeEffect : public virtual plParticleEffect {
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


DllClass plParticleFlockEffect : public virtual plParticleEffect {
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


DllClass plParticleFollowSystemEffect : public virtual plParticleEffect {
    CREATABLE(plParticleFollowSystemEffect, kParticleFollowSystemEffect,
              plParticleEffect)
};


DllClass plParticleWindEffect : public virtual plParticleEffect {
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


DllClass plParticleLocalWind : public virtual plParticleWindEffect {
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


DllClass plParticleUniformWind : public virtual plParticleWindEffect {
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
