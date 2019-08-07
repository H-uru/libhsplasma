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

#include "pyFogEnvironment.h"

#include <PRP/Misc/plFogEnvironment.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"

PY_PLASMA_NEW(FogEnvironment, plFogEnvironment)

PY_PROPERTY(unsigned char, FogEnvironment, type, getType, setType)
PY_PROPERTY(float, FogEnvironment, start, getStart, setStart)
PY_PROPERTY(float, FogEnvironment, end, getEnd, setEnd)
PY_PROPERTY(float, FogEnvironment, density, getDensity, setDensity)
PY_PROPERTY(hsColorRGBA, FogEnvironment, color, getColor, setColor)

PyGetSetDef pyFogEnvironment_GetSet[] = {
    pyFogEnvironment_type_getset,
    pyFogEnvironment_start_getset,
    pyFogEnvironment_end_getset,
    pyFogEnvironment_density_getset,
    pyFogEnvironment_color_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FogEnvironment, plFogEnvironment, "plFogEnvironment wrapper")

PY_PLASMA_TYPE_INIT(FogEnvironment)
{
    pyFogEnvironment_Type.tp_new = pyFogEnvironment_new;
    pyFogEnvironment_Type.tp_getset = pyFogEnvironment_GetSet;
    pyFogEnvironment_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyFogEnvironment_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(FogEnvironment, "kLinearFog", plFogEnvironment::kLinearFog);
    PY_TYPE_ADD_CONST(FogEnvironment, "kExpFog",    plFogEnvironment::kExpFog);
    PY_TYPE_ADD_CONST(FogEnvironment, "kExp2Fog",   plFogEnvironment::kExp2Fog);
    PY_TYPE_ADD_CONST(FogEnvironment, "kNoFog",     plFogEnvironment::kNoFog);

    Py_INCREF(&pyFogEnvironment_Type);
    return (PyObject*)&pyFogEnvironment_Type;
}

PY_PLASMA_IFC_METHODS(FogEnvironment, plFogEnvironment)
