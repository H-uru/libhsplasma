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

#include "pyConvexVolume.h"

#include <PRP/Region/plConvexVolume.h>
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(ConvexVolume, plConvexVolume)

PY_PROPERTY_VECTOR(hsPlane3, ConvexVolume, localPlanes, getLocalPlanes, setLocalPlanes)

static PyGetSetDef pyConvexVolume_GetSet[] = {
    pyConvexVolume_localPlanes_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ConvexVolume, plConvexVolume, "plConvexVolume wrapper")

PY_PLASMA_TYPE_INIT(ConvexVolume)
{
    pyConvexVolume_Type.tp_new = pyConvexVolume_new;
    pyConvexVolume_Type.tp_getset = pyConvexVolume_GetSet;
    pyConvexVolume_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyConvexVolume_Type) < 0)
        return nullptr;

    Py_INCREF(&pyConvexVolume_Type);
    return (PyObject*)&pyConvexVolume_Type;
}

PY_PLASMA_IFC_METHODS(ConvexVolume, plConvexVolume)
