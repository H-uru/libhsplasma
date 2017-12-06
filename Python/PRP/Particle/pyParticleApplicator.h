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

#ifndef _PY_PARTICLEAPPLICATOR_H
#define _PY_PARTICLEAPPLICATOR_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(ParticleApplicator, class plParticleApplicator);
PY_WRAP_PLASMA(ParticleAngleApplicator, class plParticleAngleApplicator);
PY_WRAP_PLASMA(ParticleLifeMinApplicator, class plParticleLifeMinApplicator);
PY_WRAP_PLASMA(ParticleLifeMaxApplicator, class plParticleLifeMaxApplicator);
PY_WRAP_PLASMA(ParticlePPSApplicator, class plParticlePPSApplicator);
PY_WRAP_PLASMA(ParticleScaleMinApplicator, class plParticleScaleMinApplicator);
PY_WRAP_PLASMA(ParticleScaleMaxApplicator, class plParticleScaleMaxApplicator);
PY_WRAP_PLASMA(ParticleVelMinApplicator, class plParticleVelMinApplicator);
PY_WRAP_PLASMA(ParticleVelMaxApplicator, class plParticleVelMaxApplicator);

#endif
