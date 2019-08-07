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

#include "pyParticleEffect.h"

#include <PRP/Particle/plParticleEffect.h>
#include "PRP/KeyedObject/pyKeyedObject.h"

/* pyParticleEffect */
PY_PLASMA_NEW(ParticleEffect, plParticleEffect)
PY_PLASMA_TYPE(ParticleEffect, plParticleEffect, "plParticleEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleEffect)
{
    pyParticleEffect_Type.tp_new = pyParticleEffect_new;
    pyParticleEffect_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyParticleEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleEffect_Type);
    return (PyObject*)&pyParticleEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleEffect, plParticleEffect)


/* pyParticleFollowSystemEffect */
PY_PLASMA_NEW(ParticleFollowSystemEffect, plParticleFollowSystemEffect)
PY_PLASMA_TYPE(ParticleFollowSystemEffect, plParticleFollowSystemEffect,
               "plParticleFollowSystemEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleFollowSystemEffect)
{
    pyParticleFollowSystemEffect_Type.tp_new = pyParticleFollowSystemEffect_new;
    pyParticleFollowSystemEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleFollowSystemEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleFollowSystemEffect_Type);
    return (PyObject*)&pyParticleFollowSystemEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleFollowSystemEffect, plParticleFollowSystemEffect)
