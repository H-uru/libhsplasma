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

PY_GETSET_GETTER_DECL(BoundsOriented, planes)
{
    PyObject* list = PyTuple_New(self->fThis->getNumPlanes());
    for (size_t i=0; i<self->fThis->getNumPlanes(); i++)
        PyTuple_SET_ITEM(list, i, pyPlane3_FromPlane3(self->fThis->getPlanes()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(BoundsOriented, planes)
{
    PY_PROPERTY_CHECK_NULL(planes)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "planes should be a sequence of hsPlane3 objects");
        return -1;
    }
    Py_ssize_t numPlanes = seq.size();
    std::vector<hsPlane3> planes(numPlanes);
    for (Py_ssize_t i=0; i<numPlanes; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlane3_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "planes should be a sequence of hsPlane3 objects");
            return -1;
        }
        planes[i] = pyPlasma_get<hsPlane3>(item);
    }
    self->fThis->setPlanes(numPlanes, &planes[0]);
    return 0;
}

PY_PROPERTY_GETSET_DECL(BoundsOriented, planes)

PY_PROPERTY(hsVector3, BoundsOriented, center, getCenter, setCenter)
PY_PROPERTY(unsigned int, BoundsOriented, centerValid, getCenterValid, setCenterValid)

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
