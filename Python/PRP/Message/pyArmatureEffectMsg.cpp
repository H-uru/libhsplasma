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

#include "pyArmatureEffectMsg.h"

#include <PRP/Message/plArmatureEffectMsg.h>
#include "pyMessage.h"

PY_PLASMA_NEW(ArmatureEffectStateMsg, plArmatureEffectStateMsg)

PY_PROPERTY(int8_t, ArmatureEffectStateMsg, surface, getSurface, setSurface)
PY_PROPERTY(bool, ArmatureEffectStateMsg, addSurface, getAddSurface, setAddSurface)

static PyGetSetDef pyArmatureEffectStateMsg_GetSet[] = {
    pyArmatureEffectStateMsg_surface_getset,
    pyArmatureEffectStateMsg_addSurface_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ArmatureEffectStateMsg, plArmatureEffectStateMsg,
               "plArmatureEffectStateMsg wrapper")

PY_PLASMA_TYPE_INIT(ArmatureEffectStateMsg)
{
    pyArmatureEffectStateMsg_Type.tp_new = pyArmatureEffectStateMsg_new;
    pyArmatureEffectStateMsg_Type.tp_getset = pyArmatureEffectStateMsg_GetSet;
    pyArmatureEffectStateMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyArmatureEffectStateMsg_Type) < 0)
        return nullptr;

    Py_INCREF(&pyArmatureEffectStateMsg_Type);
    return (PyObject*)&pyArmatureEffectStateMsg_Type;
}

PY_PLASMA_IFC_METHODS(ArmatureEffectStateMsg, plArmatureEffectStateMsg)
