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

PY_PLASMA_NEW(ContainedEventData, proContainedEventData)

PY_PROPERTY(plKey, ContainedEventData, contained, getContained, setContained)
PY_PROPERTY(plKey, ContainedEventData, container, getContainer, setContainer)
PY_PROPERTY(bool, ContainedEventData, entering, isEntering, setEntering)

static PyGetSetDef pyContainedEventData_GetSet[] = {
    pyContainedEventData_contained_getset,
    pyContainedEventData_container_getset,
    pyContainedEventData_entering_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ContainedEventData, proContainedEventData,
               "proContainedEventData wrapper")

PY_PLASMA_TYPE_INIT(ContainedEventData)
{
    pyContainedEventData_Type.tp_new = pyContainedEventData_new;
    pyContainedEventData_Type.tp_getset = pyContainedEventData_GetSet;
    pyContainedEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyContainedEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyContainedEventData_Type);
    return (PyObject*)&pyContainedEventData_Type;
}

PY_PLASMA_IFC_METHODS(ContainedEventData, proContainedEventData)
