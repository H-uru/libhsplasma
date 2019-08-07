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

#include "pyGBufferGroup.h"

#include <PRP/Geometry/plGBufferGroup.h>
#include "Math/pyGeometry3.h"
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(GBufferTriangle)
PY_PLASMA_EMPTY_INIT(GBufferTriangle)
PY_PLASMA_VALUE_NEW(GBufferTriangle, plGBufferTriangle)

PY_METHOD_VA(GBufferTriangle, read,
    "Params: stream\n"
    "Reads the triangle from a stream")
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

PY_METHOD_VA(GBufferTriangle, write,
    "Params: stream\n"
    "Writes the triangle to a stream")
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

static PyMethodDef pyGBufferTriangle_Methods[] = {
    pyGBufferTriangle_read_method,
    pyGBufferTriangle_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index1, fIndex1)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index2, fIndex2)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index3, fIndex3)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, spanIndex, fSpanIndex)
PY_PROPERTY_MEMBER(hsVector3, GBufferTriangle, center, fCenter)

static PyGetSetDef pyGBufferTriangle_GetSet[] = {
    pyGBufferTriangle_index1_getset,
    pyGBufferTriangle_index2_getset,
    pyGBufferTriangle_index3_getset,
    pyGBufferTriangle_spanIndex_getset,
    pyGBufferTriangle_center_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GBufferTriangle, plGBufferTriangle, "plGBufferTriangle wrapper")

PY_PLASMA_TYPE_INIT(GBufferTriangle)
{
    pyGBufferTriangle_Type.tp_dealloc = pyGBufferTriangle_dealloc;
    pyGBufferTriangle_Type.tp_init = pyGBufferTriangle___init__;
    pyGBufferTriangle_Type.tp_new = pyGBufferTriangle_new;
    pyGBufferTriangle_Type.tp_methods = pyGBufferTriangle_Methods;
    pyGBufferTriangle_Type.tp_getset = pyGBufferTriangle_GetSet;
    if (PyType_CheckAndReady(&pyGBufferTriangle_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGBufferTriangle_Type);
    return (PyObject*)&pyGBufferTriangle_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferTriangle, plGBufferTriangle)
