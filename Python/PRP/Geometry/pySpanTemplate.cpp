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

extern "C" {

static PyObject* pySpanTemplate_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot create plSpanTemplate objects from Python");
    return NULL;
}

static PyObject* pySpanTemplate_read(pySpanTemplate* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpanTemplate_write(pySpanTemplate* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpanTemplate_getVerts(pySpanTemplate* self, void*) {
    std::vector<plSpanTemplate::Vertex> verts = self->fThis->getVertices();
    PyObject* list = PyList_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyList_SET_ITEM(list, i, pySpanTemplateVertex_FromSpanTemplateVertex(&verts[i]));
    return list;
}

static PyObject* pySpanTemplate_getIndices(pySpanTemplate* self, void*) {
    const unsigned short* indices = self->fThis->getIndices();
    size_t numIndices = self->fThis->getNumTris() * 3;
    PyObject* list = PyList_New(numIndices);
    for (size_t i=0; i<numIndices; i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(indices[i]));
    return list;
}

static int pySpanTemplate_setVerts(pySpanTemplate* self, PyObject* value, void*) {
    std::vector<plSpanTemplate::Vertex> verts;
    if (value == NULL) {
        self->fThis->setVertices(verts);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "vertices should be a list of plSpanTemplateVertex objects");
        return -1;
    }
    verts.resize(PyList_Size(value));
    for (size_t i=0; i<verts.size(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pySpanTemplateVertex_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "vertices should be a list of plSpanTemplateVertex objects");
            return -1;
        }
        verts[i] = *((pySpanTemplateVertex*)itm)->fThis;
    }
    self->fThis->setVertices(verts);
    return 0;
}

static int pySpanTemplate_setIndices(pySpanTemplate* self, PyObject* value, void*) {
    std::vector<unsigned short> indices;
    if (value == NULL) {
        self->fThis->setIndices(0, NULL);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
        return -1;
    }
    size_t numIndices = PyList_Size(value);
    indices.resize(numIndices);
    for (size_t i=0; i<numIndices; i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyInt_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
            return -1;
        }
        indices[i] = PyInt_AsLong(itm);
    }
    self->fThis->setIndices(numIndices, indices.data());
    return 0;
}

static PyMethodDef pySpanTemplate_Methods[] = {
    { "read", (PyCFunction)pySpanTemplate_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from the stream" },
    { "write", (PyCFunction)pySpanTemplate_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to the stream" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(unsigned short, SpanTemplate, format, getFormat, setFormat)

static PyGetSetDef pySpanTemplate_GetSet[] = {
    { _pycs("vertices"), (getter)pySpanTemplate_getVerts,
        (setter)pySpanTemplate_setVerts, NULL, NULL },
    { _pycs("indices"), (getter)pySpanTemplate_getIndices,
        (setter)pySpanTemplate_setIndices, NULL, NULL },
    pySpanTemplate_format_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySpanTemplate_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpanTemplate",        /* tp_name */
    sizeof(pySpanTemplate),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plSpanTemplate wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpanTemplate_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pySpanTemplate_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySpanTemplate_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pySpanTemplate_Type() {
    if (PyType_Ready(&pySpanTemplate_Type) < 0)
        return NULL;

    Py_INCREF(&pySpanTemplate_Type);
    return (PyObject*)&pySpanTemplate_Type;
}

PY_PLASMA_IFC_METHODS(SpanTemplate, plSpanTemplate)

}
