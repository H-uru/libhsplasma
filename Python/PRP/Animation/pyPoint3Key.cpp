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
#include <PRP/Animation/hsKeys.h>
#include "pyKeys.h"
#include "Math/pyGeometry3.h"

extern "C" {

static int pyPoint3Key___init__(pyPoint3Key* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyPoint3Key_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPoint3Key* self = (pyPoint3Key*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsPoint3Key();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPoint3Key_getInTan(pyPoint3Key* self, void*) {
    return pyVector3_FromVector3(self->fThis->fInTan);
}

static PyObject* pyPoint3Key_getOutTan(pyPoint3Key* self, void*) {
    return pyVector3_FromVector3(self->fThis->fOutTan);
}

static PyObject* pyPoint3Key_getValue(pyPoint3Key* self, void*) {
    return pyVector3_FromVector3(self->fThis->fValue);
}

static int pyPoint3Key_setInTan(pyPoint3Key* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "inTan should be an hsVector3");
        return -1;
    }
    self->fThis->fInTan = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyPoint3Key_setOutTan(pyPoint3Key* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "outTan should be an hsVector3");
        return -1;
    }
    self->fThis->fOutTan = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyPoint3Key_setValue(pyPoint3Key* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be an hsVector3");
        return -1;
    }
    self->fThis->fValue = *((pyVector3*)value)->fThis;
    return 0;
}

static PyGetSetDef pyPoint3Key_GetSet[] = {
    { _pycs("inTan"), (getter)pyPoint3Key_getInTan, (setter)pyPoint3Key_setInTan, NULL, NULL },
    { _pycs("outTan"), (getter)pyPoint3Key_getOutTan, (setter)pyPoint3Key_setOutTan, NULL, NULL },
    { _pycs("value"), (getter)pyPoint3Key_getValue, (setter)pyPoint3Key_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPoint3Key_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsPoint3Key",             /* tp_name */
    sizeof(pyPoint3Key),                /* tp_basicsize */
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
    "hsPoint3Key wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyPoint3Key_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyPoint3Key___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyPoint3Key_new,                    /* tp_new */
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

PyObject* Init_pyPoint3Key_Type() {
    pyPoint3Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyPoint3Key_Type) < 0)
        return NULL;

    Py_INCREF(&pyPoint3Key_Type);
    return (PyObject*)&pyPoint3Key_Type;
}

int pyPoint3Key_Check(PyObject* obj) {
    if (obj->ob_type == &pyPoint3Key_Type
        || PyType_IsSubtype(obj->ob_type, &pyPoint3Key_Type))
        return 1;
    return 0;
}

PyObject* pyPoint3Key_FromPoint3Key(hsPoint3Key* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPoint3Key* pyobj = PyObject_New(pyPoint3Key, &pyPoint3Key_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
