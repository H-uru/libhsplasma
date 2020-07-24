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

#include "pyWarpMsg.h"

#include <PRP/Message/plWarpMsg.h>
#include "Math/pyMatrix.h"
#include "pyMessage.h"

PY_PLASMA_NEW(WarpMsg, plWarpMsg)

PY_PROPERTY(uint32_t, WarpMsg, warpFlags, getWarpFlags, setWarpFlags)
PY_PROPERTY(hsMatrix44, WarpMsg, transform, getTransform, setTransform)

static PyGetSetDef pyWarpMsg_GetSet[] = {
    pyWarpMsg_warpFlags_getset,
    pyWarpMsg_transform_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(WarpMsg, plWarpMsg, "plWarpMsg wrapper")

PY_PLASMA_TYPE_INIT(WarpMsg)
{
    pyWarpMsg_Type.tp_new = pyWarpMsg_new;
    pyWarpMsg_Type.tp_getset = pyWarpMsg_GetSet;
    pyWarpMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyWarpMsg_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(WarpMsg, "kFlushTransform", plWarpMsg::kFlushTransform);
    PY_TYPE_ADD_CONST(WarpMsg, "kZeroVelocity", plWarpMsg::kZeroVelocity);

    Py_INCREF(&pyWarpMsg_Type);
    return (PyObject*)&pyWarpMsg_Type;
}

PY_PLASMA_IFC_METHODS(WarpMsg, plWarpMsg)
