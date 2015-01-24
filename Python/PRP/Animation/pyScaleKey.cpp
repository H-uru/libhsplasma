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

static int pyScaleKey___init__(pyScaleKey* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyScaleKey_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScaleKey* self = (pyScaleKey*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsScaleKey();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScaleKey_getInTan(pyScaleKey* self, void*) {
    return pyVector3_FromVector3(self->fThis->fInTan);
}

static PyObject* pyScaleKey_getOutTan(pyScaleKey* self, void*) {
    return pyVector3_FromVector3(self->fThis->fOutTan);
}

static PyObject* pyScaleKey_getValue(pyScaleKey* self, void*) {
    return Py_BuildValue("OO",
                         pyVector3_FromVector3(self->fThis->fS),
                         pyQuat_FromQuat(self->fThis->fQ));
}

static int pyScaleKey_setInTan(pyScaleKey* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "inTan should be an hsVector3");
        return -1;
    }
    self->fThis->fInTan = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyScaleKey_setOutTan(pyScaleKey* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "outTan should be an hsVector3");
        return -1;
    }
    self->fThis->fOutTan = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyScaleKey_setValue(pyScaleKey* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_Size(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    PyObject* s = PyTuple_GetItem(value, 0);
    PyObject* q = PyTuple_GetItem(value, 1);
    if (!pyVector3_Check(s) || !pyQuat_Check(q)) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    self->fThis->fS = *((pyVector3*)s)->fThis;
    self->fThis->fQ = *((pyQuat*)q)->fThis;
    return 0;
}

static PyGetSetDef pyScaleKey_GetSet[] = {
    { _pycs("inTan"), (getter)pyScaleKey_getInTan, (setter)pyScaleKey_setInTan, NULL, NULL },
    { _pycs("outTan"), (getter)pyScaleKey_getOutTan, (setter)pyScaleKey_setOutTan, NULL, NULL },
    { _pycs("value"), (getter)pyScaleKey_getValue, (setter)pyScaleKey_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScaleKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsScaleKey",            /* tp_name */
    sizeof(pyScaleKey),                 /* tp_basicsize */
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
    "hsScaleKey wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyScaleKey_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyScaleKey___init__,      /* tp_init */
    NULL,                               /* tp_alloc */
    pyScaleKey_new,                     /* tp_new */
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

PyObject* Init_pyScaleKey_Type() {
    pyScaleKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyScaleKey_Type) < 0)
        return NULL;

    Py_INCREF(&pyScaleKey_Type);
    return (PyObject*)&pyScaleKey_Type;
}

int pyScaleKey_Check(PyObject* obj) {
    if (obj->ob_type == &pyScaleKey_Type
        || PyType_IsSubtype(obj->ob_type, &pyScaleKey_Type))
        return 1;
    return 0;
}

PyObject* pyScaleKey_FromScaleKey(hsScaleKey* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScaleKey* pyobj = PyObject_New(pyScaleKey, &pyScaleKey_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
