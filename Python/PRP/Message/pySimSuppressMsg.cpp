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

#include "pySimulationMsg.h"

#include <PRP/Message/plSimulationMsg.h>

PY_PLASMA_NEW(SimSuppressMsg, plSimSuppressMsg)

PY_PROPERTY(bool, SimSuppressMsg, suppress, getSuppress, setSuppress)

static PyGetSetDef pySimSuppressMsg_GetSet[] = {
    pySimSuppressMsg_suppress_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimSuppressMsg, plSimSuppressMsg, "plSimSuppressMsg wrapper")

PY_PLASMA_TYPE_INIT(SimSuppressMsg)
{
    pySimSuppressMsg_Type.tp_new = pySimSuppressMsg_new;
    pySimSuppressMsg_Type.tp_getset = pySimSuppressMsg_GetSet;
    pySimSuppressMsg_Type.tp_base = &pySimulationMsg_Type;
    if (PyType_CheckAndReady(&pySimSuppressMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pySimSuppressMsg_Type);
    return (PyObject*)&pySimSuppressMsg_Type;
}

PY_PLASMA_IFC_METHODS(SimSuppressMsg, plSimSuppressMsg)
