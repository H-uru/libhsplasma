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

#include "pyDrawableSpans.h"

#include <PRP/Geometry/plDrawableSpans.h>

extern "C" {

static void pyDISpanIndex_dealloc(pyDISpanIndex* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyDISpanIndex___init__(pyDISpanIndex* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyDISpanIndex_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDISpanIndex* self = (pyDISpanIndex*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plDISpanIndex();
    return (PyObject*)self;
}

static PyObject* pyDISpanIndex_getFlags(pyDISpanIndex* self, void*) {
    return  PyInt_FromLong(self->fThis->fFlags);
}

static PyObject* pyDISpanIndex_getIndices(pyDISpanIndex* self, void*) {
    PyObject* list = PyList_New(self->fThis->fIndices.size());
    for (size_t i=0; i<self->fThis->fIndices.size(); i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(self->fThis->fIndices[i]));
    return list;
}

static int pyDISpanIndex_setFlags(pyDISpanIndex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->fFlags = PyInt_AsLong(value);
    return 0;
}

static int pyDISpanIndex_setIndices(pyDISpanIndex* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->fIndices.clear();
        return 0;
    } else if (PyList_Check(value)) {
        self->fThis->fIndices.resize(PyList_Size(value));
        for (size_t i=0; i<self->fThis->fIndices.size(); i++) {
            if (!PyInt_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
                return -1;
            }
            self->fThis->fIndices[i] = PyInt_AsLong(PyList_GetItem(value, i));
        }
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
        return -1;
    }
}

static PyGetSetDef pyDISpanIndex_GetSet[] = {
    { _pycs("flags"), (getter)pyDISpanIndex_getFlags,
        (setter)pyDISpanIndex_setFlags, NULL, NULL },
    { _pycs("indices"), (getter)pyDISpanIndex_getIndices,
        (setter)pyDISpanIndex_setIndices,
        _pycs("Collection of span index groups for the spans"), NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDISpanIndex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDISpanIndex",         /* tp_name */
    sizeof(pyDISpanIndex),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyDISpanIndex_dealloc,  /* tp_dealloc */
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
    "plDISpanIndex wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyDISpanIndex_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyDISpanIndex___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyDISpanIndex_new,                  /* tp_new */
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

PyObject* Init_pyDISpanIndex_Type() {
    if (PyType_Ready(&pyDISpanIndex_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyDISpanIndex_Type.tp_dict, "kNone",
                         PyInt_FromLong(plDISpanIndex::kNone));
    PyDict_SetItemString(pyDISpanIndex_Type.tp_dict, "kMatrixOnly",
                         PyInt_FromLong(plDISpanIndex::kMatrixOnly));
    PyDict_SetItemString(pyDISpanIndex_Type.tp_dict, "kDontTransformSpans",
                         PyInt_FromLong(plDISpanIndex::kDontTransformSpans));

    Py_INCREF(&pyDISpanIndex_Type);
    return (PyObject*)&pyDISpanIndex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(DISpanIndex, plDISpanIndex)

}
