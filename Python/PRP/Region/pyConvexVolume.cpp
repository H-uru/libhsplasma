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

PY_GETSET_GETTER_DECL(ConvexVolume, localPlanes)
{
    const auto& planes = self->fThis->getLocalPlanes();
    PyObject* result = PyTuple_New(planes.size());
    for (size_t i = 0; i < planes.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlane3_FromPlane3(planes[i]));
    return result;
}

PY_GETSET_SETTER_DECL(ConvexVolume, localPlanes)
{
    PY_PROPERTY_CHECK_NULL(localPlanes);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "localPlanes should be a sequence of hsPlane3 objects");
        return -1;
    }
    std::vector<hsPlane3> planes(seq.size());
    for (size_t i = 0; i < planes.size(); ++i) {
        PyObject* plane = seq.get(i);
        if (!pyPlane3_Check(plane)) {
            PyErr_SetString(PyExc_TypeError, "localPlanes should be a sequence of hsPlane3 objects");
            return -1;
        }
        planes[i] = *((pyPlane3*)plane)->fThis;
    }
    self->fThis->setLocalPlanes(planes);
    return 0;
}

PY_PROPERTY_GETSET_DECL(ConvexVolume, localPlanes)

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
