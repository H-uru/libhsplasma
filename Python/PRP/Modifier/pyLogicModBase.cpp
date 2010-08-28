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
#include <PRP/Modifier/plLogicModBase.h>
#include "pyLogicModifier.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Message/pyNotifyMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/pyCreatable.h"
#include "Util/pyBitVector.h"

extern "C" {

static PyObject* pyLogicModBase_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plLogicModBase is abstract");
    return NULL;
}

static PyObject* pyLogicModBase_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLogicModBase_FromLogicModBase(plLogicModBase::Convert(IConvert(cre)));
}

static PyObject* pyLogicModBase_clearCommands(pyLogicModBase* self) {
    self->fThis->clearCommands();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModBase_addCommand(pyLogicModBase* self, PyObject* args) {
    pyMessage* msg;
    if (!PyArg_ParseTuple(args, "O", &msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects a plMessage");
        return NULL;
    }
    if (!pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects a plMessage");
        return NULL;
    }
    self->fThis->addCommand(msg->fThis);
    msg->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModBase_delCommand(pyLogicModBase* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCommand expects an int");
        return NULL;
    }
    self->fThis->delCommand(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModBase_getFlag(pyLogicModBase* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getFlag expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getFlag(idx) ? 1 : 0);
}

static PyObject* pyLogicModBase_setFlag(pyLogicModBase* self, PyObject* args) {
    int idx, value;
    if (!PyArg_ParseTuple(args, "ii", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlag expects int, bool");
        return NULL;
    }
    self->fThis->setFlag(idx, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModBase_getCommands(pyLogicModBase* self, void*) {
    PyObject* list = PyList_New(self->fThis->getCommands().getSize());
    for (size_t i=0; i<self->fThis->getCommands().getSize(); i++)
        PyList_SET_ITEM(list, i, pyMessage_FromMessage(self->fThis->getCommands()[i]));
    return list;
}

static PyObject* pyLogicModBase_getNotify(pyLogicModBase* self, void*) {
    return pyNotifyMsg_FromNotifyMsg(self->fThis->getNotify());
}

static PyObject* pyLogicModBase_getDisabled(pyLogicModBase* self, void*) {
    return PyBool_FromLong(self->fThis->isDisabled() ? 1 : 0);
}

static int pyLogicModBase_setCommands(pyLogicModBase* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add commands, use addCommand");
    return -1;
}

static int pyLogicModBase_setNotify(pyLogicModBase* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setNotify(NULL);
        return 0;
    } else if (pyNotifyMsg_Check(value)) {
        self->fThis->setNotify(((pyNotifyMsg*)value)->fThis);
        ((pyNotifyMsg*)value)->fPyOwned = false;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "notify should be a plNotifyMsg");
        return -1;
    }
}

static int pyLogicModBase_setDisabled(pyLogicModBase* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "disabled should be a bool");
        return -1;
    }
    self->fThis->setDisabled(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyLogicModBase_Methods[] = {
    { "Convert", (PyCFunction)pyLogicModBase_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLogicModBase" },
    { "clearCommands", (PyCFunction)pyLogicModBase_clearCommands, METH_NOARGS,
      "Remove all commands" },
    { "addCommand", (PyCFunction)pyLogicModBase_addCommand, METH_VARARGS,
      "Params: key\n"
      "Add a command" },
    { "delCommand", (PyCFunction)pyLogicModBase_delCommand, METH_NOARGS,
      "Params: idx\n"
      "Remove a command" },
    { "getLogicFlag", (PyCFunction)pyLogicModBase_getFlag, METH_VARARGS,
      "Params: flag\n"
      "Returns True if the LogicMod flag is set" },
    { "setLogicFlag", (PyCFunction)pyLogicModBase_setFlag, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified LogicMod flag" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLogicModBase_GetSet[] = {
    { "commands", (getter)pyLogicModBase_getCommands, (setter)pyLogicModBase_setCommands, NULL, NULL },
    { "notify", (getter)pyLogicModBase_getNotify, (setter)pyLogicModBase_setNotify, NULL, NULL },
    { "disabled", (getter)pyLogicModBase_getDisabled, (setter)pyLogicModBase_setDisabled, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLogicModBase_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLogicModBase",          /* tp_name */
    sizeof(pyLogicModBase),             /* tp_basicsize */
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
    "plLogicModBase wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLogicModBase_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyLogicModBase_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLogicModBase_new,        /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLogicModBase_Type() {
    pyLogicModBase_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyLogicModBase_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kLocalElement",
                         PyInt_FromLong(plLogicModBase::kLocalElement));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kReset",
                         PyInt_FromLong(plLogicModBase::kReset));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kTriggered",
                         PyInt_FromLong(plLogicModBase::kTriggered));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kOneShot",
                         PyInt_FromLong(plLogicModBase::kOneShot));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kRequestingTrigger",
                         PyInt_FromLong(plLogicModBase::kRequestingTrigger));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kTypeActivator",
                         PyInt_FromLong(plLogicModBase::kTypeActivator));
    PyDict_SetItemString(pyLogicModBase_Type.tp_dict, "kMultiTrigger",
                         PyInt_FromLong(plLogicModBase::kMultiTrigger));

    Py_INCREF(&pyLogicModBase_Type);
    return (PyObject*)&pyLogicModBase_Type;
}

int pyLogicModBase_Check(PyObject* obj) {
    if (obj->ob_type == &pyLogicModBase_Type
        || PyType_IsSubtype(obj->ob_type, &pyLogicModBase_Type))
        return 1;
    return 0;
}

PyObject* pyLogicModBase_FromLogicModBase(plLogicModBase* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLogicModBase* pyobj = PyObject_New(pyLogicModBase, &pyLogicModBase_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
