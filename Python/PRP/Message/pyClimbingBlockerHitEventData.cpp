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

PY_PLASMA_NEW(ClimbingBlockerHitEventData, proClimbingBlockerHitEventData)

PY_PROPERTY(plKey, ClimbingBlockerHitEventData, blocker, getBlocker, setBlocker)

static PyGetSetDef pyClimbingBlockerHitEventData_GetSet[] = {
    pyClimbingBlockerHitEventData_blocker_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ClimbingBlockerHitEventData, proClimbingBlockerHitEventData,
               "proClimbingBlockerHitEventData wrapper")

PY_PLASMA_TYPE_INIT(ClimbingBlockerHitEventData)
{
    pyClimbingBlockerHitEventData_Type.tp_new = pyClimbingBlockerHitEventData_new;
    pyClimbingBlockerHitEventData_Type.tp_getset = pyClimbingBlockerHitEventData_GetSet;
    pyClimbingBlockerHitEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyClimbingBlockerHitEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyClimbingBlockerHitEventData_Type);
    return (PyObject*)&pyClimbingBlockerHitEventData_Type;
}

PY_PLASMA_IFC_METHODS(ClimbingBlockerHitEventData, proClimbingBlockerHitEventData)
