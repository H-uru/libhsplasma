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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>

extern "C" {

static int pyScalarKey___init__(pyScalarKey* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyScalarKey_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarKey* self = (pyScalarKey*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsScalarKey();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarKey_getInTan(pyScalarKey* self, void*) {
    return PyFloat_FromDouble(self->fThis->fInTan);
}

static PyObject* pyScalarKey_getOutTan(pyScalarKey* self, void*) {
    return PyFloat_FromDouble(self->fThis->fOutTan);
}

static PyObject* pyScalarKey_getValue(pyScalarKey* self, void*) {
    return PyFloat_FromDouble(self->fThis->fValue);
}

static int pyScalarKey_setInTan(pyScalarKey* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "inTan should be a float");
        return -1;
    }
    self->fThis->fInTan = PyFloat_AsDouble(value);
    return 0;
}

static int pyScalarKey_setOutTan(pyScalarKey* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "outTan should be a float");
        return -1;
    }
    self->fThis->fOutTan = PyFloat_AsDouble(value);
    return 0;
}

static int pyScalarKey_setValue(pyScalarKey* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be a float");
        return -1;
    }
    self->fThis->fValue = PyFloat_AsDouble(value);
    return 0;
}

static PyGetSetDef pyScalarKey_GetSet[] = {
    { _pycs("inTan"), (getter)pyScalarKey_getInTan, (setter)pyScalarKey_setInTan, NULL, NULL },
    { _pycs("outTan"), (getter)pyScalarKey_getOutTan, (setter)pyScalarKey_setOutTan, NULL, NULL },
    { _pycs("value"), (getter)pyScalarKey_getValue, (setter)pyScalarKey_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScalarKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsScalarKey",           /* tp_name */
    sizeof(pyScalarKey),                /* tp_basicsize */
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
    "hsScalarKey wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyScalarKey_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyScalarKey___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarKey_new,                    /* tp_new */
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

PyObject* Init_pyScalarKey_Type() {
    pyScalarKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyScalarKey_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarKey_Type);
    return (PyObject*)&pyScalarKey_Type;
}

int pyScalarKey_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarKey_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarKey_Type))
        return 1;
    return 0;
}

PyObject* pyScalarKey_FromScalarKey(hsScalarKey* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarKey* pyobj = PyObject_New(pyScalarKey, &pyScalarKey_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
