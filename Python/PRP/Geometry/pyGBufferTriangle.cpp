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

#include <PyPlasma.h>
#include <PRP/Geometry/plGBufferGroup.h>
#include "pyGBufferGroup.h"
#include "Math/pyGeometry3.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyGBufferTriangle_dealloc(pyGBufferTriangle* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyGBufferTriangle___init__(pyGBufferTriangle* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyGBufferTriangle_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGBufferTriangle* self = (pyGBufferTriangle*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plGBufferTriangle();
    return (PyObject*)self;
}

static PyObject* pyGBufferTriangle_read(pyGBufferTriangle* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferTriangle_write(pyGBufferTriangle* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyGBufferTriangle_getIndex1(pyGBufferTriangle* self, void*) {
    return PyInt_FromLong(self->fThis->fIndex1);
}

static PyObject* pyGBufferTriangle_getIndex2(pyGBufferTriangle* self, void*) {
    return PyInt_FromLong(self->fThis->fIndex2);
}

static PyObject* pyGBufferTriangle_getIndex3(pyGBufferTriangle* self, void*) {
    return PyInt_FromLong(self->fThis->fIndex3);
}

static PyObject* pyGBufferTriangle_getSpanIndex(pyGBufferTriangle* self, void*) {
    return PyInt_FromLong(self->fThis->fSpanIndex);
}

static PyObject* pyGBufferTriangle_getCenter(pyGBufferTriangle* self, void*) {
    return pyVector3_FromVector3(self->fThis->fCenter);
}

static int pyGBufferTriangle_setIndex1(pyGBufferTriangle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index1 should be an int");
        return -1;
    }
    self->fThis->fIndex1 = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferTriangle_setIndex2(pyGBufferTriangle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index2 should be an int");
        return -1;
    }
    self->fThis->fIndex2 = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferTriangle_setIndex3(pyGBufferTriangle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index3 should be an int");
        return -1;
    }
    self->fThis->fIndex3 = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferTriangle_setSpanIndex(pyGBufferTriangle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "spanIndex should be an int");
        return -1;
    }
    self->fThis->fSpanIndex = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferTriangle_setCenter(pyGBufferTriangle* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "center should be an hsVector3");
        return -1;
    }
    self->fThis->fCenter = *((pyVector3*)value)->fThis;
    return 0;
}

static PyMethodDef pyGBufferTriangle_Methods[] = {
    { "read", (PyCFunction)pyGBufferTriangle_read, METH_VARARGS,
      "Params: stream\n"
      "Reads the triangle from a stream" },
    { "write", (PyCFunction)pyGBufferTriangle_write, METH_VARARGS,
      "Params: stream\n"
      "Writes the triangle to a stream" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyGBufferTriangle_GetSet[] = {
    { "index1", (getter)pyGBufferTriangle_getIndex1, (setter)pyGBufferTriangle_setIndex1, NULL, NULL },
    { "index2", (getter)pyGBufferTriangle_getIndex2, (setter)pyGBufferTriangle_setIndex2, NULL, NULL },
    { "index3", (getter)pyGBufferTriangle_getIndex3, (setter)pyGBufferTriangle_setIndex3, NULL, NULL },
    { "spanIndex", (getter)pyGBufferTriangle_getSpanIndex, (setter)pyGBufferTriangle_setSpanIndex, NULL, NULL },
    { "center", (getter)pyGBufferTriangle_getCenter, (setter)pyGBufferTriangle_setCenter, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGBufferTriangle_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plGBufferTriangle",       /* tp_name */
    sizeof(pyGBufferTriangle),          /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyGBufferTriangle_dealloc, /* tp_dealloc */
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
    "plGBufferTriangle wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGBufferTriangle_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyGBufferTriangle_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyGBufferTriangle___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyGBufferTriangle_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyGBufferTriangle_Type() {
    if (PyType_Ready(&pyGBufferTriangle_Type) < 0)
        return NULL;

    Py_INCREF(&pyGBufferTriangle_Type);
    return (PyObject*)&pyGBufferTriangle_Type;
}

int pyGBufferTriangle_Check(PyObject* obj) {
    if (obj->ob_type == &pyGBufferTriangle_Type
        || PyType_IsSubtype(obj->ob_type, &pyGBufferTriangle_Type))
        return 1;
    return 0;
}

PyObject* pyGBufferTriangle_FromGBufferTriangle(const plGBufferTriangle& tri) {
    pyGBufferTriangle* pytri = PyObject_New(pyGBufferTriangle, &pyGBufferTriangle_Type);
    delete pytri->fThis;
    pytri->fThis = new plGBufferTriangle(tri);
    return (PyObject*)pytri;
}

}
