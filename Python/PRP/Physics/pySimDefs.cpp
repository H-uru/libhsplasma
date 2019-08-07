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

#include "pyPhysical.h"

#include <PRP/Physics/plPhysical.h>

PY_PLASMA_NEW_MSG(SimDefs, "Cannot construct plSimDefs objects")

typedef PyObject pySimDefs;
PY_PLASMA_TYPE(SimDefs, plSimDefs, "plSimDefs constants")

PY_PLASMA_TYPE_INIT(SimDefs)
{
    pySimDefs_Type.tp_new = pySimDefs_new;
    if (PyType_CheckAndReady(&pySimDefs_Type) < 0)
        return nullptr;

    /* Bounds */
    PY_TYPE_ADD_CONST(SimDefs, "kBoxBounds", plSimDefs::kBoxBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kSphereBounds", plSimDefs::kSphereBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kHullBounds", plSimDefs::kHullBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kProxyBounds", plSimDefs::kProxyBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kExplicitBounds", plSimDefs::kExplicitBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kCylinderBounds", plSimDefs::kCylinderBounds);

    /* Group */
    PY_TYPE_ADD_CONST(SimDefs, "kGroupStatic", plSimDefs::kGroupStatic);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupAvatar", plSimDefs::kGroupAvatar);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupDynamic", plSimDefs::kGroupDynamic);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupDetector", plSimDefs::kGroupDetector);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupLOSOnly", plSimDefs::kGroupLOSOnly);

    /* LOSDBs */
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBNone", plSimDefs::kLOSDBNone);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBUIBlockers", plSimDefs::kLOSDBUIBlockers);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBUIItems", plSimDefs::kLOSDBUIItems);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBCameraBlockers", plSimDefs::kLOSDBCameraBlockers);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBCustom", plSimDefs::kLOSDBCustom);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBLocalAvatar", plSimDefs::kLOSDBLocalAvatar);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBShootableItems", plSimDefs::kLOSDBShootableItems);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBAvatarWalkable", plSimDefs::kLOSDBAvatarWalkable);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBSwimRegion", plSimDefs::kLOSDBSwimRegion);

    Py_INCREF(&pySimDefs_Type);
    return (PyObject*)&pySimDefs_Type;
}
