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

#include "pyVolumeIsect.h"

#include <PRP/Region/plVolumeIsect.h>
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(ConvexIsect, plConvexIsect)

PY_METHOD_VA(ConvexIsect, addPlane,
    "Adds or updates a given plane\n"
    "Params: normal, position")
{
    PyObject* normal;
    PyObject* position;
    if (!PyArg_ParseTuple(args, "OO", &normal, &position) || !pyVector3_Check(normal) ||
        !pyVector3_Check(position)) {
        PyErr_SetString(PyExc_TypeError, "addPlane expects hsVector3, hsVector3");
        return NULL;
    }
    self->fThis->addPlane(*((pyVector3*)normal)->fThis, *((pyVector3*)position)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ConvexIsect, transform,
    "Calculates worldspace transformation for this volume\n"
    "Params: localToWorld, worldToLocal")
{
    PyObject* l2w;
    PyObject* w2l;
    if (!PyArg_ParseTuple(args, "OO", &l2w, &w2l) || !pyMatrix44_Check(l2w) || !pyMatrix44_Check(w2l)) {
        PyErr_SetString(PyExc_TypeError, "transform expects hsMatrix44, hsMatrix44");
        return NULL;
    }
    self->fThis->transform(*((pyMatrix44*)l2w)->fThis, *((pyMatrix44*)w2l)->fThis);
    Py_RETURN_NONE;
}

PyMethodDef pyConvexIsect_Methods[] = {
    pyConvexIsect_addPlane_method,
    pyConvexIsect_transform_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(ConvexIsect, plConvexIsect, "plConvexIsect wrapper")

PY_PLASMA_TYPE_INIT(ConvexIsect) {
    pyConvexIsect_Type.tp_new = pyConvexIsect_new;
    pyConvexIsect_Type.tp_methods = pyConvexIsect_Methods;
    pyConvexIsect_Type.tp_base = &pyVolumeIsect_Type;
    if (PyType_CheckAndReady(&pyConvexIsect_Type) < 0)
        return NULL;

    Py_INCREF(&pyConvexIsect_Type);
    return (PyObject*)&pyConvexIsect_Type;
}

PY_PLASMA_IFC_METHODS(ConvexIsect, plConvexIsect)
