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

PY_PLASMA_NEW(ResponderStateEventData, proResponderStateEventData)

PY_PROPERTY(int, ResponderStateEventData, state, getState, setState)

static PyGetSetDef pyResponderStateEventData_GetSet[] = {
    pyResponderStateEventData_state_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ResponderStateEventData, proResponderStateEventData,
               "proResponderStateEventData wrapper")

PY_PLASMA_TYPE_INIT(ResponderStateEventData)
{
    pyResponderStateEventData_Type.tp_new = pyResponderStateEventData_new;
    pyResponderStateEventData_Type.tp_getset = pyResponderStateEventData_GetSet;
    pyResponderStateEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyResponderStateEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyResponderStateEventData_Type);
    return (PyObject*)&pyResponderStateEventData_Type;
}

PY_PLASMA_IFC_METHODS(ResponderStateEventData, proResponderStateEventData)
