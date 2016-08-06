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

#include "pySpan.h"

#include <PRP/Geometry/plVertexSpan.h>

extern "C" {

static PyObject* pyVertexSpan_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyVertexSpan* self = (pyVertexSpan*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plVertexSpan();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyVertexSpan_getGroupIdx(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getGroupIdx());
}

static PyObject* pyVertexSpan_getVBufferIdx(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getVBufferIdx());
}

static PyObject* pyVertexSpan_getCellIdx(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getCellIdx());
}

static PyObject* pyVertexSpan_getCellOffset(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getCellOffset());
}

static PyObject* pyVertexSpan_getVStartIdx(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getVStartIdx());
}

static PyObject* pyVertexSpan_getVLength(pyVertexSpan* self, void*) {
    return PyInt_FromLong(self->fThis->getVLength());
}

static int pyVertexSpan_setGroupIdx(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "groupIdx should be an int");
        return -1;
    }
    self->fThis->setGroupIdx(PyInt_AsLong(value));
    return 0;
}

static int pyVertexSpan_setVBufferIdx(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "VBufferIdx should be an int");
        return -1;
    }
    self->fThis->setVBufferIdx(PyInt_AsLong(value));
    return 0;
}

static int pyVertexSpan_setCellIdx(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "cellIdx should be an int");
        return -1;
    }
    self->fThis->setCellIdx(PyInt_AsLong(value));
    return 0;
}

static int pyVertexSpan_setCellOffset(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "cellOffset should be an int");
        return -1;
    }
    self->fThis->setCellOffset(PyInt_AsLong(value));
    return 0;
}

static int pyVertexSpan_setVStartIdx(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "VStartIdx should be an int");
        return -1;
    }
    self->fThis->setVStartIdx(PyInt_AsLong(value));
    return 0;
}

static int pyVertexSpan_setVLength(pyVertexSpan* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "VLength should be an int");
        return -1;
    }
    self->fThis->setVLength(PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyVertexSpan_GetSet[] = {
    { _pycs("groupIdx"), (getter)pyVertexSpan_getGroupIdx,
        (setter)pyVertexSpan_setGroupIdx, _pycs("The Buffer Group index"), NULL },
    { _pycs("VBufferIdx"), (getter)pyVertexSpan_getVBufferIdx,
        (setter)pyVertexSpan_setVBufferIdx, _pycs("The Vertex Buffer index"), NULL },
    { _pycs("cellIdx"), (getter)pyVertexSpan_getCellIdx,
        (setter)pyVertexSpan_setCellIdx, _pycs("The Cell Buffer index"), NULL },
    { _pycs("cellOffset"), (getter)pyVertexSpan_getCellOffset,
        (setter)pyVertexSpan_setCellOffset, _pycs("The Cell offset"), NULL },
    { _pycs("VStartIdx"), (getter)pyVertexSpan_getVStartIdx,
        (setter)pyVertexSpan_setVStartIdx,
        _pycs("The first vertex in this Span"), NULL },
    { _pycs("VLength"), (getter)pyVertexSpan_getVLength,
        (setter)pyVertexSpan_setVLength,
        _pycs("The number of vertices in this Span"), NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyVertexSpan_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plVertexSpan",          /* tp_name */
    sizeof(pyVertexSpan),               /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plVertexSpan wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyVertexSpan_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyVertexSpan_new,                   /* tp_new */
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

PyObject* Init_pyVertexSpan_Type() {
    pyVertexSpan_Type.tp_base = &pySpan_Type;
    if (PyType_Ready(&pyVertexSpan_Type) < 0)
        return NULL;

    Py_INCREF(&pyVertexSpan_Type);
    return (PyObject*)&pyVertexSpan_Type;
}

int pyVertexSpan_Check(PyObject* obj) {
    if (obj->ob_type == &pyVertexSpan_Type
        || PyType_IsSubtype(obj->ob_type, &pyVertexSpan_Type))
        return 1;
    return 0;
}

PyObject* pyVertexSpan_FromVertexSpan(plVertexSpan* span) {
    if (span == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyVertexSpan* obj = PyObject_New(pyVertexSpan, &pyVertexSpan_Type);
    obj->fThis = span;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
