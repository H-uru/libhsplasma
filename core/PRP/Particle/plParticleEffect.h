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

class PLASMA_DLL plParticleEffect : public hsKeyedObject
{
    CREATABLE(plParticleEffect, kParticleEffect, hsKeyedObject)
};


class PLASMA_DLL plParticleCollisionEffect : public plParticleEffect
{
    CREATABLE(plParticleCollisionEffect, kParticleCollisionEffect,
              plParticleEffect)

protected:
    plKey fSceneObj;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSceneObj() const { return fSceneObj; }
    void setSceneObj(plKey obj) { fSceneObj = std::move(obj); }
};


class PLASMA_DLL plParticleCollisionEffectBeat : public plParticleCollisionEffect
{
    CREATABLE(plParticleCollisionEffectBeat, kParticleCollisionEffectBeat,
              plParticleCollisionEffect)
};


class PLASMA_DLL plParticleCollisionEffectBounce : public plParticleCollisionEffect
{
    CREATABLE(plParticleCollisionEffectBounce, kParticleCollisionEffectBounce,
              plParticleCollisionEffect)

protected:
    float fBounce, fFriction;

public:
    plParticleCollisionEffectBounce() : fBounce(), fFriction() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getBounce() const { return fBounce; }
    float getFriction() const { return fFriction; }

    void setBounce(float bounce) { fBounce = bounce; }
    void setFriction(float friction) { fFriction = friction; }
};


class PLASMA_DLL plParticleCollisionEffectDie : public plParticleCollisionEffect
{
    CREATABLE(plParticleCollisionEffectDie, kParticleCollisionEffectDie,
              plParticleCollisionEffect)
};


class PLASMA_DLL plParticleFadeOutEffect : public plParticleEffect
{
    CREATABLE(plParticleFadeOutEffect, kParticleFadeOutEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeOutEffect() : fLength(), fIgnoreZ() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getLength() const { return fLength; }
    float getIgnoreZ() const { return fIgnoreZ; }

    void setLength(float length) { fLength = length; }
    void setIgnoreZ(float iz) { fIgnoreZ = iz; }
};


class PLASMA_DLL plParticleFadeVolumeEffect : public plParticleEffect
{
    CREATABLE(plParticleFadeVolumeEffect, kParticleFadeVolumeEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeVolumeEffect() : fLength(), fIgnoreZ() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getLength() const { return fLength; }
    float getIgnoreZ() const { return fIgnoreZ; }

    void setLength(float length) { fLength = length; }
    void setIgnoreZ(float iz) { fIgnoreZ = iz; }
};


class PLASMA_DLL plParticleFlockEffect : public plParticleEffect
{
    CREATABLE(plParticleFlockEffect, kParticleFlockEffect, plParticleEffect)

protected:
    hsVector3 fTargetOffset, fDissenterTarget;
    float fInfAvgRadSq, fInfRepRadSq, fAvgVelStr, fRepDirStr;
    float fGoalOrbitStr, fGoalChaseStr, fGoalDistSq;
    float fFullChaseDistSq, fMaxOrbitSpeed, fMaxChaseSpeed;
    float fMaxParticles;

public:
    plParticleFlockEffect()
        : fInfAvgRadSq(), fInfRepRadSq(), fAvgVelStr(),
          fRepDirStr(), fGoalOrbitStr(), fGoalChaseStr(),
          fGoalDistSq(), fFullChaseDistSq(), fMaxOrbitSpeed(),
          fMaxChaseSpeed(), fMaxParticles() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getTargetOffset() const { return fTargetOffset; }
    hsVector3 getDissenterTarget() const { return fDissenterTarget; }
    float getInfAvgRadSq() const { return fInfAvgRadSq; }
    float getInfRepRadSq() const { return fInfRepRadSq; }
    float getAvgVelStr() const { return fAvgVelStr; }
    float getRepDirStr() const { return fRepDirStr; }
    float getGoalOrbitStr() const { return fGoalOrbitStr; }
    float getGoalChaseStr() const { return fGoalChaseStr; }
    float getGoalDistSq() const { return fGoalDistSq; }
    float getFullChaseDistSq() const { return fFullChaseDistSq; }
    float getMaxOrbitSpeed() const { return fMaxOrbitSpeed; }
    float getMaxChaseSpeed() const { return fMaxChaseSpeed; }
    float getMaxParticles() const { return fMaxParticles; }

