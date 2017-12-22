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

#ifndef _PY_PARTICLEEFFECT_H
#define _PY_PARTICLEEFFECT_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(ParticleEffect, class plParticleEffect);
PY_WRAP_PLASMA(ParticleCollisionEffect, class plParticleCollisionEffect);
PY_WRAP_PLASMA(ParticleCollisionEffectBeat, class plParticleCollisionEffectBeat);
PY_WRAP_PLASMA(ParticleCollisionEffectBounce, class plParticleCollisionEffectBounce);
PY_WRAP_PLASMA(ParticleCollisionEffectDie, class plParticleCollisionEffectDie);
PY_WRAP_PLASMA(ParticleFadeOutEffect, class plParticleFadeOutEffect);
PY_WRAP_PLASMA(ParticleFadeVolumeEffect, class plParticleFadeVolumeEffect);
PY_WRAP_PLASMA(ParticleFlockEffect, class plParticleFlockEffect);
PY_WRAP_PLASMA(ParticleFollowSystemEffect, class plParticleFollowSystemEffect);
PY_WRAP_PLASMA(ParticleWindEffect, class plParticleWindEffect);
PY_WRAP_PLASMA(ParticleLocalWind, class plParticleLocalWind);
PY_WRAP_PLASMA(ParticleUniformWind, class plParticleUniformWind);

#endif
