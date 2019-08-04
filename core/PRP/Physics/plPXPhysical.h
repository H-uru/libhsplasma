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

class PLASMA_DLL plPXSimDefs
{
public:
    enum Bounds
    {
        kBoxBounds = 1, kSphereBounds, kHullBounds, kProxyBounds,
        kExplicitBounds, kCylinderBounds, kNumBounds, kBoundsMax = 0xFF
    };

    enum Group
    {
        kGroupStatic,
        kGroupAvatarBlocker,
        kGroupDynamicBlocker,
        kGroupAvatar,
        kGroupDynamic,
        kGroupDetector,
        kGroupLOSOnly,
        kGroupExcludeRegion,
        kGroupMax
    };

    static unsigned int fromGroup(uint8_t group)
    {
        if (group == kGroupStatic) {
            return plSimDefs::kGroupStatic;
        } else if (group == kGroupAvatarBlocker) {
            return plSimDefs::kGroupStatic;
        } else if (group == kGroupDynamicBlocker) {
            return plSimDefs::kGroupStatic;
        } else if (group == kGroupAvatar) {
            return plSimDefs::kGroupAvatar;
        } else if (group == kGroupDynamic) {
            return plSimDefs::kGroupDynamic;
        } else if (group == kGroupDetector) {
            return plSimDefs::kGroupDetector;
        } else if (group == kGroupLOSOnly) {
            return plSimDefs::kGroupLOSOnly;
        }

        throw hsNotImplementedException(__FILE__, __LINE__, ST::format("plPXSimDefs::fromGroup: PhysX group {}", group));
    }

    static uint8_t toGroup(unsigned int group, unsigned int collide)
    {
        if (collide == (1 << plSimDefs::kGroupAvatar)) {
            return kGroupAvatarBlocker;
        } else if (collide == (1 << plSimDefs::kGroupDynamic)) {
            return kGroupDynamicBlocker;
        } else if (group == plSimDefs::kGroupStatic) {
            return kGroupStatic;
        } else if (group == plSimDefs::kGroupAvatar) {
            return kGroupAvatar;
        } else if (group == plSimDefs::kGroupDynamic) {
            return kGroupDynamic;
        } else if (group == plSimDefs::kGroupDetector) {
            return kGroupDetector;
        } else if (group == plSimDefs::kGroupLOSOnly) {
            return kGroupLOSOnly;
        }

        throw hsNotImplementedException(__FILE__, __LINE__, ST::format("plPXSimDefs::toGroup: Generic group {}", group));
    }

    static unsigned int getCollideGroup(uint8_t group)
    {
        if (group == kGroupAvatarBlocker) {
            return (1 << plSimDefs::kGroupAvatar);
        } else if (group == kGroupDynamicBlocker) {
            return (1 << plSimDefs::kGroupDynamic);
        } else {
            return 0;
        }
    }

    static unsigned int getReportsOn(unsigned int group)
    {
        unsigned int retGroup = 0;

        for (size_t i=0; i<kGroupMax; i++) {
            if ((group & (1u << i)) != 0) {
                retGroup |= (1 << fromGroup(i));
            }
        }

        return retGroup;
    }

    static unsigned int setReportsOn(unsigned int group)
    {
        unsigned int retGroup = 0;

        for (size_t i=0; i<plSimDefs::kGroupMax; i++) {
            if ((group & (1u << i)) != 0) {
                retGroup |= (1 << toGroup(i,0));
            }
        }

        return retGroup;
    }
};

class plGenericPhysical;

class PLASMA_DLL PXCookedData
{
public:
    static void readTriangleMesh(hsStream* S, plGenericPhysical* physical);
    static void readConvexMesh(hsStream* S, plGenericPhysical* physical);

private:
    static unsigned int readOPC(hsStream* S);
    static void readHBM(hsStream* S);
    static void readSuffix(hsStream* S);
    static void skipMaxDependantList(hsStream*S, unsigned int size);
};
