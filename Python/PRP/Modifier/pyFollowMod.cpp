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

#include "pyFollowMod.h"

#include <PRP/Modifier/plFollowMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(FollowMod, plFollowMod)

PY_PROPERTY(plFollowMod::FollowLeaderType, FollowMod, leaderType, getLeaderType,
            setLeaderType)
PY_PROPERTY(uint8_t, FollowMod, mode, getMode, setMode)
PY_PROPERTY(plKey, FollowMod, leader, getLeader, setLeader)

static PyGetSetDef pyFollowMod_GetSet [] = {
    pyFollowMod_leaderType_getset,
    pyFollowMod_mode_getset,
    pyFollowMod_leader_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FollowMod, plFollowMod, "plFollowMod wrapper")

PY_PLASMA_TYPE_INIT(FollowMod)
{
    pyFollowMod_Type.tp_new = pyFollowMod_new;
    pyFollowMod_Type.tp_getset = pyFollowMod_GetSet;
    pyFollowMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyFollowMod_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(FollowMod, "kFollowPlayer", plFollowMod::kFollowPlayer);
    PY_TYPE_ADD_CONST(FollowMod, "kFollowObject", plFollowMod::kFollowObject);
    PY_TYPE_ADD_CONST(FollowMod, "kFollowCamera", plFollowMod::kFollowCamera);
    PY_TYPE_ADD_CONST(FollowMod, "kFollowListener", plFollowMod::kFollowListener);

    PY_TYPE_ADD_CONST(FollowMod, "kPositionX", plFollowMod::kPositionX);
    PY_TYPE_ADD_CONST(FollowMod, "kPositionY", plFollowMod::kPositionY);
    PY_TYPE_ADD_CONST(FollowMod, "kPositionZ", plFollowMod::kPositionZ);
    PY_TYPE_ADD_CONST(FollowMod, "kPosition", plFollowMod::kPosition);
    PY_TYPE_ADD_CONST(FollowMod, "kRotate", plFollowMod::kRotate);
    PY_TYPE_ADD_CONST(FollowMod, "kFullTransform", plFollowMod::kFullTransform);

    Py_INCREF(&pyFollowMod_Type);
    return (PyObject*) &pyFollowMod_Type;
}

PY_PLASMA_IFC_METHODS(FollowMod, plFollowMod)
