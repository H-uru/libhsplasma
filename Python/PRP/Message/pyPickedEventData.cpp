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
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(PickedEventData, proPickedEventData)

PY_PROPERTY(plKey, PickedEventData, picker, getPicker, setPicker)
PY_PROPERTY(plKey, PickedEventData, picked, getPicked, setPicked)
PY_PROPERTY(bool, PickedEventData, enabled, isEnabled, setEnabled)
PY_PROPERTY(hsVector3, PickedEventData, hitPoint, getHitPoint, setHitPoint)

static PyGetSetDef pyPickedEventData_GetSet[] = {
    pyPickedEventData_picker_getset,
    pyPickedEventData_picked_getset,
    pyPickedEventData_enabled_getset,
    pyPickedEventData_hitPoint_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PickedEventData, proPickedEventData, "proPickedEventData wrapper")

PY_PLASMA_TYPE_INIT(PickedEventData)
{
    pyPickedEventData_Type.tp_new = pyPickedEventData_new;
    pyPickedEventData_Type.tp_getset = pyPickedEventData_GetSet;
    pyPickedEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyPickedEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPickedEventData_Type);
    return (PyObject*)&pyPickedEventData_Type;
}

PY_PLASMA_IFC_METHODS(PickedEventData, proPickedEventData)
