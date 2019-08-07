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
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(Bounds)
PY_PLASMA_EMPTY_INIT(Bounds)
PY_PLASMA_VALUE_NEW(Bounds, hsBounds)

PY_METHOD_NOARGS(Bounds, ClassName,
    "Returns the RTTI Class name of this Bounds object")
{
    return PyString_FromString(self->fThis->ClassName());
}

PY_METHOD_VA(Bounds, read,
    "Params: stream\n"
    "Read this Bounds object from the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Bounds, write,
    "Params: stream\n"
    "Write this Bounds object to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyBounds_Methods[] = {
    pyBounds_ClassName_method,
    pyBounds_read_method,
    pyBounds_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(int, Bounds, type, getType, setType)

static PyGetSetDef pyBounds_GetSet[] = {
    pyBounds_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Bounds, hsBounds, "hsBounds wrapper")

PY_PLASMA_TYPE_INIT(Bounds)
{
    pyBounds_Type.tp_dealloc = pyBounds_dealloc;
    pyBounds_Type.tp_init = pyBounds___init__;
    pyBounds_Type.tp_new = pyBounds_new;
    pyBounds_Type.tp_methods = pyBounds_Methods;
    pyBounds_Type.tp_getset = pyBounds_GetSet;
    if (PyType_CheckAndReady(&pyBounds_Type) < 0)
        return nullptr;

    Py_INCREF(&pyBounds_Type);
    return (PyObject*)&pyBounds_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds, hsBounds)
