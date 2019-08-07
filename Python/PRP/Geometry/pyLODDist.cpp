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

#include "pyClusterGroup.h"

#include <PRP/Geometry/plClusterGroup.h>
#include "Stream/pyStream.h"

PY_PLASMA_NEW_MSG(LODDist, "Cannot create plLODDist objects from Python")

PY_METHOD_VA(LODDist, read,
    "Params: stream\n"
    "Reads this object from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(LODDist, write,
    "Params: stream\n"
    "Writes this object to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyLODDist_Methods[] = {
    pyLODDist_read_method,
    pyLODDist_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(float, LODDist, min, getMin, setMin)
PY_PROPERTY(float, LODDist, max, getMax, setMax)

static PyGetSetDef pyLODDist_GetSet[] = {
    pyLODDist_min_getset,
    pyLODDist_max_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LODDist, plLODDist, "plLODDist wrapper")

PY_PLASMA_TYPE_INIT(LODDist)
{
    pyLODDist_Type.tp_new = pyLODDist_new;
    pyLODDist_Type.tp_methods = pyLODDist_Methods;
    pyLODDist_Type.tp_getset = pyLODDist_GetSet;
    if (PyType_CheckAndReady(&pyLODDist_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLODDist_Type);
    return (PyObject*)&pyLODDist_Type;
}

PY_PLASMA_IFC_METHODS(LODDist, plLODDist)
