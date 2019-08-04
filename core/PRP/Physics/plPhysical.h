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

#ifndef _PLPHYSICAL_H
#define _PLPHYSICAL_H

#include "PRP/Object/plSynchedObject.h"

class PLASMA_DLL plSimDefs
{
public:
    enum Bounds
    {
        kBoxBounds = 1, kSphereBounds, kHullBounds, kProxyBounds,
        kExplicitBounds, kCylinderBounds, kNumBounds, kBoundsMax = 0xFF
    };

    /* NOTE - This enum does not match Plasma!
     * It has been created to hold all possible values across versions.
     */
    enum Group
    {
        kGroupStatic,
        kGroupAvatar,
        kGroupDynamic,
        kGroupDetector,
        kGroupLOSOnly,
        kGroupMax
    };

    enum LOSDB
    {
        kLOSDBNone = 0,
        kLOSDBUIBlockers = 0x1,
        kLOSDBUIItems = 0x2,
        kLOSDBCameraBlockers = 0x4,
        kLOSDBCustom = 0x8,
        kLOSDBLocalAvatar = 0x10,
        kLOSDBShootableItems = 0x20,
        kLOSDBAvatarWalkable = 0x40,
        kLOSDBSwimRegion = 0x80,
        kLOSDBMax = 0x100,
        kLOSDBForce16 = 0xFFFF
    };

    static const char* BoundsNames[];
    static const char* GroupNames[];
};

class PLASMA_DLL plPhysical : public plSynchedObject
{
    CREATABLE(plPhysical, kPhysical, plSynchedObject)
};

#endif
