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

DllClass plParticleGenerator : public plCreatable {
    CREATABLE(plParticleGenerator, kParticleGenerator, plCreatable)
};


DllClass plOneTimeParticleGenerator : public virtual plParticleGenerator {
    CREATABLE(plOneTimeParticleGenerator, kOneTimeParticleGenerator,
              plParticleGenerator)

protected:
    unsigned int fCount;
    hsVector3* fPosition;
    hsVector3* fDirection;
    float fXSize, fYSize, fScaleMin, fScaleMax, fPartRadsPerSecRange;

public:
    plOneTimeParticleGenerator();
    virtual ~plOneTimeParticleGenerator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearParticles();
};


DllClass plSimpleParticleGenerator : public virtual plParticleGenerator {
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
    plSimpleParticleGenerator();
    virtual ~plSimpleParticleGenerator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearSources();
};

#endif
