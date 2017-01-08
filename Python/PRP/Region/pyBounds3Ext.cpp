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

PY_PLASMA_VALUE_NEW(Bounds3Ext, hsBounds3Ext)

static PyObject* pyBounds3Ext_getAxis(pyBounds3Ext* self, void* idx) {
    return pyVector3_FromVector3(self->fThis->getAxis((long)idx));
}

static PyObject* pyBounds3Ext_getDist(pyBounds3Ext* self, void* idx) {
    hsFloatPoint2 dist = self->fThis->getDist((long)idx);
    return Py_BuildValue("ff", dist.X, dist.Y);
}

static int pyBounds3Ext_setAxis(pyBounds3Ext* self, PyObject* value, void* idx) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "axes should be an hsVector3");
        return -1;
    }
    self->fThis->setAxis((long)idx, *((pyVector3*)value)->fThis);
    return 0;
}

static int pyBounds3Ext_setDist(pyBounds3Ext* self, PyObject* value, void* idx) {
    if (value == NULL || !PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {
        PyErr_SetString(PyExc_TypeError, "dists should be a tuple (float, float)");
        return -1;
    }
    hsFloatPoint2 dist;
    PyObject* itmX = PyTuple_GET_ITEM(value, 0);
    PyObject* itmY = PyTuple_GET_ITEM(value, 1);
    if (!PyFloat_Check(itmX) || !PyFloat_Check(itmY)) {
        PyErr_SetString(PyExc_TypeError, "dists should be a tuple (float, float)");
        return -1;
    }
    dist.X = PyFloat_AsDouble(itmX);
    dist.Y = PyFloat_AsDouble(itmY);
    self->fThis->setDist((long)idx, dist);
    return 0;
}

PY_PROPERTY(unsigned int, Bounds3Ext, flags, getFlags, setFlags)
PY_PROPERTY(hsVector3, Bounds3Ext, corner, getCorner, setCorner)
PY_PROPERTY(float, Bounds3Ext, radius, getRadius, setRadius)

static PyGetSetDef pyBounds3Ext_GetSet[] = {
    pyBounds3Ext_flags_getset,
    pyBounds3Ext_corner_getset,
    { _pycs("axis0"), (getter)pyBounds3Ext_getAxis,
        (setter)pyBounds3Ext_setAxis, NULL, (void*)0 },
    { _pycs("axis1"), (getter)pyBounds3Ext_getAxis,
        (setter)pyBounds3Ext_setAxis, NULL, (void*)1 },
    { _pycs("axis2"), (getter)pyBounds3Ext_getAxis,
        (setter)pyBounds3Ext_setAxis, NULL, (void*)2 },
    { _pycs("dist0"), (getter)pyBounds3Ext_getDist,
        (setter)pyBounds3Ext_setDist, NULL, (void*)0 },
    { _pycs("dist1"), (getter)pyBounds3Ext_getDist,
        (setter)pyBounds3Ext_setDist, NULL, (void*)1 },
    { _pycs("dist2"), (getter)pyBounds3Ext_getDist,
        (setter)pyBounds3Ext_setDist, NULL, (void*)2 },
    pyBounds3Ext_radius_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Bounds3Ext, hsBounds3Ext, "hsBounds3Ext wrapper")

PY_PLASMA_TYPE_INIT(Bounds3Ext) {
    pyBounds3Ext_Type.tp_new = pyBounds3Ext_new;
    pyBounds3Ext_Type.tp_getset = pyBounds3Ext_GetSet;
    pyBounds3Ext_Type.tp_base = &pyBounds3_Type;
    if (PyType_CheckAndReady(&pyBounds3Ext_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisAligned", hsBounds3Ext::kAxisAligned);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kSphereSet", hsBounds3Ext::kSphereSet);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kDistsSet", hsBounds3Ext::kDistsSet);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisZeroZero", hsBounds3Ext::kAxisZeroZero);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisOneZero", hsBounds3Ext::kAxisOneZero);
    PY_TYPE_ADD_CONST(Bounds3Ext, "kAxisTwoZero", hsBounds3Ext::kAxisTwoZero);

    Py_INCREF(&pyBounds3Ext_Type);
    return (PyObject*)&pyBounds3Ext_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds3Ext, hsBounds3Ext)

}
