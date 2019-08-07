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

PY_PLASMA_NEW(CollisionEventData, proCollisionEventData)

PY_PROPERTY(bool, CollisionEventData, enter, isEnter, setEnter)
PY_PROPERTY(plKey, CollisionEventData, hitter, getHitter, setHitter)
PY_PROPERTY(plKey, CollisionEventData, hittee, getHittee, setHittee)

static PyGetSetDef pyCollisionEventData_GetSet[] = {
    pyCollisionEventData_enter_getset,
    pyCollisionEventData_hitter_getset,
    pyCollisionEventData_hittee_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CollisionEventData, proCollisionEventData,
               "proCollisionEventData wrapper")

PY_PLASMA_TYPE_INIT(CollisionEventData)
{
    pyCollisionEventData_Type.tp_new = pyCollisionEventData_new;
    pyCollisionEventData_Type.tp_getset = pyCollisionEventData_GetSet;
    pyCollisionEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyCollisionEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCollisionEventData_Type);
    return (PyObject*)&pyCollisionEventData_Type;
}

PY_PLASMA_IFC_METHODS(CollisionEventData, proCollisionEventData)
