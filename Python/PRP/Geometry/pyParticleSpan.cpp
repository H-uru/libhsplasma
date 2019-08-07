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

#include "pySpan.h"

#include <PRP/Geometry/plIcicle.h>

PY_PLASMA_NEW(ParticleSpan, plParticleSpan)

PY_PLASMA_TYPE(ParticleSpan, plParticleSpan, "plParticleSpan wrapper")

PY_PLASMA_TYPE_INIT(ParticleSpan)
{
    pyParticleSpan_Type.tp_new = pyParticleSpan_new;
    pyParticleSpan_Type.tp_base = &pyIcicle_Type;
    if (PyType_CheckAndReady(&pyParticleSpan_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleSpan_Type);
    return (PyObject*)&pyParticleSpan_Type;
}

PY_PLASMA_IFC_METHODS(ParticleSpan, plParticleSpan)
