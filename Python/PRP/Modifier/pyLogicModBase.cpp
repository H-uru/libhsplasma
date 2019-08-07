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

#include "pyLogicModifier.h"

#include <PRP/Modifier/plLogicModBase.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Message/pyNotifyMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/pyCreatable.h"
#include "Util/pyBitVector.h"

PY_PLASMA_NEW_MSG(LogicModBase, "plLogicModBase is abstract")

PY_METHOD_NOARGS(LogicModBase, clearCommands, "Remove all commands")
{
    self->fThis->clearCommands();
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModBase, addCommand,
    "Params: key\n"
    "Add a command")
{
    pyMessage* msg;
    if (!PyArg_ParseTuple(args, "O", &msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects a plMessage");
        return nullptr;
    }
    if (!pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects a plMessage");
        return nullptr;
    }
    self->fThis->addCommand(msg->fThis);
    msg->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModBase, delCommand,
    "Params: idx\n"
    "Remove a command")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCommand expects an int");
        return nullptr;
    }
    self->fThis->delCommand(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModBase, getLogicFlag,
    "Params: flag\n"
    "Returns True if the LogicMod flag is set")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getLogicFlag expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getLogicFlag(idx));
}

PY_METHOD_VA(LogicModBase, setLogicFlag,
    "Params: flag, value\n"
    "Sets the specified LogicMod flag")
{
    int idx, value;
    if (!PyArg_ParseTuple(args, "ii", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setLogicFlag expects int, bool");
        return nullptr;
    }
    self->fThis->setLogicFlag(idx, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pyLogicModBase_Methods[] = {
    pyLogicModBase_clearCommands_method,
    pyLogicModBase_addCommand_method,
    pyLogicModBase_delCommand_method,
    pyLogicModBase_getLogicFlag_method,
    pyLogicModBase_setLogicFlag_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(LogicModBase, commands)
{
    PyObject* list = PyTuple_New(self->fThis->getCommands().size());
    for (size_t i=0; i<self->fThis->getCommands().size(); i++)
        PyTuple_SET_ITEM(list, i, ICreate(self->fThis->getCommands()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(LogicModBase, commands, "To add commands, use addCommand")
PY_PROPERTY_GETSET_DECL(LogicModBase, commands)

PY_PROPERTY_CREATABLE(plNotifyMsg, NotifyMsg, LogicModBase, notify,
                      getNotify, setNotify)
PY_PROPERTY(bool, LogicModBase, disabled, isDisabled, setDisabled)

static PyGetSetDef pyLogicModBase_GetSet[] = {
    pyLogicModBase_commands_getset,
    pyLogicModBase_notify_getset,
    pyLogicModBase_disabled_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LogicModBase, plLogicModBase, "plLogicModBase wrapper")

PY_PLASMA_TYPE_INIT(LogicModBase)
{
    pyLogicModBase_Type.tp_new = pyLogicModBase_new;
    pyLogicModBase_Type.tp_methods = pyLogicModBase_Methods;
    pyLogicModBase_Type.tp_getset = pyLogicModBase_GetSet;
    pyLogicModBase_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyLogicModBase_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(LogicModBase, "kLocalElement", plLogicModBase::kLocalElement);
    PY_TYPE_ADD_CONST(LogicModBase, "kReset", plLogicModBase::kReset);
    PY_TYPE_ADD_CONST(LogicModBase, "kTriggered", plLogicModBase::kTriggered);
    PY_TYPE_ADD_CONST(LogicModBase, "kOneShot", plLogicModBase::kOneShot);
    PY_TYPE_ADD_CONST(LogicModBase, "kRequestingTrigger", plLogicModBase::kRequestingTrigger);
    PY_TYPE_ADD_CONST(LogicModBase, "kTypeActivator", plLogicModBase::kTypeActivator);
    PY_TYPE_ADD_CONST(LogicModBase, "kMultiTrigger", plLogicModBase::kMultiTrigger);

    Py_INCREF(&pyLogicModBase_Type);
    return (PyObject*)&pyLogicModBase_Type;
}

PY_PLASMA_IFC_METHODS(LogicModBase, plLogicModBase)
