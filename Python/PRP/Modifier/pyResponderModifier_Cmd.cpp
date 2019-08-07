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
#include "PRP/pyCreatable.h"
#include "PRP/Message/pyMessage.h"

PY_PLASMA_DEALLOC(ResponderModifier_Cmd)

PY_PLASMA_INIT_DECL(ResponderModifier_Cmd)
{
    pyMessage* msg = nullptr;
    int waitOn = -1;
    if (!PyArg_ParseTuple(args, "|Oi", &msg, &waitOn)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a message and an int");
        return -1;
    }
    if (msg && !pyMessage_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a message and an int");
        return -1;
    }
    if (msg) {
        self->fThis->fMsg = msg->fThis;
        msg->fPyOwned = false;
    } else {
        self->fThis->fMsg = nullptr;
    }
    self->fThis->fWaitOn = waitOn;
    return 0;
}

PY_PLASMA_NEW(ResponderModifier_Cmd, plResponderModifier::plResponderCmd)

PY_PROPERTY_CREATABLE_MEMBER(plMessage, Message, ResponderModifier_Cmd, msg, fMsg)
PY_PROPERTY_MEMBER(int8_t, ResponderModifier_Cmd, waitOn, fWaitOn)

static PyGetSetDef pyResponderModifier_Cmd_GetSet[] = {
    pyResponderModifier_Cmd_msg_getset,
    pyResponderModifier_Cmd_waitOn_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ResponderModifier_Cmd, plResponderModifier_Cmd,
               "plResponderModifier::plResponderCmd wrapper")

PY_PLASMA_TYPE_INIT(ResponderModifier_Cmd)
{
    pyResponderModifier_Cmd_Type.tp_dealloc = pyResponderModifier_Cmd_dealloc;
    pyResponderModifier_Cmd_Type.tp_init = pyResponderModifier_Cmd___init__;
    pyResponderModifier_Cmd_Type.tp_new = pyResponderModifier_Cmd_new;
    pyResponderModifier_Cmd_Type.tp_getset = pyResponderModifier_Cmd_GetSet;
    if (PyType_CheckAndReady(&pyResponderModifier_Cmd_Type) < 0)
        return nullptr;

    Py_INCREF(&pyResponderModifier_Cmd_Type);
    return (PyObject*)&pyResponderModifier_Cmd_Type;
}

PY_PLASMA_IFC_METHODS(ResponderModifier_Cmd, plResponderModifier::plResponderCmd)
