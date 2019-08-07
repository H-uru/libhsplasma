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

PY_PLASMA_NEW(Message, plMessage)

PY_METHOD_VA(Message, addReceiver,
    "Params: callback\n"
    "Register a receiver key to the object")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return nullptr;
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
        return nullptr;
    }
    self->fThis->delReceiver(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Message, clearReceivers, "Remove all receivers from the object")
{
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

static PyMethodDef pyMessage_Methods[] = {
    pyMessage_addReceiver_method,
    pyMessage_delReceiver_method,
    pyMessage_clearReceivers_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(Message, receivers)
{
    PyObject* list = PyTuple_New(self->fThis->getReceivers().size());
    for (size_t i=0; i<self->fThis->getReceivers().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(Message, receivers, "To add receivers, use addReceiver()")
PY_PROPERTY_GETSET_DECL(Message, receivers)

PY_PROPERTY(plKey, Message, sender, getSender, setSender)
PY_PROPERTY(double, Message, timeStamp, getTimeStamp, setTimeStamp)
PY_PROPERTY(unsigned int, Message, BCastFlags, getBCastFlags, setBCastFlags)

static PyGetSetDef pyMessage_GetSet[] = {
    pyMessage_sender_getset,
    pyMessage_timeStamp_getset,
    pyMessage_BCastFlags_getset,
    pyMessage_receivers_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Message, plMessage, "plMessage wrapper")

PY_PLASMA_TYPE_INIT(Message)
{
    pyMessage_Type.tp_new = pyMessage_new;
    pyMessage_Type.tp_methods = pyMessage_Methods;
    pyMessage_Type.tp_getset = pyMessage_GetSet;
    pyMessage_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyMessage_Type) < 0)
        return nullptr;

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
