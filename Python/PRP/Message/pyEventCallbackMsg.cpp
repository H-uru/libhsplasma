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

#include "pyEventCallbackMsg.h"

#include <PRP/Message/plEventCallbackMsg.h>
#include "pyMessage.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(EventCallbackMsg, plEventCallbackMsg)

PY_PROPERTY(float, EventCallbackMsg, eventTime, getEventTime, setEventTime)
PY_PROPERTY(CallbackEvent, EventCallbackMsg, event, getEvent, setEvent)
PY_PROPERTY(short, EventCallbackMsg, index, getIndex, setIndex)
PY_PROPERTY(short, EventCallbackMsg, repeats, getRepeats, setRepeats)
PY_PROPERTY(short, EventCallbackMsg, user, getUser, setUser)

static PyGetSetDef pyEventCallbackMsg_GetSet[] = {
    pyEventCallbackMsg_eventTime_getset,
    pyEventCallbackMsg_event_getset,
    pyEventCallbackMsg_index_getset,
    pyEventCallbackMsg_repeats_getset,
    pyEventCallbackMsg_user_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EventCallbackMsg, plEventCallbackMsg, "plEventCallbackMsg wrapper")

PY_PLASMA_TYPE_INIT(EventCallbackMsg)
{
    pyEventCallbackMsg_Type.tp_new = pyEventCallbackMsg_new;
    pyEventCallbackMsg_Type.tp_getset = pyEventCallbackMsg_GetSet;
    pyEventCallbackMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyEventCallbackMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEventCallbackMsg_Type);
    return (PyObject*)&pyEventCallbackMsg_Type;
}

PY_PLASMA_IFC_METHODS(EventCallbackMsg, plEventCallbackMsg)
