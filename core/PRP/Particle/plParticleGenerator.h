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

#ifndef _PLPARTICLEGENERATOR_H
#define _PLPARTICLEGENERATOR_H

#include "PRP/plCreatable.h"
#include "Math/hsGeometry3.h"

class PLASMA_DLL plParticleGenerator : public plCreatable {
    CREATABLE(plParticleGenerator, kParticleGenerator, plCreatable)
};


class PLASMA_DLL plOneTimeParticleGenerator : public virtual plParticleGenerator {
    CREATABLE(plOneTimeParticleGenerator, kOneTimeParticleGenerator,
              plParticleGenerator)

protected:
    unsigned int fCount;
    hsVector3* fPosition;
    hsVector3* fDirection;
    float fXSize, fYSize, fScaleMin, fScaleMax, fPartRadsPerSecRange;

public:
    plOneTimeParticleGenerator()
        : fCount(0), fPosition(NULL), fDirection(NULL), fXSize(0.0f),
          fYSize(0.0f), fScaleMin(0.0f), fScaleMax(0.0f),
          fPartRadsPerSecRange(0.0f) { }
    virtual ~plOneTimeParticleGenerator();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void clearParticles();
};


class PLASMA_DLL plSimpleParticleGenerator : public virtual plParticleGenerator {
    CREATABLE(plSimpleParticleGenerator, kSimpleParticleGenerator,
              plParticleGenerator)

public:
    enum {
        kImmortal = 0x1,
        kDisabled = 0x2
    };

protected:
    float fParticlesPerSecond;
    unsigned int fNumSources;
    hsVector3* fInitPos;
    float* fInitPitch;
    float* fInitYaw;
    float fAngleRange, fVelMin, fVelMax, fXSize, fYSize, fScaleMin, fScaleMax;
    float fGenLife, fPartLifeMin, fPartLifeMax, fPartMassRange;
    float fPartRadsPerSecRange;

public:
    plSimpleParticleGenerator()
        : fParticlesPerSecond(0.0f), fNumSources(0), fInitPos(NULL),
          fInitPitch(NULL), fInitYaw(NULL), fAngleRange(0.0f), fVelMin(0.0f),
          fVelMax(0.0f), fXSize(0.0f), fYSize(0.0f), fScaleMin(0.0f),
          fScaleMax(0.0f), fGenLife(0.0f), fPartLifeMin(0.0f),
          fPartLifeMax(0.0f),fPartMassRange(0.0f), fPartRadsPerSecRange(0.0f) { }
    virtual ~plSimpleParticleGenerator();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void clearSources();
};

#endif
