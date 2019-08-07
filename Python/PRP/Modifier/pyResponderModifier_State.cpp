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

#include "pyResponderModifier.h"

#include <PRP/Modifier/plResponderModifier.h>
#include "PRP/Message/pyMessage.h"

PY_PLASMA_DEALLOC(ResponderModifier_State)
PY_PLASMA_EMPTY_INIT(ResponderModifier_State)
PY_PLASMA_NEW(ResponderModifier_State, plResponderModifier::plResponderState)

PY_METHOD_VA(ResponderModifier_State, addCommand,
    "Params: msg, waitOn\n"
    "Add a command to the Responder state")
{
    pyMessage* msg;
    int waitOn;
    if (!PyArg_ParseTuple(args, "Oi", &msg, &waitOn)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects plMessage, int");
        return nullptr;
    }
    if (!pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCommand expects plMessage, int");
        return nullptr;
    }
    self->fThis->addCommand(msg->fThis, waitOn);
    msg->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResponderModifier_State, delCommand,
    "Params: idx\n"
    "Delete a command from the Responder state")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCommand expects an int");
        return nullptr;
    }
    self->fThis->delCommand(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ResponderModifier_State, clearCommands,
    "Delete all commands from the Responder state")
{
    self->fThis->clearCommands();
    Py_RETURN_NONE;
}

static PyMethodDef pyResponderModifier_State_Methods[] = {
    pyResponderModifier_State_addCommand_method,
    pyResponderModifier_State_delCommand_method,
    pyResponderModifier_State_clearCommands_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ResponderModifier_State, commands)
{
    PyObject* list = PyTuple_New(self->fThis->fCmds.size());
    for (size_t i=0; i<self->fThis->fCmds.size(); i++)
        PyTuple_SET_ITEM(list, i, pyResponderModifier_Cmd_FromResponderModifier_Cmd(self->fThis->fCmds[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ResponderModifier_State, commands, "To add commands, use addCommand")
PY_PROPERTY_GETSET_DECL(ResponderModifier_State, commands)

PY_GETSET_GETTER_DECL(ResponderModifier_State, waitToCmd)
{
    PyObject* dict = PyDict_New();
    for (const auto& wp : self->fThis->fWaitToCmd)
        PyDict_SetItem(dict, pyPlasma_convert(wp.first), pyPlasma_convert(wp.second));
    return dict;
}

PY_GETSET_SETTER_DECL(ResponderModifier_State, waitToCmd)
{
    PY_PROPERTY_CHECK_NULL(waitToCmd)
    if (!PyDict_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waitToCmd should be a dict { int => int }");
        return -1;
    }

    PyObject *dkey, *dvalue;
    Py_ssize_t pos = 0;
    self->fThis->fWaitToCmd.clear();

    while (PyDict_Next(value, &pos, &dkey, &dvalue)) {
        if (!pyPlasma_check<int8_t>(dkey) || !pyPlasma_check<int8_t>(dvalue)) {
            PyErr_SetString(PyExc_TypeError, "waitToCmd should be a dict { int => int }");
            return -1;
        }
        self->fThis->fWaitToCmd[pyPlasma_get<int8_t>(dkey)] = pyPlasma_get<int8_t>(dvalue);
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(ResponderModifier_State, waitToCmd)

PY_PROPERTY_MEMBER(int8_t, ResponderModifier_State, numCallbacks, fNumCallbacks)
PY_PROPERTY_MEMBER(int8_t, ResponderModifier_State, switchToState, fSwitchToState)

static PyGetSetDef pyResponderModifier_State_GetSet[] = {
    pyResponderModifier_State_commands_getset,
    pyResponderModifier_State_numCallbacks_getset,
    pyResponderModifier_State_switchToState_getset,
    pyResponderModifier_State_waitToCmd_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ResponderModifier_State, plResponderModifier_State,
               "plResponderModifier::plResponderState wrapper")

PY_PLASMA_TYPE_INIT(ResponderModifier_State)
{
    pyResponderModifier_State_Type.tp_dealloc = pyResponderModifier_State_dealloc;
    pyResponderModifier_State_Type.tp_init = pyResponderModifier_State___init__;
    pyResponderModifier_State_Type.tp_new = pyResponderModifier_State_new;
    pyResponderModifier_State_Type.tp_methods = pyResponderModifier_State_Methods;
    pyResponderModifier_State_Type.tp_getset = pyResponderModifier_State_GetSet;
    if (PyType_CheckAndReady(&pyResponderModifier_State_Type) < 0)
        return nullptr;

    Py_INCREF(&pyResponderModifier_State_Type);
    return (PyObject*)&pyResponderModifier_State_Type;
}

PY_PLASMA_IFC_METHODS(ResponderModifier_State, plResponderModifier::plResponderState)
