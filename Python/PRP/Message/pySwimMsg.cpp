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

#include "pySwimMsg.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Message/plSwimMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(SwimMsg, plSwimMsg)

PY_PROPERTY(bool, SwimMsg, isEntering, getIsEntering, setIsEntering)
PY_PROPERTY(plKey, SwimMsg, swimRegion, getSwimRegion, setSwimRegion)

static PyGetSetDef pySwimMsg_GetSet[] = {
    pySwimMsg_isEntering_getset,
    pySwimMsg_swimRegion_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SwimMsg, plSwimMsg, "plSwimMsg wrapper")

PY_PLASMA_TYPE_INIT(SwimMsg)
{
    pySwimMsg_Type.tp_new = pySwimMsg_new;
    pySwimMsg_Type.tp_getset = pySwimMsg_GetSet;
    pySwimMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pySwimMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pySwimMsg_Type);
    return (PyObject*)&pySwimMsg_Type;
}

PY_PLASMA_IFC_METHODS(SwimMsg, plSwimMsg)
