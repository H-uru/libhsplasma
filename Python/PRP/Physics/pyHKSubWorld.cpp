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

#include "pyHKSubWorld.h"

#include <PRP/Physics/plHKSubWorld.h>
#include "PRP/Object/pyObjInterface.h"
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(HKSubWorld, plHKSubWorld)

PY_PROPERTY(hsVector3, HKSubWorld, gravity, getGravity, setGravity)

static PyGetSetDef pyHKSubWorld_GetSet[] = {
    pyHKSubWorld_gravity_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(HKSubWorld, plHKSubWorld, "plHKSubWorld wrapper")

PY_PLASMA_TYPE_INIT(HKSubWorld)
{
    pyHKSubWorld_Type.tp_new = pyHKSubWorld_new;
    pyHKSubWorld_Type.tp_getset = pyHKSubWorld_GetSet;
    pyHKSubWorld_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyHKSubWorld_Type) < 0)
        return nullptr;

    Py_INCREF(&pyHKSubWorld_Type);
    return (PyObject*)&pyHKSubWorld_Type;
}

PY_PLASMA_IFC_METHODS(HKSubWorld, plHKSubWorld)
