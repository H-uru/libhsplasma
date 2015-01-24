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
#include "Math/pyMatrix.h"

extern "C" {

static int pyMatrix44Key___init__(pyMatrix44Key* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyMatrix44Key_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrix44Key* self = (pyMatrix44Key*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsMatrix44Key();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrix44Key_getValue(pyMatrix44Key* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->fValue);
}

static int pyMatrix44Key_setValue(pyMatrix44Key* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix44_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be an hsMatrix44");
        return -1;
    }
    self->fThis->fValue = *((pyMatrix44*)value)->fThis;
    return 0;
}

static PyGetSetDef pyMatrix44Key_GetSet[] = {
    { _pycs("value"), (getter)pyMatrix44Key_getValue,
        (setter)pyMatrix44Key_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMatrix44Key_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsMatrix44Key",         /* tp_name */
    sizeof(pyMatrix44Key),              /* tp_basicsize */
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
    "hsMatrix44Key wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyMatrix44Key_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyMatrix44Key___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrix44Key_new,                  /* tp_new */
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

PyObject* Init_pyMatrix44Key_Type() {
    pyMatrix44Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyMatrix44Key_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrix44Key_Type);
    return (PyObject*)&pyMatrix44Key_Type;
}

int pyMatrix44Key_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrix44Key_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrix44Key_Type))
        return 1;
    return 0;
}

PyObject* pyMatrix44Key_FromMatrix44Key(hsMatrix44Key* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrix44Key* pyobj = PyObject_New(pyMatrix44Key, &pyMatrix44Key_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
