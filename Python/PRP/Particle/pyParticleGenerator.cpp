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

#include "pyParticleGenerator.h"

#include <PRP/Particle/plParticleGenerator.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(ParticleGenerator, "plParticleGenerator is abstract")
PY_PLASMA_TYPE(ParticleGenerator, plParticleGenerator, "plParticleGenerator wrapper")

PY_PLASMA_TYPE_INIT(ParticleGenerator)
{
    pyParticleGenerator_Type.tp_new = pyParticleGenerator_new;
    pyParticleGenerator_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyParticleGenerator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleGenerator_Type);
    return (PyObject*)&pyParticleGenerator_Type;
}

PY_PLASMA_IFC_METHODS(ParticleGenerator, plParticleGenerator)
