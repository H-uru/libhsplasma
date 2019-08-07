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

#include "pyTimerCallbackMsg.h"

#include <PRP/Message/plTimerCallbackMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(TimerCallbackMsg, plTimerCallbackMsg)

PY_PROPERTY(unsigned int, TimerCallbackMsg, ID, getID, setID)
PY_PROPERTY(float, TimerCallbackMsg, time, getTime, setTime)

static PyGetSetDef pyTimerCallbackMsg_GetSet[] = {
    pyTimerCallbackMsg_ID_getset,
    pyTimerCallbackMsg_time_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(TimerCallbackMsg, plTimerCallbackMsg, "plTimerCallbackMsg wrapper")

PY_PLASMA_TYPE_INIT(TimerCallbackMsg)
{
    pyTimerCallbackMsg_Type.tp_new = pyTimerCallbackMsg_new;
    pyTimerCallbackMsg_Type.tp_getset = pyTimerCallbackMsg_GetSet;
    pyTimerCallbackMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyTimerCallbackMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyTimerCallbackMsg_Type);
    return (PyObject*)&pyTimerCallbackMsg_Type;
}

PY_PLASMA_IFC_METHODS(TimerCallbackMsg, plTimerCallbackMsg)
