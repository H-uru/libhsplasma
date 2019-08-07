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

#include "pyVolumeSensorConditionalObject.h"

#include <PRP/ConditionalObject/plVolumeSensorConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(VolumeSensorConditionalObject, plVolumeSensorConditionalObject)

PY_PROPERTY(int, VolumeSensorConditionalObject, trigNum, getTrigNum, setTrigNum)
PY_PROPERTY(int, VolumeSensorConditionalObject, type, getType, setType)
PY_PROPERTY(bool, VolumeSensorConditionalObject, first, getFirst, setFirst)

static PyGetSetDef pyVolumeSensorConditionalObject_GetSet[] = {
    pyVolumeSensorConditionalObject_trigNum_getset,
    pyVolumeSensorConditionalObject_type_getset,
    pyVolumeSensorConditionalObject_first_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VolumeSensorConditionalObject, plVolumeSensorConditionalObject,
               "plVolumeSensorConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(VolumeSensorConditionalObject)
{
    pyVolumeSensorConditionalObject_Type.tp_new = pyVolumeSensorConditionalObject_new;
    pyVolumeSensorConditionalObject_Type.tp_getset = pyVolumeSensorConditionalObject_GetSet;
    pyVolumeSensorConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyVolumeSensorConditionalObject_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(VolumeSensorConditionalObject, "kTypeEnter",
                      plVolumeSensorConditionalObject::kTypeEnter);
    PY_TYPE_ADD_CONST(VolumeSensorConditionalObject, "kTypeExit",
                      plVolumeSensorConditionalObject::kTypeExit);

    Py_INCREF(&pyVolumeSensorConditionalObject_Type);
    return (PyObject*)&pyVolumeSensorConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(VolumeSensorConditionalObject, plVolumeSensorConditionalObject)
