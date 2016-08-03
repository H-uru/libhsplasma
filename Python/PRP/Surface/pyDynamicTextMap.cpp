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
#include <PRP/Surface/plDynamicTextMap.h>
#include "pyDynamicTextMap.h"
#include "pyBitmap.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyDynamicTextMap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDynamicTextMap* self = (pyDynamicTextMap*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDynamicTextMap();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDynamicTextMap_getWidth(pyDynamicTextMap* self, void*) {
    return PyInt_FromLong(self->fThis->getVisWidth());
}

static PyObject* pyDynamicTextMap_getHeight(pyDynamicTextMap* self, void*) {
    return PyInt_FromLong(self->fThis->getVisHeight());
}

static PyObject* pyDynamicTextMap_getHasAlpha(pyDynamicTextMap* self, void*) {
    return PyBool_FromLong(self->fThis->hasAlpha() ? 1 : 0);
}

static PyObject* pyDynamicTextMap_getInitBuffer(pyDynamicTextMap* self, void*) {
    PyObject* data = PyList_New(self->fThis->getInitBufferSize());
    for (size_t i=0; i<self->fThis->getInitBufferSize(); i++)
        PyList_SET_ITEM(data, i, PyInt_FromLong(self->fThis->getInitBuffer()[i]));
    return data;
}

static int pyDynamicTextMap_setWidth(pyDynamicTextMap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visWidth should be an int");
        return -1;
    }
    self->fThis->setVisWidth(PyInt_AsLong(value));
    return 0;
}

static int pyDynamicTextMap_setHeight(pyDynamicTextMap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visHeight should be an int");
        return -1;
    }
    self->fThis->setVisHeight(PyInt_AsLong(value));
    return 0;
}

static int pyDynamicTextMap_setHasAlpha(pyDynamicTextMap* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "hasAlpha should be a bool");
        return -1;
    }
    self->fThis->setHasAlpha(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyDynamicTextMap_setInitBuffer(pyDynamicTextMap* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setInitBuffer(NULL, 0);
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "initBuffer should be a list of ints");
        return -1;
    }
    int len = PyList_Size(value);
    unsigned int* buf = new unsigned int[len];
    for (int i=0; i<len; i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyInt_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "initBuffer should be a list of ints");
            delete[] buf;
            return -1;
        }
        buf[i] = PyInt_AsLong(itm);
    }
    self->fThis->setInitBuffer(buf, (size_t)len);
    delete[] buf;
    return 0;
}

static PyMethodDef pyDynamicTextMap_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyDynamicTextMap_GetSet[] = {
    { _pycs("visWidth"), (getter)pyDynamicTextMap_getWidth,
        (setter)pyDynamicTextMap_setWidth, NULL, NULL },
    { _pycs("visHeight"), (getter)pyDynamicTextMap_getHeight,
        (setter)pyDynamicTextMap_setHeight, NULL, NULL },
    { _pycs("hasAlpha"), (getter)pyDynamicTextMap_getHasAlpha,
        (setter)pyDynamicTextMap_setHasAlpha, NULL, NULL },
    { _pycs("initBuffer"), (getter)pyDynamicTextMap_getInitBuffer,
        (setter)pyDynamicTextMap_setInitBuffer, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDynamicTextMap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDynamicTextMap",      /* tp_name */
    sizeof(pyDynamicTextMap),           /* tp_basicsize */
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
    "plDynamicTextMap wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDynamicTextMap_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    pyDynamicTextMap_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDynamicTextMap_new,               /* tp_new */
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

PyObject* Init_pyDynamicTextMap_Type() {
    pyDynamicTextMap_Type.tp_base = &pyMipmap_Type;
    if (PyType_Ready(&pyDynamicTextMap_Type) < 0)
        return NULL;

    Py_INCREF(&pyDynamicTextMap_Type);
    return (PyObject*)&pyDynamicTextMap_Type;
}

int pyDynamicTextMap_Check(PyObject* obj) {
    if (obj->ob_type == &pyDynamicTextMap_Type
        || PyType_IsSubtype(obj->ob_type, &pyDynamicTextMap_Type))
        return 1;
    return 0;
}

PyObject* pyDynamicTextMap_FromDynamicTextMap(class plDynamicTextMap* img) {
    if (img == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDynamicTextMap* pybmp = PyObject_New(pyDynamicTextMap, &pyDynamicTextMap_Type);
    pybmp->fThis = img;
    pybmp->fPyOwned = false;
    return (PyObject*)pybmp;
}

}
