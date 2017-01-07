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

extern "C" {

PY_PLASMA_VALUE_NEW(BoundsOriented, hsBoundsOriented)

static PyObject* pyBoundsOriented_getPlanes(pyBoundsOriented* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumPlanes());
    for (size_t i=0; i<self->fThis->getNumPlanes(); i++)
        PyList_SET_ITEM(list, i, pyPlane3_FromPlane3(self->fThis->getPlanes()[i]));
    return list;
}

static int pyBoundsOriented_setPlanes(pyBoundsOriented* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setPlanes(0, NULL);
        return 0;
    } else if (PyList_Check(value)) {
        size_t numPlanes = PyList_Size(value);
        hsPlane3* planes = new hsPlane3[numPlanes];
        for (size_t i=0; i<numPlanes; i++) {
            if (!pyPlane3_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "planes should be a list of hsPlane3 objects");
                delete[] planes;
                return -1;
            }
            planes[i] = *((pyPlane3*)PyList_GetItem(value, i))->fThis;
        }
        self->fThis->setPlanes(numPlanes, planes);
        delete[] planes;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "planes should be a list of hsPlane3 objects");
        return -1;
    }
}

PY_PROPERTY(hsVector3, BoundsOriented, center, getCenter, setCenter)
PY_PROPERTY(unsigned int, BoundsOriented, centerValid, getCenterValid, setCenterValid)

static PyGetSetDef pyBoundsOriented_GetSet[] = {
    pyBoundsOriented_center_getset,
    pyBoundsOriented_centerValid_getset,
    { _pycs("planes"), (getter)pyBoundsOriented_getPlanes,
        (setter)pyBoundsOriented_setPlanes, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(BoundsOriented, hsBoundsOriented, "hsBoundsOriented wrapper")

PY_PLASMA_TYPE_INIT(BoundsOriented) {
    pyBoundsOriented_Type.tp_new = pyBoundsOriented_new;
    pyBoundsOriented_Type.tp_getset = pyBoundsOriented_GetSet;
    pyBoundsOriented_Type.tp_base = &pyBounds_Type;
    if (PyType_Ready(&pyBoundsOriented_Type) < 0)
        return NULL;

    Py_INCREF(&pyBoundsOriented_Type);
    return (PyObject*)&pyBoundsOriented_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(BoundsOriented, hsBoundsOriented)

}
