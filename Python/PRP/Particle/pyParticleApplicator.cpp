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

#include "pyParticleApplicator.h"

#include <PRP/Particle/plParticleApplicator.hpp>
#include "PRP/Avatar/pyAGApplicator.h"

PY_PLASMA_NEW(ParticleApplicator, plParticleApplicator)
PY_PLASMA_TYPE(ParticleApplicator, plParticleApplicator, "plParticleApplicator wrapper")

PY_PLASMA_TYPE_INIT(ParticleApplicator)
{
    pyParticleApplicator_Type.tp_new = pyParticleApplicator_new;
    pyParticleApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_CheckAndReady(&pyParticleApplicator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleApplicator_Type);
    return (PyObject*)&pyParticleApplicator_Type;
}

PY_PLASMA_IFC_METHODS(ParticleApplicator, plParticleApplicator)

#define PY_ParticleApplicator_Subtype(pyType)                   \
    PY_PLASMA_NEW(pyType, pl##pyType)                           \
    PY_PLASMA_TYPE(pyType, pl##pyType, "pl" #pyType " wrapper") \
    PY_PLASMA_TYPE_INIT(pyType)                                 \
    {                                                           \
        py##pyType##_Type.tp_new = py##pyType##_new;            \
        py##pyType##_Type.tp_base = &pyParticleApplicator_Type; \
        if (PyType_CheckAndReady(&py##pyType##_Type) < 0)       \
            return nullptr;                                     \
                                                                \
        Py_INCREF(&py##pyType##_Type);                          \
        return (PyObject*)&py##pyType##_Type;                   \
    }                                                           \
    PY_PLASMA_IFC_METHODS(pyType, pl##pyType)

PY_ParticleApplicator_Subtype(ParticleAngleApplicator)
PY_ParticleApplicator_Subtype(ParticleLifeMinApplicator)
PY_ParticleApplicator_Subtype(ParticleLifeMaxApplicator)
PY_ParticleApplicator_Subtype(ParticlePPSApplicator)
PY_ParticleApplicator_Subtype(ParticleScaleMinApplicator)
PY_ParticleApplicator_Subtype(ParticleScaleMaxApplicator)
PY_ParticleApplicator_Subtype(ParticleVelMinApplicator)
PY_ParticleApplicator_Subtype(ParticleVelMaxApplicator)
