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

#include "pyResponderModifier.h"

#include <PRP/Modifier/plResponderModifier.h>
#include "PRP/pyCreatable.h"
#include "PRP/Message/pyMessage.h"

extern "C" {

static void pyResponderModifier_Cmd_dealloc(pyResponderModifier_Cmd* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyResponderModifier_Cmd___init__(pyResponderModifier_Cmd* self, PyObject* args, PyObject* /*kwds*/) {
    pyMessage* msg = NULL;
    int waitOn = -1;
    if (!PyArg_ParseTuple(args, "|Oi", &msg, &waitOn)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a message and an int");
        return -1;
    }
    if (msg != NULL && !pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a message and an int");
        return -1;
    }
    if (msg != NULL) {
        self->fThis->fMsg = msg->fThis;
        msg->fPyOwned = false;
    } else {
        self->fThis->fMsg = NULL;
    }
    self->fThis->fWaitOn = waitOn;
    return 0;
}

static PyObject* pyResponderModifier_Cmd_new(PyTypeObject* type, PyObject* /*args*/, PyObject* /*kwds*/) {
    pyResponderModifier_Cmd* self = (pyResponderModifier_Cmd*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plResponderModifier::plResponderCmd();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyResponderModifier_Cmd_getMsg(pyResponderModifier_Cmd* self, void*) {
    return ICreate(self->fThis->fMsg);
}

static PyObject* pyResponderModifier_Cmd_getWaitOn(pyResponderModifier_Cmd* self, void*) {
    return PyInt_FromLong(self->fThis->fWaitOn);
}

static int pyResponderModifier_Cmd_setMsg(pyResponderModifier_Cmd* self, PyObject* value, void*) {
    if (value == NULL || !pyMessage_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "msg should be a plMessage");
        return -1;
    }
    self->fThis->fMsg = ((pyMessage*)value)->fThis;
    ((pyMessage*)value)->fPyOwned = false;
    return 0;
}

static int pyResponderModifier_Cmd_setWaitOn(pyResponderModifier_Cmd* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waitOn should be an int");
        return -1;
    }
    self->fThis->fWaitOn = PyInt_AsLong(value);
    return 0;
}

static PyGetSetDef pyResponderModifier_Cmd_GetSet[] = {
    { _pycs("msg"), (getter)pyResponderModifier_Cmd_getMsg,
        (setter)pyResponderModifier_Cmd_setMsg, NULL, NULL },
    { _pycs("waitOn"), (getter)pyResponderModifier_Cmd_getWaitOn,
        (setter)pyResponderModifier_Cmd_setWaitOn, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyResponderModifier_Cmd_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plResponderModifier_Cmd", /* tp_name */
    sizeof(pyResponderModifier_Cmd),    /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyResponderModifier_Cmd_dealloc, /* tp_dealloc */
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
    "plResponderModifier::plResponderCmd wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyResponderModifier_Cmd_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyResponderModifier_Cmd___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyResponderModifier_Cmd_new,        /* tp_new */
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

PyObject* Init_pyResponderModifier_Cmd_Type() {
    if (PyType_Ready(&pyResponderModifier_Cmd_Type) < 0)
        return NULL;

    Py_INCREF(&pyResponderModifier_Cmd_Type);
    return (PyObject*)&pyResponderModifier_Cmd_Type;
}

int pyResponderModifier_Cmd_Check(PyObject* obj) {
    if (obj->ob_type == &pyResponderModifier_Cmd_Type
        || PyType_IsSubtype(obj->ob_type, &pyResponderModifier_Cmd_Type))
        return 1;
    return 0;
}

PyObject* pyResponderModifier_Cmd_FromResponderCmd(plResponderModifier::plResponderCmd* cmd) {
    if (cmd == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyResponderModifier_Cmd* pyobj = PyObject_New(pyResponderModifier_Cmd, &pyResponderModifier_Cmd_Type);
    pyobj->fThis = cmd;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
