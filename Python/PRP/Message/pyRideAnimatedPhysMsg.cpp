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

#include "pyRideAnimatedPhysMsg.h"

#include "pyMessage.h"
#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Message/plRideAnimatedPhysMsg.h>

PY_PLASMA_NEW(RideAnimatedPhysMsg, plRideAnimatedPhysMsg)

PY_PROPERTY(bool, RideAnimatedPhysMsg, entering, getEntering, setEntering)
PY_PROPERTY(plKey, RideAnimatedPhysMsg, region, getRegion, setRegion)

static PyGetSetDef pyRideAnimatedPhysMsg_GetSet[] = {
    pyRideAnimatedPhysMsg_entering_getset,
    pyRideAnimatedPhysMsg_region_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(RideAnimatedPhysMsg, plRideAnimatedPhysMsg,
               "plRideAnimatedPhysMsg wrapper")

PY_PLASMA_TYPE_INIT(RideAnimatedPhysMsg)
{
    pyRideAnimatedPhysMsg_Type.tp_new = pyRideAnimatedPhysMsg_new;
    pyRideAnimatedPhysMsg_Type.tp_getset = pyRideAnimatedPhysMsg_GetSet;
    pyRideAnimatedPhysMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyRideAnimatedPhysMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRideAnimatedPhysMsg_Type);
    return (PyObject*)&pyRideAnimatedPhysMsg_Type;
}

PY_PLASMA_IFC_METHODS(RideAnimatedPhysMsg, plRideAnimatedPhysMsg);
