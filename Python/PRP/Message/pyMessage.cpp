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

#include "pyMessage.h"

#include <PRP/Message/plMessage.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(Message, plMessage)

PY_METHOD_VA(Message, addReceiver,
    "Params: callback\n"
    "Register a receiver key to the object")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_VA(Message, delReceiver,
    "Params: idx\n"
    "Unregister a receiver key from the object")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }
    self->fThis->delReceiver(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Message, clearReceivers, "Remove all receivers from the object") {
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

static PyObject* pyMessage_getReceivers(pyMessage* self, void*) {
    PyObject* list = PyList_New(self->fThis->getReceivers().size());
    for (size_t i=0; i<self->fThis->getReceivers().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

static int pyMessage_setReceivers(pyMessage* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver()");
    return -1;
}

static PyMethodDef pyMessage_Methods[] = {
    pyMessage_addReceiver_method,
    pyMessage_delReceiver_method,
    pyMessage_clearReceivers_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plKey, Message, sender, getSender, setSender)
PY_PROPERTY(double, Message, timeStamp, getTimeStamp, setTimeStamp)
PY_PROPERTY(unsigned int, Message, BCastFlags, getBCastFlags, setBCastFlags)

static PyGetSetDef pyMessage_GetSet[] = {
    pyMessage_sender_getset,
    pyMessage_timeStamp_getset,
    pyMessage_BCastFlags_getset,
    { _pycs("receivers"), (getter)pyMessage_getReceivers,
        (setter)pyMessage_setReceivers, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyMessage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plMessage",             /* tp_name */
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

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyMessage_Type() {
    pyMessage_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyMessage_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(Message, "kBCastNone", plMessage::kBCastNone);
    PY_TYPE_ADD_CONST(Message, "kBCastByType", plMessage::kBCastByType);
    PY_TYPE_ADD_CONST(Message, "kPropagateToChildren", plMessage::kPropagateToChildren);
    PY_TYPE_ADD_CONST(Message, "kBCastByExactType", plMessage::kBCastByExactType);
    PY_TYPE_ADD_CONST(Message, "kPropagateToModifiers", plMessage::kPropagateToModifiers);
    PY_TYPE_ADD_CONST(Message, "kClearAfterBCast", plMessage::kClearAfterBCast);
    PY_TYPE_ADD_CONST(Message, "kNetPropagate", plMessage::kNetPropagate);
    PY_TYPE_ADD_CONST(Message, "kNetSent", plMessage::kNetSent);
    PY_TYPE_ADD_CONST(Message, "kNetUseRelevanceRegions", plMessage::kNetUseRelevanceRegions);
    PY_TYPE_ADD_CONST(Message, "kNetForce", plMessage::kNetForce);
    PY_TYPE_ADD_CONST(Message, "kNetNonLocal", plMessage::kNetNonLocal);
    PY_TYPE_ADD_CONST(Message, "kLocalPropagate", plMessage::kLocalPropagate);
    PY_TYPE_ADD_CONST(Message, "kNetNonDeterministic", plMessage::kNetNonDeterministic);
    PY_TYPE_ADD_CONST(Message, "kMsgWatch", plMessage::kMsgWatch);
    PY_TYPE_ADD_CONST(Message, "kNetStartCascade", plMessage::kNetStartCascade);
    PY_TYPE_ADD_CONST(Message, "kNetAllowInterAge", plMessage::kNetAllowInterAge);
    PY_TYPE_ADD_CONST(Message, "kNetSendUnreliable", plMessage::kNetSendUnreliable);
    PY_TYPE_ADD_CONST(Message, "kCCRSendToAllPlayers", plMessage::kCCRSendToAllPlayers);
    PY_TYPE_ADD_CONST(Message, "kNetCreatedRemotely", plMessage::kNetCreatedRemotely);

    Py_INCREF(&pyMessage_Type);
    return (PyObject*)&pyMessage_Type;
}

PY_PLASMA_IFC_METHODS(Message, plMessage)

}
