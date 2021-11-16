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

#ifndef _PLPARTICLEAPPLICATOR_H
#define _PLPARTICLEAPPLICATOR_H

#include "PRP/Avatar/plAGApplicator.h"

class HSPLASMA_EXPORT plParticleApplicator : public plAGApplicator
{
    CREATABLE(plParticleApplicator, kParticleApplicator, plAGApplicator)
};


class HSPLASMA_EXPORT plParticleAngleApplicator : public plParticleApplicator
{
    CREATABLE(plParticleAngleApplicator, kParticleAngleApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleLifeMinApplicator : public plParticleApplicator
{
    CREATABLE(plParticleLifeMinApplicator, kParticleLifeMinApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleLifeMaxApplicator : public plParticleApplicator
{
    CREATABLE(plParticleLifeMaxApplicator, kParticleLifeMaxApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticlePPSApplicator : public plParticleApplicator
{
    CREATABLE(plParticlePPSApplicator, kParticlePPSApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleScaleMinApplicator : public plParticleApplicator
{
    CREATABLE(plParticleScaleMinApplicator, kParticleScaleMinApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleScaleMaxApplicator : public plParticleApplicator
{
    CREATABLE(plParticleScaleMaxApplicator, kParticleScaleMaxApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleVelMinApplicator : public plParticleApplicator
{
    CREATABLE(plParticleVelMinApplicator, kParticleVelMinApplicator,
              plParticleApplicator)
};


class HSPLASMA_EXPORT plParticleVelMaxApplicator : public plParticleApplicator
{
    CREATABLE(plParticleVelMaxApplicator, kParticleVelMaxApplicator,
              plParticleApplicator)
};

#endif
