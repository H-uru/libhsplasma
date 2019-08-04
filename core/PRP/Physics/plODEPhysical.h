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

/* The enumerations in this file are internal use ONLY.
 * Do NOT include this file in your own code!
 */
#include "plPhysical.h"

class PLASMA_DLL plODESimDefs
{
public:
    enum Bounds
    {
        kBoxBounds = 1, kSphereBounds, kHullBounds, kProxyBounds,
        kExplicitBounds, kCylinderBounds, kNumBounds, kBoundsMax = 0xFF
    };

    /* TODO! */
    enum Group
    {
        kGroupStatic,
        kGroupAvatarBlocker,
        kGroupDynamicBlocker,
        kGroupAvatar,
        kGroupDynamic,
        kGroupDetector,
        kGroupLOSOnly,
        kGroupMax
    };
};
