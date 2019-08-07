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

PY_PLASMA_NEW(CoopEventData, proCoopEventData)

PY_PROPERTY(unsigned int, CoopEventData, id, getID, setID)
PY_PROPERTY(unsigned short, CoopEventData, serial, getSerial, setSerial)

static PyGetSetDef pyCoopEventData_GetSet[] = {
    pyCoopEventData_id_getset,
    pyCoopEventData_serial_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CoopEventData, proCoopEventData, "proCoopEventData wrapper")

PY_PLASMA_TYPE_INIT(CoopEventData)
{
    pyCoopEventData_Type.tp_new = pyCoopEventData_new;
    pyCoopEventData_Type.tp_getset = pyCoopEventData_GetSet;
    pyCoopEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyCoopEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCoopEventData_Type);
    return (PyObject*)&pyCoopEventData_Type;
}

PY_PLASMA_IFC_METHODS(CoopEventData, proCoopEventData)
