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
#include <PRP/Modifier/plResponderModifier.h>
#include "pyResponderModifier.h"
#include "PRP/Message/pyMessage.h"

extern "C" {

static void pyResponderModifier_State_dealloc(pyResponderModifier_State* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyResponderModifier_State___init__(pyResponderModifier_State* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyResponderModifier_State_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyResponderModifier_State* self = (pyResponderModifier_State*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plResponderModifier::plResponderState();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyResponderModifier_State_addCommand(pyResponderModifier_State* self, PyObject* args) {
    pyMessage* msg;
    int waitOn;
    if (!PyArg_ParseTuple(args, "Oi", &msg, &waitOn)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects plMessage, int");
        return NULL;
    }
    if (!pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects plMessage, int");
        return NULL;
    }
    self->fThis->addCommand(msg->fThis, waitOn);
    msg->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_State_delCommand(pyResponderModifier_State* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCommand expects an int");
        return NULL;
    }
    self->fThis->delCommand(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_State_clearCommands(pyResponderModifier_State* self) {
    self->fThis->clearCommands();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_State_getCommands(pyResponderModifier_State* self, void*) {
    PyObject* list = PyList_New(self->fThis->fCmds.getSize());
    for (size_t i=0; i<self->fThis->fCmds.getSize(); i++)
        PyList_SET_ITEM(list, i, pyResponderModifier_Cmd_FromResponderCmd(self->fThis->fCmds[i]));
    return list;
}

static PyObject* pyResponderModifier_State_getNumCallbacks(pyResponderModifier_State* self, void*) {
    return PyInt_FromLong(self->fThis->fNumCallbacks);
}

static PyObject* pyResponderModifier_State_getSwitch(pyResponderModifier_State* self, void*) {
    return PyInt_FromLong(self->fThis->fSwitchToState);
}

static PyObject* pyResponderModifier_State_getWaits(pyResponderModifier_State* self, void*) {
    PyObject* dict = PyDict_New();
    std::map<hsByte, hsByte>::iterator wp = self->fThis->fWaitToCmd.begin();
    for ( ; wp != self->fThis->fWaitToCmd.end(); wp++)
        PyDict_SetItem(dict, PyInt_FromLong(wp->first), PyInt_FromLong(wp->second));
    return dict;
}

static int pyResponderModifier_State_setCommands(pyResponderModifier_State* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_TypeError, "To add commands, use addCommand");
    return -1;
}

static int pyResponderModifier_State_setNumCallbacks(pyResponderModifier_State* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "numCallbacks should be an int");
        return -1;
    }
    self->fThis->fNumCallbacks = PyInt_AsLong(value);
    return 0;
}

static int pyResponderModifier_State_setSwitch(pyResponderModifier_State* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "switchToState should be an int");
        return -1;
    }
    self->fThis->fSwitchToState = PyInt_AsLong(value);
    return 0;
}

static int pyResponderModifier_State_setWaits(pyResponderModifier_State* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->fWaitToCmd.clear();
        return 0;
    }
    if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waitToCmd should be a dict { int => int }");
        return -1;
    }

    PyObject *dkey, *dvalue;
    Py_ssize_t pos = 0;
    self->fThis->fWaitToCmd.clear();

    while (PyDict_Next(value, &pos, &dkey, &dvalue)) {
        if (!PyInt_Check(dkey) || !PyInt_Check(dvalue)) {
            PyErr_SetString(PyExc_TypeError, "waitToCmd should be a dict { int => int }");
            return -1;
        }
        self->fThis->fWaitToCmd[PyInt_AsLong(dkey)] = PyInt_AsLong(dvalue);
    }
    return 0;
}

static PyMethodDef pyResponderModifier_State_Methods[] = {
    { "addCommand", (PyCFunction)pyResponderModifier_State_addCommand, METH_VARARGS,
      "Params: msg, waitOn\n"
      "Add a command to the Responder state" },
    { "delCommand", (PyCFunction)pyResponderModifier_State_delCommand, METH_VARARGS,
      "Params: idx\n"
      "Delete a command from the Responder state" },
    { "clearCommands", (PyCFunction)pyResponderModifier_State_clearCommands, METH_NOARGS,
      "Delete all commands from the Responder state" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyResponderModifier_State_GetSet[] = {
    { "commands", (getter)pyResponderModifier_State_getCommands, (setter)pyResponderModifier_State_setCommands, NULL, NULL },
    { "numCallbacks", (getter)pyResponderModifier_State_getNumCallbacks, (setter)pyResponderModifier_State_setNumCallbacks, NULL, NULL },
    { "switchToState", (getter)pyResponderModifier_State_getSwitch, (setter)pyResponderModifier_State_setSwitch, NULL, NULL },
    { "waitToCmd", (getter)pyResponderModifier_State_getWaits, (setter)pyResponderModifier_State_setWaits, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyResponderModifier_State_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plResponderModifier_State", /* tp_name */
    sizeof(pyResponderModifier_State),  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyResponderModifier_State_dealloc, /* tp_dealloc */
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
    "plResponderModifier::plResponderState wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyResponderModifier_State_Methods,  /* tp_methods */
    NULL,                               /* tp_members */
    pyResponderModifier_State_GetSet,   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyResponderModifier_State___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyResponderModifier_State_new,      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyResponderModifier_State_Type() {
    if (PyType_Ready(&pyResponderModifier_State_Type) < 0)
        return NULL;

    Py_INCREF(&pyResponderModifier_State_Type);
    return (PyObject*)&pyResponderModifier_State_Type;
}

int pyResponderModifier_State_Check(PyObject* obj) {
    if (obj->ob_type == &pyResponderModifier_State_Type
        || PyType_IsSubtype(obj->ob_type, &pyResponderModifier_State_Type))
        return 1;
    return 0;
}

PyObject* pyResponderModifier_State_FromResponderState(plResponderModifier::plResponderState* state) {
    if (state == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyResponderModifier_State* pyobj = PyObject_New(pyResponderModifier_State, &pyResponderModifier_State_Type);
    pyobj->fThis = state;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
