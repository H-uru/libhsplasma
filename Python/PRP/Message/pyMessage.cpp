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
#include <PRP/Message/plMessage.h>
#include "pyMessage.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyMessage_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMessage* self = (pyMessage*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMessage();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMessage_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMessage_FromMessage(plMessage::Convert(IConvert(cre)));
}

static PyObject* pyMessage_addReceiver(pyMessage* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    self->fThis->addReceiver(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMessage_delReceiver(pyMessage* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }
    self->fThis->delReceiver(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMessage_clearReceivers(pyMessage* self) {
    self->fThis->clearReceivers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMessage_getSender(pyMessage* self, void*) {
    return pyKey_FromKey(self->fThis->getSender());
}

static PyObject* pyMessage_getTS(pyMessage* self, void*) {
    return PyFloat_FromDouble(self->fThis->getTimeStamp());
}

static PyObject* pyMessage_getFlags(pyMessage* self, void*) {
    return PyInt_FromLong(self->fThis->getBCastFlags());
}

static PyObject* pyMessage_getReceivers(pyMessage* self, void*) {
    PyObject* list = PyList_New(self->fThis->getReceivers().getSize());
    for (size_t i=0; i<self->fThis->getReceivers().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

static int pyMessage_setSender(pyMessage* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setSender(plKey());
        return 0;
    }
    if (!pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sender should be a plKey");
        return -1;
    }
    self->fThis->setSender(*((pyKey*)value)->fThis);
    return 0;
}

static int pyMessage_setTS(pyMessage* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "timeStamp should be a float");
        return -1;
    }
    self->fThis->setTimeStamp(PyFloat_AsDouble(value));
    return 0;
}
static int pyMessage_setFlags(pyMessage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "BCastFlags should be an int");
        return -1;
    }
    self->fThis->setBCastFlags(PyInt_AsLong(value));
    return 0;
}

static int pyMessage_setReceivers(pyMessage* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver()");
    return -1;
}

static PyMethodDef pyMessage_Methods[] = {
    { "Convert", (PyCFunction)pyMessage_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMessage" },
    { "addReceiver", (PyCFunction)pyMessage_addReceiver, METH_VARARGS,
      "Params: callback\n"
      "Register a receiver key to the object" },
    { "delReceiver", (PyCFunction)pyMessage_delReceiver, METH_VARARGS,
      "Params: idx\n"
      "Unregister a receiver key from the object" },
    { "clearReceivers", (PyCFunction)pyMessage_clearReceivers, METH_NOARGS,
      "Remove all receivers from the object" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMessage_GetSet[] = {
    { "sender", (getter)pyMessage_getSender, (setter)pyMessage_setSender, NULL, NULL },
    { "timeStamp", (getter)pyMessage_getTS, (setter)pyMessage_setTS, NULL, NULL },
    { "BCastFlags", (getter)pyMessage_getFlags, (setter)pyMessage_setFlags, NULL, NULL },
    { "receivers", (getter)pyMessage_getReceivers, (setter)pyMessage_setReceivers, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMessage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plMessage",               /* tp_name */
    sizeof(pyMessage),                  /* tp_basicsize */
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
    "plMessage wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMessage_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyMessage_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMessage_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMessage_Type() {
    pyMessage_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyMessage_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyMessage_Type.tp_dict, "kBCastNone",
                         PyInt_FromLong(plMessage::kBCastNone));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kBCastByType",
                         PyInt_FromLong(plMessage::kBCastByType));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kPropagateToChildren",
                         PyInt_FromLong(plMessage::kPropagateToChildren));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kBCastByExactType",
                         PyInt_FromLong(plMessage::kBCastByExactType));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kPropagateToModifiers",
                         PyInt_FromLong(plMessage::kPropagateToModifiers));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kClearAfterBCast",
                         PyInt_FromLong(plMessage::kClearAfterBCast));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetPropagate",
                         PyInt_FromLong(plMessage::kNetPropagate));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetSent",
                         PyInt_FromLong(plMessage::kNetSent));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetUseRelevanceRegions",
                         PyInt_FromLong(plMessage::kNetUseRelevanceRegions));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetForce",
                         PyInt_FromLong(plMessage::kNetForce));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetNonLocal",
                         PyInt_FromLong(plMessage::kNetNonLocal));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kLocalPropagate",
                         PyInt_FromLong(plMessage::kLocalPropagate));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetNonDeterministic",
                         PyInt_FromLong(plMessage::kNetNonDeterministic));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kMsgWatch",
                         PyInt_FromLong(plMessage::kMsgWatch));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetStartCascade",
                         PyInt_FromLong(plMessage::kNetStartCascade));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetAllowInterAge",
                         PyInt_FromLong(plMessage::kNetAllowInterAge));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetSendUnreliable",
                         PyInt_FromLong(plMessage::kNetSendUnreliable));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kCCRSendToAllPlayers",
                         PyInt_FromLong(plMessage::kCCRSendToAllPlayers));
    PyDict_SetItemString(pyMessage_Type.tp_dict, "kNetCreatedRemotely",
                         PyInt_FromLong(plMessage::kNetCreatedRemotely));

    Py_INCREF(&pyMessage_Type);
    return (PyObject*)&pyMessage_Type;
}

int pyMessage_Check(PyObject* obj) {
    if (obj->ob_type == &pyMessage_Type
        || PyType_IsSubtype(obj->ob_type, &pyMessage_Type))
        return 1;
    return 0;
}

PyObject* pyMessage_FromMessage(class plMessage* atc) {
    if (atc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMessage* pyobj = PyObject_New(pyMessage, &pyMessage_Type);
    pyobj->fThis = atc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
