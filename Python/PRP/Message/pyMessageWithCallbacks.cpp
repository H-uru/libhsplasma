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

#include "pyMessageWithCallbacks.h"

#include <PRP/Message/plMessageWithCallbacks.h>
#include "pyMessage.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(MessageWithCallbacks, plMessageWithCallbacks)

PY_METHOD_VA(MessageWithCallbacks, addCallback,
    "Params: key\n"
    "Adds a callback message")
{
    PyObject* msg;
    if (!(PyArg_ParseTuple(args, "O", &msg) && pyMessage_Check(msg))) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plMessage");
        return nullptr;
    }
    self->fThis->addCallback(((pyMessage*)msg)->fThis);
    ((pyMessage*)msg)->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(MessageWithCallbacks, clearCallbacks,
    "Removes all callback messages")
{
    self->fThis->clearCallbacks();
    Py_RETURN_NONE;
}

PY_METHOD_VA(MessageWithCallbacks, delCallback,
    "Params: idx\n"
    "Removes a callback message")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return nullptr;
    }
    if (size_t(idx) >= self->fThis->getCallbacks().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    self->fThis->delCallback((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyMessageWithCallbacks_Methods[] = {
    pyMessageWithCallbacks_addCallback_method,
    pyMessageWithCallbacks_clearCallbacks_method,
    pyMessageWithCallbacks_delCallback_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(MessageWithCallbacks, callbacks)
{
    const std::vector<plMessage*>& callbacks = self->fThis->getCallbacks();
    PyObject* tup = PyTuple_New(callbacks.size());
    for (size_t i = 0; i < callbacks.size(); ++i)
        PyTuple_SET_ITEM(tup, i, ICreate(callbacks[i]));
    return tup;
}

PY_PROPERTY_SETTER_MSG(MessageWithCallbacks, callbacks, "To add callbacks, use addCallback")
PY_PROPERTY_GETSET_DECL(MessageWithCallbacks, callbacks)

static PyGetSetDef pyMessageWithCallbacks_GetSet[] = {
    pyMessageWithCallbacks_callbacks_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MessageWithCallbacks, plMessageWithCallbacks,
               "plMessageWithCallbacks wrapper")

PY_PLASMA_TYPE_INIT(MessageWithCallbacks)
{
    pyMessageWithCallbacks_Type.tp_new = pyMessageWithCallbacks_new;
    pyMessageWithCallbacks_Type.tp_methods = pyMessageWithCallbacks_Methods;
    pyMessageWithCallbacks_Type.tp_getset = pyMessageWithCallbacks_GetSet;
    pyMessageWithCallbacks_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyMessageWithCallbacks_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMessageWithCallbacks_Type);
    return (PyObject*)&pyMessageWithCallbacks_Type;
}

PY_PLASMA_IFC_METHODS(MessageWithCallbacks, plMessageWithCallbacks)
