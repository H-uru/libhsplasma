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

#include "pyStream.h"

#include <Stream/hsRAMStream.h>

PY_PLASMA_NEW(RAMStream, hsRAMStream)

PY_METHOD_VA(RAMStream, resize,
    "Params: newsize\n"
    "Allocates newsize bytes in the internal buffer.  This will truncate "
    "data if it's shorter than the current buffer, or zero-fill the extra "
    "space if it's larger than the current buffer.")
{
    int newSize;

    if (!PyArg_ParseTuple(args, "i", &newSize)) {
        PyErr_SetString(PyExc_TypeError, "resize expects an int");
        return nullptr;
    }
    self->fThis->resize(newSize);
    Py_RETURN_NONE;
}

static PyMethodDef pyRAMStream_Methods[] = {
    pyRAMStream_resize_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(RAMStream, buffer)
{
    PyObject* bufObj = PyBytes_FromStringAndSize(nullptr, self->fThis->size());
    char* data = PyBytes_AS_STRING(bufObj);
    self->fThis->copyTo(data, self->fThis->size());
    return bufObj;
}

PY_GETSET_SETTER_DECL(RAMStream, buffer)
{
    if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "buffer should be a binary string");
        return -1;
    }
    char* buf;
    Py_ssize_t len;
    PyBytes_AsStringAndSize(value, &buf, &len);
    self->fThis->copyFrom(buf, len);
    return 0;
}

PY_PROPERTY_GETSET_DECL(RAMStream, buffer)

static PyGetSetDef pyRAMStream_GetSet[] = {
    pyRAMStream_buffer_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(RAMStream, hsRAMStream, "hsRAMStream wrapper")

PY_PLASMA_TYPE_INIT(RAMStream)
{
    pyRAMStream_Type.tp_new = pyRAMStream_new;
    pyRAMStream_Type.tp_methods = pyRAMStream_Methods;
    pyRAMStream_Type.tp_getset = pyRAMStream_GetSet;
    pyRAMStream_Type.tp_base = &pyStream_Type;
    if (PyType_CheckAndReady(&pyRAMStream_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRAMStream_Type);
    return (PyObject*)&pyRAMStream_Type;
}

PY_PLASMA_IFC_METHODS(RAMStream, hsRAMStream)
