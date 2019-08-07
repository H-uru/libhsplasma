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

#include "pySwimRegion.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Region/plSwimRegion.h>

PY_PLASMA_NEW(SwimCircularCurrentRegion, plSwimCircularCurrentRegion)

PY_PROPERTY(float, SwimCircularCurrentRegion, rotation, getRotation, setRotation)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullNearDistSq, getPullNearDistSq, setPullNearDistSq)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullFarDistSq, getPullFarDistSq, setPullFarDistSq)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullNearVel, getPullNearVel, setPullNearVel)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullFarVel, getPullFarVel, setPullFarVel)
PY_PROPERTY(plKey, SwimCircularCurrentRegion, currentObj, getCurrentObj, setCurrentObj)

PyGetSetDef pySwimCircularCurrentRegion_GetSet[] = {
    pySwimCircularCurrentRegion_rotation_getset,
    pySwimCircularCurrentRegion_pullNearDistSq_getset,
    pySwimCircularCurrentRegion_pullFarDistSq_getset,
    pySwimCircularCurrentRegion_pullNearVel_getset,
    pySwimCircularCurrentRegion_pullFarVel_getset,
    pySwimCircularCurrentRegion_currentObj_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SwimCircularCurrentRegion, plSwimCircularCurrentRegion,
               "plSwimCircularCurrentRegion wrapper")

PY_PLASMA_TYPE_INIT(SwimCircularCurrentRegion)
{
    pySwimCircularCurrentRegion_Type.tp_new = pySwimCircularCurrentRegion_new;
    pySwimCircularCurrentRegion_Type.tp_getset = pySwimCircularCurrentRegion_GetSet;
    pySwimCircularCurrentRegion_Type.tp_base = &pySwimRegionInterface_Type;
    if (PyType_CheckAndReady(&pySwimCircularCurrentRegion_Type) < 0)
        return nullptr;

    Py_INCREF(&pySwimCircularCurrentRegion_Type);
    return (PyObject*)&pySwimCircularCurrentRegion_Type;
}

PY_PLASMA_IFC_METHODS(SwimCircularCurrentRegion, plSwimCircularCurrentRegion);