    void setTargetOffset(const hsVector3& offset) { fTargetOffset = offset; }
    void setDissenterTarget(const hsVector3& target) { fDissenterTarget = target; }
    void setInfAvgRadSq(float radsq) { fInfAvgRadSq = radsq; }
    void setInfRepRadSq(float radsq) { fInfRepRadSq = radsq; }
    void setAvgVelStr(float str) { fAvgVelStr = str; }
    void setRepDirStr(float str) { fRepDirStr = str; }
    void setGoalOrbitStr(float str) { fGoalOrbitStr = str; }
    void setGoalChaseStr(float str) { fGoalChaseStr = str; }
    void setGoalDistSq(float distsq) { fGoalDistSq = distsq; }
    void setFullChaseDistSq(float distsq) { fFullChaseDistSq = distsq; }
    void setMaxOrbitSpeed(float speed) { fMaxOrbitSpeed = speed; }
    void setMaxChaseSpeed(float speed) { fMaxChaseSpeed = speed; }
    void setMaxParticles(float maxParticles) { fMaxParticles = maxParticles; }
};


class PLASMA_DLL plParticleFollowSystemEffect : public plParticleEffect
{
    CREATABLE(plParticleFollowSystemEffect, kParticleFollowSystemEffect,
              plParticleEffect)
};


class PLASMA_DLL plParticleWindEffect : public plParticleEffect
{
    CREATABLE(plParticleWindEffect, kParticleWindEffect, plParticleEffect)

protected:
    float fStrength, fConstancy, fSwirl;
    bool fHorizontal;
    hsVector3 fRefDir, fDir;

public:
    plParticleWindEffect()
        : fStrength(), fConstancy(), fSwirl(), fHorizontal() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getStrength() const { return fStrength; }
    float getConstancy() const { return fConstancy; }
    float getSwirl() const { return fSwirl; }
    bool isHorizontal() const { return fHorizontal; }
    hsVector3 getRefDir() const { return fRefDir; }
    hsVector3 getDir() const { return fDir; }

    void setStrength(float strength) { fStrength = strength; }
    void setConstancy(float constancy) { fConstancy = constancy; }
    void setSwirl(float swirl) { fSwirl = swirl; }
    void setHorizontal(bool horiz) { fHorizontal = horiz; }
    void setRefDir(const hsVector3& dir) { fRefDir = dir; }
    void setDir(const hsVector3& dir) { fDir = dir; }
};


class PLASMA_DLL plParticleLocalWind : public plParticleWindEffect
{
    CREATABLE(plParticleLocalWind, kParticleLocalWind, plParticleWindEffect)

protected:
    hsVector3 fScale;
    float fSpeed;

public:
    plParticleLocalWind() : fSpeed() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getScale() const { return fScale; }
    float getSpeed() const { return fSpeed; }

    void setScale(const hsVector3& scale) { fScale = scale; }
    void setSpeed(float speed) { fSpeed = speed; }
};


class PLASMA_DLL plParticleUniformWind : public plParticleWindEffect
{
    CREATABLE(plParticleUniformWind, kParticleUniformWind, plParticleWindEffect)

protected:
    float fFreqMin, fFreqMax, fFreqRate;

public:
    plParticleUniformWind() : fFreqMin(), fFreqMax(), fFreqRate() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getFreqMin() const { return fFreqMin; }
    float getFreqMax() const { return fFreqMax; }
    float getFreqRate() const { return fFreqRate; }

    void setFreqMin(float fmin) { fFreqMin = fmin; }
    void setFreqMax(float fmax) { fFreqMax = fmax; }
    void setFreqRate(float rate) { fFreqRate = rate; }
};

#endif
