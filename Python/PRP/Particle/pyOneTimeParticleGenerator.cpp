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
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(OneTimeParticleGenerator, plOneTimeParticleGenerator)

PY_PROPERTY_VECTOR(hsVector3, OneTimeParticleGenerator, position, getPosition,
                   setPosition)
PY_PROPERTY_VECTOR(hsVector3, OneTimeParticleGenerator, direction, getDirection,
                   setDirection)
PY_PROPERTY(float, OneTimeParticleGenerator, XSize, getXSize, setXSize)
PY_PROPERTY(float, OneTimeParticleGenerator, YSize, getYSize, setYSize)
PY_PROPERTY(float, OneTimeParticleGenerator, scaleMin, getScaleMin, setScaleMin)
PY_PROPERTY(float, OneTimeParticleGenerator, scaleMax, getScaleMax, setScaleMax)
PY_PROPERTY(float, OneTimeParticleGenerator, partRadsPerSecRange,
            getPartRadsPerSecRange, setPartRadsPerSecRange)

static PyGetSetDef pyOneTimeParticleGenerator_GetSet[] = {
    pyOneTimeParticleGenerator_position_getset,
    pyOneTimeParticleGenerator_direction_getset,
    pyOneTimeParticleGenerator_XSize_getset,
    pyOneTimeParticleGenerator_YSize_getset,
    pyOneTimeParticleGenerator_scaleMin_getset,
    pyOneTimeParticleGenerator_scaleMax_getset,
    pyOneTimeParticleGenerator_partRadsPerSecRange_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(OneTimeParticleGenerator, plOneTimeParticleGenerator,
               "plOneTimeParticleGenerator wrapper")

PY_PLASMA_TYPE_INIT(OneTimeParticleGenerator)
{
    pyOneTimeParticleGenerator_Type.tp_new = pyOneTimeParticleGenerator_new;
    pyOneTimeParticleGenerator_Type.tp_getset = pyOneTimeParticleGenerator_GetSet;
    pyOneTimeParticleGenerator_Type.tp_base = &pyParticleGenerator_Type;
    if (PyType_CheckAndReady(&pyOneTimeParticleGenerator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOneTimeParticleGenerator_Type);
    return (PyObject*)&pyOneTimeParticleGenerator_Type;
}

PY_PLASMA_IFC_METHODS(OneTimeParticleGenerator, plOneTimeParticleGenerator)
