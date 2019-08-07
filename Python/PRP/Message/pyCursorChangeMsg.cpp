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

#include "pyCursorChangeMsg.h"

#include <PRP/Message/plCursorChangeMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(CursorChangeMsg, plCursorChangeMsg)

PY_PROPERTY(int, CursorChangeMsg, type, getType, setType)
PY_PROPERTY(int, CursorChangeMsg, priority, getPriority, setPriority)

static PyGetSetDef pyCursorChangeMsg_GetSet[] = {
    pyCursorChangeMsg_type_getset,
    pyCursorChangeMsg_priority_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CursorChangeMsg, plCursorChangeMsg, "plCursorChangeMsg wrapper")

PY_PLASMA_TYPE_INIT(CursorChangeMsg)
{
    pyCursorChangeMsg_Type.tp_new = pyCursorChangeMsg_new;
    pyCursorChangeMsg_Type.tp_getset = pyCursorChangeMsg_GetSet;
    pyCursorChangeMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyCursorChangeMsg_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CursorChangeMsg, "kNoChange", plCursorChangeMsg::kNoChange);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorUp", plCursorChangeMsg::kCursorUp);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorLeft", plCursorChangeMsg::kCursorLeft);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorRight", plCursorChangeMsg::kCursorRight);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorDown", plCursorChangeMsg::kCursorDown);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorPoised", plCursorChangeMsg::kCursorPoised);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorClicked", plCursorChangeMsg::kCursorClicked);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorUnClicked", plCursorChangeMsg::kCursorUnClicked);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorHidden", plCursorChangeMsg::kCursorHidden);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorOpen", plCursorChangeMsg::kCursorOpen);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorGrab", plCursorChangeMsg::kCursorGrab);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kCursorArrow", plCursorChangeMsg::kCursorArrow);
    PY_TYPE_ADD_CONST(CursorChangeMsg, "kNullCursor", plCursorChangeMsg::kNullCursor);

    Py_INCREF(&pyCursorChangeMsg_Type);
    return (PyObject*)&pyCursorChangeMsg_Type;
}

PY_PLASMA_IFC_METHODS(CursorChangeMsg, plCursorChangeMsg)
