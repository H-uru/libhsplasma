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

#include "pyDynamicTextMap.h"

#include <PRP/Surface/plDynamicTextMap.h>
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

static PyObject* pyDynamicTextMap_getInitBuffer(pyDynamicTextMap* self, void*) {
    PyObject* data = PyList_New(self->fThis->getInitBufferSize());
    for (size_t i=0; i<self->fThis->getInitBufferSize(); i++)
        PyList_SET_ITEM(data, i, PyInt_FromLong(self->fThis->getInitBuffer()[i]));
    return data;
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

PY_PROPERTY(unsigned int, DynamicTextMap, visWidth, getVisWidth, setVisWidth)
PY_PROPERTY(unsigned int, DynamicTextMap, visHeight, getVisHeight, setVisHeight)
PY_PROPERTY(bool, DynamicTextMap, hasAlpha, hasAlpha, setHasAlpha)

static PyGetSetDef pyDynamicTextMap_GetSet[] = {
    pyDynamicTextMap_visWidth_getset,
    pyDynamicTextMap_visHeight_getset,
    pyDynamicTextMap_hasAlpha_getset,
    { _pycs("initBuffer"), (getter)pyDynamicTextMap_getInitBuffer,
        (setter)pyDynamicTextMap_setInitBuffer, NULL, NULL },
    PY_GETSET_TERMINATOR
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

    NULL,                               /* tp_methods */
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

PY_PLASMA_IFC_METHODS(DynamicTextMap, plDynamicTextMap)

}
