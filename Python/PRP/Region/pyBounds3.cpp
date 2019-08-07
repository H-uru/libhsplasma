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

#include "pyBounds.h"

#include <PRP/Region/hsBounds.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_VALUE_NEW(Bounds3, hsBounds3)

PY_PROPERTY(hsVector3, Bounds3, mins, getMins, setMins)
PY_PROPERTY(hsVector3, Bounds3, maxs, getMaxs, setMaxs)
PY_PROPERTY(hsVector3, Bounds3, center, getCenter, setCenter)

static PyGetSetDef pyBounds3_GetSet[] = {
    pyBounds3_mins_getset,
    pyBounds3_maxs_getset,
    pyBounds3_center_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Bounds3, hsBounds3, "hsBounds3 wrapper")

PY_PLASMA_TYPE_INIT(Bounds3)
{
    pyBounds3_Type.tp_new = pyBounds3_new;
    pyBounds3_Type.tp_getset = pyBounds3_GetSet;
    pyBounds3_Type.tp_base = &pyBounds_Type;
    if (PyType_CheckAndReady(&pyBounds3_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Bounds3, "kCenterValid", hsBounds3::kCenterValid);
    PY_TYPE_ADD_CONST(Bounds3, "kIsSphere", hsBounds3::kIsSphere);

    Py_INCREF(&pyBounds3_Type);
    return (PyObject*)&pyBounds3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds3, hsBounds3)
