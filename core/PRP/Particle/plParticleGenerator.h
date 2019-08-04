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

class PLASMA_DLL plParticleGenerator : public plCreatable
{
    CREATABLE(plParticleGenerator, kParticleGenerator, plCreatable)
};


class PLASMA_DLL plOneTimeParticleGenerator : public plParticleGenerator
{
    CREATABLE(plOneTimeParticleGenerator, kOneTimeParticleGenerator,
              plParticleGenerator)

protected:
    std::vector<hsVector3> fPosition;
    std::vector<hsVector3> fDirection;
    float fXSize, fYSize, fScaleMin, fScaleMax, fPartRadsPerSecRange;

public:
    plOneTimeParticleGenerator()
        : fXSize(), fYSize(), fScaleMin(), fScaleMax(),
          fPartRadsPerSecRange() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<hsVector3>& getPosition() const { return fPosition; }
    const std::vector<hsVector3>& getDirection() const { return fDirection; }
    float getXSize() const { return fXSize; }
    float getYSize() const { return fYSize; }
    float getScaleMin() const { return fScaleMin; }
    float getScaleMax() const { return fScaleMax; }
    float getPartRadsPerSecRange() const { return fPartRadsPerSecRange; }

    void setPosition(const std::vector<hsVector3>& pos) { fPosition = pos; }
    void setDirection(const std::vector<hsVector3>& dir) { fDirection = dir; }
    void setXSize(float size) { fXSize = size; }
    void setYSize(float size) { fYSize = size; }
    void setScaleMin(float min) { fScaleMin = min; }
    void setScaleMax(float max) { fScaleMax = max; }
    void setPartRadsPerSecRange(float range) { fPartRadsPerSecRange = range; }
};


class PLASMA_DLL plSimpleParticleGenerator : public plParticleGenerator
{
    CREATABLE(plSimpleParticleGenerator, kSimpleParticleGenerator,
              plParticleGenerator)

public:
    enum
    {
        kImmortal = 0x1,
        kDisabled = 0x2
    };

protected:
    float fParticlesPerSecond;
    std::vector<hsVector3> fInitPos;
    std::vector<float> fInitPitch;
    std::vector<float> fInitYaw;
    float fAngleRange, fVelMin, fVelMax, fXSize, fYSize, fScaleMin, fScaleMax;
    float fGenLife, fPartLifeMin, fPartLifeMax, fPartMassRange;
    float fPartRadsPerSecRange;

public:
    plSimpleParticleGenerator()
        : fParticlesPerSecond(), fAngleRange(), fVelMin(), fVelMax(),
          fXSize(), fYSize(), fScaleMin(), fScaleMax(), fGenLife(),
          fPartLifeMin(), fPartLifeMax(), fPartMassRange(),
          fPartRadsPerSecRange() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getParticlesPerSecond() const { return fParticlesPerSecond; }
    const std::vector<hsVector3>& getInitPos() const { return fInitPos; }
    const std::vector<float>& getInitPitch() const { return fInitPitch; }
    const std::vector<float>& getInitYaw() const { return fInitYaw; }
    float getAngleRange() const { return fAngleRange; }
    float getVelMin() const { return fVelMin; }
    float getVelMax() const { return fVelMax; }
    float getXSize() const { return fXSize; }
    float getYSize() const { return fYSize; }
    float getScaleMin() const { return fScaleMin; }
    float getScaleMax() const { return fScaleMax; }
    float getGenLife() const { return fGenLife; }
    float getPartLifeMin() const { return fPartLifeMin; }
    float getPartLifeMax() const { return fPartLifeMax; }
    float getPartMassRange() const { return fPartMassRange; }
    float getPartRadsPerSecRange() const { return fPartRadsPerSecRange; }

    void setParticlesPerSecond(float pps) { fParticlesPerSecond = pps; }
    void setInitPos(const std::vector<hsVector3>& pos) { fInitPos = pos; }
    void setInitPitch(const std::vector<float>& pitch) { fInitPitch = pitch; }
    void setInitYaw(const std::vector<float>& yaw) { fInitYaw = yaw; }
    void setAngleRange(float range) { fAngleRange = range; }
    void setVelMin(float vel) { fVelMin = vel; }
    void setVelMax(float vel) { fVelMax = vel; }
    void setXSize(float size) { fXSize = size; }
    void setYSize(float size) { fYSize = size; }
    void setScaleMin(float scale) { fScaleMin = scale; }
    void setScaleMax(float scale) { fScaleMax = scale; }
    void setGenLife(float life) { fGenLife = life; }
    void setPartLifeMin(float life) { fPartLifeMin = life; }
    void setPartLifeMax(float life) { fPartLifeMax = life; }
    void setPartMassRange(float range) { fPartMassRange = range; }
    void setPartRadsPerSecRange(float range) { fPartRadsPerSecRange = range; }
};

#endif
