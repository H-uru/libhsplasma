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

#ifndef _PLPARTICLEEMITTER_H
#define _PLPARTICLEEMITTER_H

#include "PRP/plCreatable.h"
#include "PRP/Region/hsBounds.h"
#include "ResManager/plResManager.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "plParticleGenerator.h"

class PLASMA_DLL plParticleEmitter : public plCreatable
{
    CREATABLE(plParticleEmitter, kParticleEmitter, plCreatable)

public:
    enum
    {
        kMatIsEmissive = 0x1,
        kNormalUp = 0x10,
        kNormalVelUpVel = 0x20,
        kNormalFromCenter = 0x40,
        kNormalDynamicMask = kNormalFromCenter | kNormalVelUpVel,
        kNormalPrecalcMask = kNormalDynamicMask | kNormalUp,
        kNormalViewFacing = 0x100,
        kNormalNearestLight = 0x200,
        kNeedsUpdate = 0x1000000,
        kBorrowedGenerator = 0x2000000,
        kOverrideLocalToWorld = 0x4000000,
        kOnReserve = 0x8000000,
        kOrientationUp = 0x10000000,
        kOrientationVelocityBased = 0x20000000,
        kOrientationVelocityStretch = 0x40000000,
        kOrientationVelocityFlow = 0x80000000,
        kOrientationVelocityMask =
            kOrientationVelocityFlow | kOrientationVelocityStretch |
            kOrientationVelocityBased,
        kOrientationMask = kOrientationVelocityMask | kOrientationUp
    };

protected:
    uint32_t fMiscFlags, fSpanIndex, fMaxParticles;
    plParticleGenerator* fGenerator;
    hsColorRGBA fColor;

public:
    plParticleEmitter()
        : fMiscFlags(), fSpanIndex(), fMaxParticles(), fGenerator() { }
    ~plParticleEmitter();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    uint32_t getMiscFlags() const { return fMiscFlags; }
    uint32_t getSpanIndex() const { return fSpanIndex; }
    uint32_t getMaxParticles() const { return fMaxParticles; }
    plParticleGenerator* getGenerator() const { return fGenerator; }
    hsColorRGBA getColor() const { return fColor; }

    void setMiscFlags(uint32_t flags) { fMiscFlags = flags; }
    void setSpanIndex(uint32_t index) { fSpanIndex = index; }
    void setMaxParticles(uint32_t particles) { fMaxParticles = particles; }
    void setGenerator(plParticleGenerator* generator);
    void setColor(const hsColorRGBA& color) { fColor = color; }
};

#endif
