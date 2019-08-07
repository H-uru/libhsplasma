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

PY_GETSET_GETTER_DECL(SpanTemplate, vertices)
{
    std::vector<plSpanTemplate::Vertex> verts = self->fThis->getVertices();
    PyObject* list = PyTuple_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyTuple_SET_ITEM(list, i, pySpanTemplateVertex_FromSpanTemplateVertex(&verts[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SpanTemplate, vertices)
{
    PY_PROPERTY_CHECK_NULL(vertices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of plSpanTemplateVertex objects");
        return -1;
    }
    std::vector<plSpanTemplate::Vertex> verts(seq.size());
    for (size_t i=0; i<verts.size(); i++) {
        PyObject* itm = seq.get(i);
        if (!pySpanTemplateVertex_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "vertices should be a sequence of plSpanTemplateVertex objects");
            return -1;
        }
        verts[i] = *((pySpanTemplateVertex*)itm)->fThis;
    }
    self->fThis->setVertices(verts);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SpanTemplate, vertices)

PY_GETSET_GETTER_DECL(SpanTemplate, indices)
{
    const unsigned short* indices = self->fThis->getIndices();
    size_t numIndices = self->fThis->getNumTris() * 3;
    PyObject* list = PyTuple_New(numIndices);
    for (size_t i=0; i<numIndices; i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(indices[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SpanTemplate, indices)
{
    PY_PROPERTY_CHECK_NULL(indices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "indices should be a sequence of ints");
        return -1;
    }
    Py_ssize_t numIndices = seq.size();
    std::vector<unsigned short> indices(numIndices);
    for (Py_ssize_t i=0; i<numIndices; i++) {
        PyObject* itm = seq.get(i);
        if (!pyPlasma_check<unsigned short>(itm)) {
            PyErr_SetString(PyExc_TypeError, "indices should be a sequence of ints");
            return -1;
        }
        indices[i] = pyPlasma_get<unsigned short>(itm);
    }
    self->fThis->setIndices(numIndices, indices.data());
    return 0;
}

PY_PROPERTY_GETSET_DECL(SpanTemplate, indices)

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
