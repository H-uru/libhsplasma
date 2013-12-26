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
#include <PRP/Geometry/plIcicle.h>
#include "pySpan.h"
#include "pyGBufferGroup.h"

extern "C" {

static PyObject* pyIcicle_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyIcicle* self = (pyIcicle*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plIcicle();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyIcicle_getIBufferIdx(pyIcicle* self, void*) {
    return PyInt_FromLong(self->fThis->getIBufferIdx());
}

static PyObject* pyIcicle_getIStartIdx(pyIcicle* self, void*) {
    return PyInt_FromLong(self->fThis->getIStartIdx());
}

static PyObject* pyIcicle_getILength(pyIcicle* self, void*) {
    return PyInt_FromLong(self->fThis->getILength());
}

static PyObject* pyIcicle_getSortData(pyIcicle* self, void*) {
    int size = self->fThis->getILength() / 3;
    const plGBufferTriangle* sortData = self->fThis->getSortData();
    if (sortData == NULL) {
        PyObject* list = PyList_New(0);
        return list;
    } else {
        PyObject* list = PyList_New(size);
        for (int i=0; i<size; i++)
            PyList_SET_ITEM(list, i, pyGBufferTriangle_FromGBufferTriangle(sortData[i]));
        return list;
    }
}

static int pyIcicle_setIBufferIdx(pyIcicle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "IBufferIdx should be an int");
        return -1;
    }
    self->fThis->setIBufferIdx(PyInt_AsLong(value));
    return 0;
}

static int pyIcicle_setIStartIdx(pyIcicle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "IStartIdx should be an int");
        return -1;
    }
    self->fThis->setIStartIdx(PyInt_AsLong(value));
    return 0;
}

static int pyIcicle_setILength(pyIcicle* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ILength should be an int");
        return -1;
    }
    self->fThis->setILength(PyInt_AsLong(value));
    return 0;
}

static int pyIcicle_setSortData(pyIcicle* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setSortData(NULL);
        return 0;
    } else if (PyList_Check(value)) {
        int size = PyList_Size(value);
        plGBufferTriangle* sortData = new plGBufferTriangle[size];
        for (int i=0; i<size; i++) {
            if (!pyGBufferTriangle_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "sortData should be a list of plGBufferTriangles");
                return -1;
            }
            sortData[i] = *((pyGBufferTriangle*)PyList_GetItem(value, i))->fThis;
        }
        self->fThis->setSortData(sortData);
        delete[] sortData;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "sortData should be a list of plGBufferTriangles");
        return -1;
    }
}

static PyGetSetDef pyIcicle_GetSet[] = {
    { _pycs("IBufferIdx"), (getter)pyIcicle_getIBufferIdx, (setter)pyIcicle_setIBufferIdx,
      _pycs("The Face Index Buffer index"), NULL },
    { _pycs("IStartIdx"), (getter)pyIcicle_getIStartIdx, (setter)pyIcicle_setIStartIdx,
      _pycs("The first face index in this Span"), NULL },
    { _pycs("ILength"), (getter)pyIcicle_getILength, (setter)pyIcicle_setILength,
      _pycs("The number of face indices in this Span (faces * 3)"), NULL },
    { _pycs("sortData"), (getter)pyIcicle_getSortData, (setter)pyIcicle_setSortData,
      _pycs("Optional face sort data"), NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyIcicle_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plIcicle",              /* tp_name */
    sizeof(pyIcicle),                   /* tp_basicsize */
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
    "plIcicle wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyIcicle_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyIcicle_new,                       /* tp_new */
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

PyObject* Init_pyIcicle_Type() {
    pyIcicle_Type.tp_base = &pyVertexSpan_Type;
    if (PyType_Ready(&pyIcicle_Type) < 0)
        return NULL;

    Py_INCREF(&pyIcicle_Type);
    return (PyObject*)&pyIcicle_Type;
}

int pyIcicle_Check(PyObject* obj) {
    if (obj->ob_type == &pyIcicle_Type
        || PyType_IsSubtype(obj->ob_type, &pyIcicle_Type))
        return 1;
    return 0;
}

PyObject* pyIcicle_FromIcicle(plIcicle* span) {
    if (span == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyIcicle* obj = PyObject_New(pyIcicle, &pyIcicle_Type);
    obj->fThis = span;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
