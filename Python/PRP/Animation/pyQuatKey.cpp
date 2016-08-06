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
#include "Math/pyGeometry3.h"

extern "C" {

static int pyQuatKey___init__(pyQuatKey* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyQuatKey_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatKey* self = (pyQuatKey*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsQuatKey();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatKey_getValue(pyQuatKey* self, void*) {
    return pyQuat_FromQuat(self->fThis->fValue);
}

static int pyQuatKey_setValue(pyQuatKey* self, PyObject* value, void*) {
    if (value == NULL || !pyQuat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be an hsQuat");
        return -1;
    }
    self->fThis->fValue = *((pyQuat*)value)->fThis;
    return 0;
}

static PyGetSetDef pyQuatKey_GetSet[] = {
    { _pycs("value"), (getter)pyQuatKey_getValue, (setter)pyQuatKey_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyQuatKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsQuatKey",             /* tp_name */
    sizeof(pyQuatKey),                  /* tp_basicsize */
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
    "hsQuatKey wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyQuatKey_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyQuatKey___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatKey_new,                      /* tp_new */
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

PyObject* Init_pyQuatKey_Type() {
    pyQuatKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyQuatKey_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatKey_Type);
    return (PyObject*)&pyQuatKey_Type;
}

int pyQuatKey_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatKey_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatKey_Type))
        return 1;
    return 0;
}

PyObject* pyQuatKey_FromQuatKey(hsQuatKey* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatKey* pyobj = PyObject_New(pyQuatKey, &pyQuatKey_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
