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

DllClass plParticleApplicator : public plAGApplicator {
    CREATABLE(plParticleApplicator, kParticleApplicator, plAGApplicator)
};


DllClass plParticleAngleApplicator : public plParticleApplicator {
    CREATABLE(plParticleAngleApplicator, kParticleAngleApplicator,
              plParticleApplicator)
};


DllClass plParticleLifeMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleLifeMinApplicator, kParticleLifeMinApplicator,
              plParticleApplicator)
};


DllClass plParticleLifeMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleLifeMaxApplicator, kParticleLifeMaxApplicator,
              plParticleApplicator)
};


DllClass plParticlePPSApplicator : public plParticleApplicator {
    CREATABLE(plParticlePPSApplicator, kParticlePPSApplicator,
              plParticleApplicator)
};


DllClass plParticleScaleMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleScaleMinApplicator, kParticleScaleMinApplicator,
              plParticleApplicator)
};


DllClass plParticleScaleMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleScaleMaxApplicator, kParticleScaleMaxApplicator,
              plParticleApplicator)
};


DllClass plParticleVelMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleVelMinApplicator, kParticleVelMinApplicator,
              plParticleApplicator)
};


DllClass plParticleVelMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleVelMaxApplicator, kParticleVelMaxApplicator,
              plParticleApplicator)
};

#endif
