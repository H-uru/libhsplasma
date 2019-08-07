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
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(VariableEventData, proVariableEventData)

PY_PROPERTY(ST::string, VariableEventData, name, getName, setName)
PY_PROPERTY(int, VariableEventData, dataType, getDataType, setDataType)
PY_PROPERTY(float, VariableEventData, number, getNumber, setNumber)
PY_PROPERTY(plKey, VariableEventData, key, getKey, setKey)

static PyGetSetDef pyVariableEventData_GetSet[] = {
    pyVariableEventData_name_getset,
    pyVariableEventData_dataType_getset,
    pyVariableEventData_number_getset,
    pyVariableEventData_key_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VariableEventData, proVariableEventData,
               "proVariableEventData wrapper")

PY_PLASMA_TYPE_INIT(VariableEventData)
{
    pyVariableEventData_Type.tp_new = pyVariableEventData_new;
    pyVariableEventData_Type.tp_getset = pyVariableEventData_GetSet;
    pyVariableEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyVariableEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVariableEventData_Type);
    return (PyObject*)&pyVariableEventData_Type;
}

PY_PLASMA_IFC_METHODS(VariableEventData, proVariableEventData)
