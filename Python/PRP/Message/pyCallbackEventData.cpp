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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>

PY_PLASMA_NEW(CallbackEventData, proCallbackEventData)

PY_PROPERTY(int, CallbackEventData, callbackEventType, getCallbackEventType,
            setCallbackEventType)

static PyGetSetDef pyCallbackEventData_GetSet[] = {
    pyCallbackEventData_callbackEventType_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CallbackEventData, proCallbackEventData, "proCallbackEventData wrapper")

PY_PLASMA_TYPE_INIT(CallbackEventData)
{
    pyCallbackEventData_Type.tp_new = pyCallbackEventData_new;
    pyCallbackEventData_Type.tp_getset = pyCallbackEventData_GetSet;
    pyCallbackEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyCallbackEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCallbackEventData_Type);
    return (PyObject*)&pyCallbackEventData_Type;
}

PY_PLASMA_IFC_METHODS(CallbackEventData, proCallbackEventData)
