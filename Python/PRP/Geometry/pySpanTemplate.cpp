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

#include "pySpanTemplate.h"

#include <PRP/Geometry/plSpanTemplate.h>
#include "Stream/pyStream.h"

PY_PLASMA_NEW_MSG(SpanTemplate, "Cannot create plSpanTemplate objects from Python")

PY_METHOD_VA(SpanTemplate, read,
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

PY_METHOD_VA(SpanTemplate, write,
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

static PyMethodDef pySpanTemplate_Methods[] = {
    pySpanTemplate_read_method,
    pySpanTemplate_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_VECTOR(plSpanTemplate::Vertex, SpanTemplate, vertices, getVertices, setVertices)
PY_PROPERTY_VECTOR(unsigned short, SpanTemplate, indices, getIndicesVec, setIndices)
PY_PROPERTY(unsigned short, SpanTemplate, format, getFormat, setFormat)

static PyGetSetDef pySpanTemplate_GetSet[] = {
    pySpanTemplate_vertices_getset,
    pySpanTemplate_indices_getset,
    pySpanTemplate_format_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpanTemplate, plSpanTemplate, "plSpanTemplate wrapper")

PY_PLASMA_TYPE_INIT(SpanTemplate)
{
    pySpanTemplate_Type.tp_new = pySpanTemplate_new;
    pySpanTemplate_Type.tp_methods = pySpanTemplate_Methods;
    pySpanTemplate_Type.tp_getset = pySpanTemplate_GetSet;
    if (PyType_CheckAndReady(&pySpanTemplate_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpanTemplate_Type);
    return (PyObject*)&pySpanTemplate_Type;
}

PY_PLASMA_IFC_METHODS(SpanTemplate, plSpanTemplate)
