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

PY_PLASMA_VALUE_NEW(BoundsOriented, hsBoundsOriented)

PY_PROPERTY(hsVector3, BoundsOriented, center, getCenter, setCenter)
PY_PROPERTY(unsigned int, BoundsOriented, centerValid, getCenterValid, setCenterValid)
PY_PROPERTY_VECTOR(hsPlane3, BoundsOriented, planes, getPlanesVec, setPlanes)

static PyGetSetDef pyBoundsOriented_GetSet[] = {
    pyBoundsOriented_center_getset,
    pyBoundsOriented_centerValid_getset,
    pyBoundsOriented_planes_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(BoundsOriented, hsBoundsOriented, "hsBoundsOriented wrapper")

PY_PLASMA_TYPE_INIT(BoundsOriented)
{
    pyBoundsOriented_Type.tp_new = pyBoundsOriented_new;
    pyBoundsOriented_Type.tp_getset = pyBoundsOriented_GetSet;
    pyBoundsOriented_Type.tp_base = &pyBounds_Type;
    if (PyType_CheckAndReady(&pyBoundsOriented_Type) < 0)
        return nullptr;

    Py_INCREF(&pyBoundsOriented_Type);
    return (PyObject*)&pyBoundsOriented_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(BoundsOriented, hsBoundsOriented)
