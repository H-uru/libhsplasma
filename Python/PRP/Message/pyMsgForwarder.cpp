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

#include "pyMsgForwarder.h"

#include <PRP/Message/plMsgForwarder.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(MsgForwarder, plMsgForwarder)

PY_METHOD_NOARGS(MsgForwarder, clearForwardKeys,
    "Remove all forward keys from the forwarder")
{
    self->fThis->clearForwardKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(MsgForwarder, addForwardKey,
    "Params: key\n"
    "Add a forward key to the forwarder")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addForwardKey expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addForwardKey expects a plKey");
        return nullptr;
    }
    self->fThis->addForwardKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(MsgForwarder, delForwardKey,
    "Params: idx\n"
    "Remove a forward key from the forwarder")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delForwardKey expects an int");
        return nullptr;
    }
    self->fThis->delForwardKey(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyMsgForwarder_Methods[] = {
    pyMsgForwarder_clearForwardKeys_method,
    pyMsgForwarder_addForwardKey_method,
    pyMsgForwarder_delForwardKey_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(MsgForwarder, forwardKeys)
{
    PyObject* list = PyTuple_New(self->fThis->getForwardKeys().size());
    for (size_t i=0; i<self->fThis->getForwardKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getForwardKeys()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(MsgForwarder, forwardKeys, "To add forward keys, use addForwardKey")
PY_PROPERTY_GETSET_DECL(MsgForwarder, forwardKeys)

static PyGetSetDef pyMsgForwarder_GetSet[] = {
    pyMsgForwarder_forwardKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MsgForwarder, plMsgForwarder, "plMsgForwarder wrapper")

PY_PLASMA_TYPE_INIT(MsgForwarder)
{
    pyMsgForwarder_Type.tp_new = pyMsgForwarder_new;
    pyMsgForwarder_Type.tp_methods = pyMsgForwarder_Methods;
    pyMsgForwarder_Type.tp_getset = pyMsgForwarder_GetSet;
    pyMsgForwarder_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyMsgForwarder_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMsgForwarder_Type);
    return (PyObject*)&pyMsgForwarder_Type;
}

PY_PLASMA_IFC_METHODS(MsgForwarder, plMsgForwarder)
