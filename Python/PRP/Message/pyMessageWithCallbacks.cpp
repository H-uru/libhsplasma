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

extern "C" {

PY_PLASMA_NEW(MessageWithCallbacks, plMessageWithCallbacks)

PY_METHOD_VA(MessageWithCallbacks, addCallback,
    "Params: key\n"
    "Adds a callback message")
{
    PyObject* msg;
    if (!(PyArg_ParseTuple(args, "O", &msg) && pyMessage_Check(msg))) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plMessage");
        return NULL;
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
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getCallbacks().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
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

static PyObject* pyMessageWithCallbacks_getCallbacks(pyMessageWithCallbacks* self, void*) {
    const std::vector<plMessage*>& callbacks = self->fThis->getCallbacks();
    PyObject* tup = PyTuple_New(callbacks.size());
    for (size_t i = 0; i < callbacks.size(); ++i)
        PyTuple_SET_ITEM(tup, i, ICreate(callbacks[i]));
    return tup;
}

static int pyMessageWithCallbacks_setCallbacks(pyMessageWithCallbacks* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add callbacks, use addCallback");
    return -1;
}

static PyGetSetDef pyMessageWithCallbacks_GetSet[] = {
    { _pycs("callbacks"), (getter)pyMessageWithCallbacks_getCallbacks,
       (setter)pyMessageWithCallbacks_setCallbacks, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MessageWithCallbacks, plMessageWithCallbacks,
               "plMessageWithCallbacks wrapper")

PY_PLASMA_TYPE_INIT(MessageWithCallbacks) {
    pyMessageWithCallbacks_Type.tp_new = pyMessageWithCallbacks_new;
    pyMessageWithCallbacks_Type.tp_methods = pyMessageWithCallbacks_Methods;
    pyMessageWithCallbacks_Type.tp_getset = pyMessageWithCallbacks_GetSet;
    pyMessageWithCallbacks_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyMessageWithCallbacks_Type) < 0)
        return NULL;

    Py_INCREF(&pyMessageWithCallbacks_Type);
    return (PyObject*)&pyMessageWithCallbacks_Type;
}

PY_PLASMA_IFC_METHODS(MessageWithCallbacks, plMessageWithCallbacks)

};
