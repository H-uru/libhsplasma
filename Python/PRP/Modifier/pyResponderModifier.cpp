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
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ResponderModifier, plResponderModifier)

PY_METHOD_VA(ResponderModifier, addState,
    "Params: state\n"
    "Add a responder state to the Responder")
{
    pyResponderModifier_State* state;
    if (!PyArg_ParseTuple(args, "O", &state)) {
        PyErr_SetString(PyExc_TypeError, "addState expects a plResponderModifier_State");
        return nullptr;
    }
    if (!pyResponderModifier_State_Check((PyObject*)state)) {
        PyErr_SetString(PyExc_TypeError, "addState expects a plResponderModifier_State");
        return nullptr;
    }
    self->fThis->addState(state->fThis);
    state->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResponderModifier, delState,
    "Params: idx\n"
    "Delete a state from the Responder")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delState expects an int");
        return nullptr;
    }
    self->fThis->delState(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ResponderModifier, clearStates, "Delete all states from the Responder")
{
    self->fThis->clearStates();
    Py_RETURN_NONE;
}

static PyMethodDef pyResponderModifier_Methods[] = {
    pyResponderModifier_addState_method,
    pyResponderModifier_delState_method,
    pyResponderModifier_clearStates_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ResponderModifier, states)
{
    PyObject* list = PyTuple_New(self->fThis->getStates().size());
    for (size_t i=0; i<self->fThis->getStates().size(); i++)
        PyTuple_SET_ITEM(list, i, pyResponderModifier_State_FromResponderModifier_State(self->fThis->getStates()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ResponderModifier, states, "To add states, use addState")
PY_PROPERTY_GETSET_DECL(ResponderModifier, states)

PY_PROPERTY(signed char, ResponderModifier, curState, getCurState, setCurState)
PY_PROPERTY(bool, ResponderModifier, enabled, isEnabled, setEnabled)
PY_PROPERTY(unsigned char, ResponderModifier, flags, getFlags, setFlags)

static PyGetSetDef pyResponderModifier_GetSet[] = {
    pyResponderModifier_states_getset,
    pyResponderModifier_curState_getset,
    pyResponderModifier_enabled_getset,
    pyResponderModifier_flags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ResponderModifier, plResponderModifier, "plResponderModifier wrapper")

PY_PLASMA_TYPE_INIT(ResponderModifier)
{
    pyResponderModifier_Type.tp_new = pyResponderModifier_new;
    pyResponderModifier_Type.tp_methods = pyResponderModifier_Methods;
    pyResponderModifier_Type.tp_getset = pyResponderModifier_GetSet;
    pyResponderModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyResponderModifier_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ResponderModifier, "kDetectTrigger",
                      plResponderModifier::kDetectTrigger);
    PY_TYPE_ADD_CONST(ResponderModifier, "kDetectUnTrigger",
                      plResponderModifier::kDetectUnTrigger);
    PY_TYPE_ADD_CONST(ResponderModifier, "kSkipFFSound",
                      plResponderModifier::kSkipFFSound);

    Py_INCREF(&pyResponderModifier_Type);
    return (PyObject*)&pyResponderModifier_Type;
}

PY_PLASMA_IFC_METHODS(ResponderModifier, plResponderModifier)
