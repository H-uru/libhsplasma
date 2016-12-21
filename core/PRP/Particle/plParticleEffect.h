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

class PLASMA_DLL plParticleEffect : public hsKeyedObject {
    CREATABLE(plParticleEffect, kParticleEffect, hsKeyedObject)
};


class PLASMA_DLL plParticleCollisionEffect : public plParticleEffect {
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
};


class PLASMA_DLL plParticleCollisionEffectBeat : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectBeat, kParticleCollisionEffectBeat,
              plParticleCollisionEffect)
};


class PLASMA_DLL plParticleCollisionEffectBounce : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectBounce, kParticleCollisionEffectBounce,
              plParticleCollisionEffect)

protected:
    float fBounce, fFriction;

public:
    plParticleCollisionEffectBounce() : fBounce(0.0f), fFriction(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleCollisionEffectDie : public plParticleCollisionEffect {
    CREATABLE(plParticleCollisionEffectDie, kParticleCollisionEffectDie,
              plParticleCollisionEffect)
};


class PLASMA_DLL plParticleFadeOutEffect : public plParticleEffect {
    CREATABLE(plParticleFadeOutEffect, kParticleFadeOutEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeOutEffect() : fLength(0.0f), fIgnoreZ(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleFadeVolumeEffect : public plParticleEffect {
    CREATABLE(plParticleFadeVolumeEffect, kParticleFadeVolumeEffect,
              plParticleEffect)

protected:
    float fLength, fIgnoreZ;

public:
    plParticleFadeVolumeEffect() : fLength(0.0f), fIgnoreZ(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleFlockEffect : public plParticleEffect {
    CREATABLE(plParticleFlockEffect, kParticleFlockEffect, plParticleEffect)

protected:
    hsVector3 fTargetOffset, fDissenterTarget;
    float fInfAvgRadSq, fInfRepRadSq, fAvgVelStr, fRepDirStr;
    float fGoalOrbitStr, fGoalChaseStr, fGoalDistSq;
    float fFullChaseDistSq, fMaxOrbitSpeed, fMaxChaseSpeed;
    float fMaxParticles;

public:
    plParticleFlockEffect()
        : fInfAvgRadSq(0.0f), fInfRepRadSq(0.0f), fAvgVelStr(0.0f),
          fRepDirStr(0.0f), fGoalOrbitStr(0.0f), fGoalChaseStr(0.0f),
          fGoalDistSq(0.0f), fFullChaseDistSq(0.0f), fMaxOrbitSpeed(0.0f),
          fMaxChaseSpeed(0.0f), fMaxParticles(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleFollowSystemEffect : public plParticleEffect {
    CREATABLE(plParticleFollowSystemEffect, kParticleFollowSystemEffect,
              plParticleEffect)
};


class PLASMA_DLL plParticleWindEffect : public plParticleEffect {
    CREATABLE(plParticleWindEffect, kParticleWindEffect, plParticleEffect)

protected:
    float fStrength, fConstancy, fSwirl;
    bool fHorizontal;
    hsVector3 fRefDir, fDir;

public:
    plParticleWindEffect()
        : fStrength(0.0f), fConstancy(0.0f), fSwirl(0.0f), fHorizontal(false) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleLocalWind : public plParticleWindEffect {
    CREATABLE(plParticleLocalWind, kParticleLocalWind, plParticleWindEffect)

protected:
    hsVector3 fScale;
    float fSpeed;

public:
    plParticleLocalWind() : fSpeed(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plParticleUniformWind : public plParticleWindEffect {
    CREATABLE(plParticleUniformWind, kParticleUniformWind, plParticleWindEffect)

protected:
    float fFreqMin, fFreqMax, fFreqRate;

public:
    plParticleUniformWind() : fFreqMin(0.0f), fFreqMax(0.0f), fFreqRate(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
