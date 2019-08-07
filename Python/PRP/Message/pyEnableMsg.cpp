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

#include "pyEnableMsg.h"

#include <PRP/Message/plEnableMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(EnableMsg, plEnableMsg)

PY_METHOD_VA(EnableMsg, getCmd, "Params: cmd")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getCmd().get((size_t)idx));
}

PY_METHOD_VA(EnableMsg, getType, "Params: type")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getType expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getTypes().get((size_t)idx));
}

PY_METHOD_VA(EnableMsg, setCmd, "Params: cmd, value")
{
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return nullptr;
    }
    self->fThis->getCmd().set(idx, value != 0);
    Py_RETURN_NONE;
}

PY_METHOD_VA(EnableMsg, setType, "Params: type, value")
{
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setType expects int, bool");
        return nullptr;
    }
    self->fThis->getTypes().set(idx, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pyEnableMsg_Methods[] = {
    pyEnableMsg_getCmd_method,
    pyEnableMsg_getType_method,
    pyEnableMsg_setCmd_method,
    pyEnableMsg_setType_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(EnableMsg, plEnableMsg, "plEnableMsg wrapper")

PY_PLASMA_TYPE_INIT(EnableMsg)
{
    pyEnableMsg_Type.tp_new = pyEnableMsg_new;
    pyEnableMsg_Type.tp_methods = pyEnableMsg_Methods;
    pyEnableMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyEnableMsg_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(EnableMsg, "kDisable", plEnableMsg::kDisable);
    PY_TYPE_ADD_CONST(EnableMsg, "kEnable", plEnableMsg::kEnable);
    PY_TYPE_ADD_CONST(EnableMsg, "kDrawable", plEnableMsg::kDrawable);
    PY_TYPE_ADD_CONST(EnableMsg, "kPhysical", plEnableMsg::kPhysical);
    PY_TYPE_ADD_CONST(EnableMsg, "kAudible", plEnableMsg::kAudible);
    PY_TYPE_ADD_CONST(EnableMsg, "kAll", plEnableMsg::kAll);
    PY_TYPE_ADD_CONST(EnableMsg, "kByType", plEnableMsg::kByType);

    Py_INCREF(&pyEnableMsg_Type);
    return (PyObject*)&pyEnableMsg_Type;
}

PY_PLASMA_IFC_METHODS(EnableMsg, plEnableMsg)
