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

#include "pyResponderMsg.h"

#include <PRP/Message/plResponderMsg.h>
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(OneShotMsg, plOneShotMsg)

PY_METHOD_NOARGS(OneShotMsg, clearCallbacks, "Remove all callbacks")
{
    self->fThis->getCallbacks().clearCallbacks();
    Py_RETURN_NONE;
}

PY_METHOD_VA(OneShotMsg, addCallback,
    "Params: marker, receiver, user\n"
    "Add a callback")
{
    char* marker;
    PyObject* key;
    short user;
    if (!PyArg_ParseTuple(args, "esOh", "utf8", &marker, &key, &user) || !pyKey_Check(key)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects string, plKey, int");
        return nullptr;
    }
    self->fThis->getCallbacks().addCallback(marker, pyPlasma_get<plKey>(key), user);
    Py_RETURN_NONE;
}

PY_METHOD_VA(OneShotMsg, delCallback,
    "Params: idx\n"
    "Remove a callback")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return nullptr;
    }
    plOneShotCallbacks& cbs = self->fThis->getCallbacks();
    if (size_t(idx) >= cbs.getNumCallbacks()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    cbs.delCallback(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyOneShotMsg_Methods[] = {
    pyOneShotMsg_clearCallbacks_method,
    pyOneShotMsg_addCallback_method,
    pyOneShotMsg_delCallback_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(OneShotMsg, callbacks)
{
    const plOneShotCallbacks& cbs = self->fThis->getCallbacks();
    PyObject* tup = PyTuple_New(cbs.getNumCallbacks());
    for (size_t i = 0; i < cbs.getNumCallbacks(); ++i) {
        const auto& cb = cbs.getCallbacks()[i];
        PyObject* value = Py_BuildValue("OOh", pyPlasma_convert(cb.fMarker),
                                        pyPlasma_convert(cb.fReceiver), cb.fUser);
        PyTuple_SET_ITEM(tup, i, value);
    }
    return tup;
}

PY_PROPERTY_GETSET_RO_DECL(OneShotMsg, callbacks)

static PyGetSetDef pyOneShotMsg_GetSet[] = {
    pyOneShotMsg_callbacks_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(OneShotMsg, plOneShotMsg, "plOneShotMsg wrapper")

PY_PLASMA_TYPE_INIT(OneShotMsg)
{
    pyOneShotMsg_Type.tp_new = pyOneShotMsg_new;
    pyOneShotMsg_Type.tp_methods = pyOneShotMsg_Methods;
    pyOneShotMsg_Type.tp_getset = pyOneShotMsg_GetSet;
    pyOneShotMsg_Type.tp_base = &pyResponderMsg_Type;
    if (PyType_CheckAndReady(&pyOneShotMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOneShotMsg_Type);
    return (PyObject*)&pyOneShotMsg_Type;
}

PY_PLASMA_IFC_METHODS(OneShotMsg, plOneShotMsg)
