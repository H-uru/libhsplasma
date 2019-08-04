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

class PLASMA_DLL plHKSimDefs
{
public:
    enum Bounds
    {
        kBoxBounds = 1, kSphereBounds, kHullBounds, kProxyBounds,
        kExplicitBounds, kNumBounds, kBoundsMax = 0xFF
    };

    enum Group
    {
        kGroupWTFAhnonay = 1, // 0x2, seen on TreePlane in Sphere02 and on OfficeDoorBoardBlocker, PhysBoard02 in Cleft
        kGroupWTFTeledahn = 2, // 0x4, CollideGroup Slave Cave kickables
        kGroupClickable = 17, // 0x20000 Av, I doubt this is really about clickables... it is also set on "OuterSphere" and cones in the city, regions (like the weight detector plate) in Garrison, member group for the avatar physicals, ...
        kGroupCreatures = 18, // 0x40000 Cr (seen for avatars)
        kGroupAnimated = 23, // 0x800000 Ani
        kGroupFirstProper = 24, // only the groups below are really treated like groups, i.e. mapped to a generic group
        kGroupDynamic = 24, // 0x1000000 DS
        kGroupStatic = 25, // 0x2000000 SS
        kGroupDetector = 26, // 0x4000000 Det
        kGroupAvatar = 27, // 0x8000000
        kGroupMax
    };

private:
    static unsigned int fromGroup(unsigned int group)
    {
        if (group == kGroupDynamic)
            return plSimDefs::kGroupDynamic;
        else if (group == kGroupStatic)
            return plSimDefs::kGroupStatic;
        else if (group == kGroupDetector)
            return plSimDefs::kGroupDetector;
        else if (group == kGroupAvatar)
            return plSimDefs::kGroupAvatar;

        throw hsNotImplementedException(__FILE__, __LINE__, ST::format("plHKSimDefs::fromGroup: Havok group {}", group));
    }

    static unsigned int toGroup(unsigned int group)
    {
        if (group == plSimDefs::kGroupStatic)
            return kGroupStatic;
        else if (group == plSimDefs::kGroupAvatar)
            return kGroupAvatar;
        else if (group == plSimDefs::kGroupDynamic)
            return kGroupDynamic;
        else if (group == plSimDefs::kGroupDetector)
            return kGroupDetector;  

        throw hsNotImplementedException(__FILE__, __LINE__, ST::format("plHKSimDefs::fromGroup: Generic group {}", group));
    }

    static unsigned int getBitshiftGroup(unsigned int group)
    {
        unsigned int retGroup = 0;

        for (size_t i=kGroupFirstProper; i<kGroupMax; i++) {
            if ((group & (1u << i)) != 0) {
                retGroup |= (1u << fromGroup(i));
            }
        }

        return retGroup;
    }

    static unsigned int setBitshiftGroup(unsigned int group)
    {
        unsigned int retGroup = 0;

        for (size_t i=0; i<plSimDefs::kGroupMax; i++) {
            if ((group & (1u << i)) != 0) {
                retGroup |= (1u << toGroup(i));
            }
        }

        return retGroup;
    }

public:
    static unsigned int getMemGroup(unsigned int group)
    {
        // Havok stores the member group as bitflag... with only one bit set though. Find out which one.
        unsigned int maskedGroup = group & ~((1u << kGroupWTFAhnonay) | (1u << kGroupWTFTeledahn)); // ignore these weird bits
        if (maskedGroup == 0) // not a member of anything
            return plSimDefs::kGroupLOSOnly;
        else if (group == 1u << kGroupClickable) // kind of pointless, but the avatars do have this as their memGroup, and we have to map it somewhere...
            return plSimDefs::kGroupDynamic;
        for (size_t i=kGroupFirstProper; i<kGroupMax; i++) {
            if (maskedGroup == 1u << i)
                return fromGroup(i);
        }
        throw hsNotImplementedException(__FILE__, __LINE__, ST::format("plHKSimDefs::fromGroup: Havok member group 0x{_08X}", group));
    }

    static unsigned int setMemGroup(plGenericPhysical* physical)
    {
        const unsigned int group = physical->getMemberGroup();
        if (group == plSimDefs::kGroupLOSOnly)
            return 0; // not a member of anything
        return 1 << toGroup(group); // Havor stores the member group as bitflag, so convert it to one
    }

    static unsigned int getRepGroup(unsigned int group, unsigned int member)
    {
        unsigned int retGroup = getBitshiftGroup(group);
        return retGroup;
    }

    static unsigned int setRepGroup(plGenericPhysical* physical)
    {
        unsigned int retGroup = setBitshiftGroup(physical->getReportGroup());
        /* Problem with the animated flag:
         * city harbor: rgnShell_BeamDetector01 and Garrison grsnExterior: RgnJCCaveUnoccupied are identical in everything that matters, but the former has the animated flag, the latter does not. */
        /* Try to get the clickable flag back */
        if (physical->getMemberGroup() == plSimDefs::kGroupDetector && physical->getLOSDBs() == plSimDefs::kLOSDBNone && !(physical->getReportGroup() & (1u << plSimDefs::kGroupAvatar))) { // one could add:  && physical->getProperty(plSimulationInterface::kPinned) && physical->getCollideGroup() == 0
            // Examples: Garrison grsnElevator: DnElevEntryExclude (repGroup = 0), AhnySphere02 Sphere02: PressueRegion01 (repGroup contains dynamic)
            retGroup |= (1u << kGroupClickable);
        }

        return retGroup;
    }

    static unsigned int getColGroup(unsigned int group, unsigned int member)
    {
        unsigned int retGroup = getBitshiftGroup(group);
        return retGroup;
    }

    static unsigned int setColGroup(plGenericPhysical* physical)
    {
        unsigned int retGroup = setBitshiftGroup(physical->getCollideGroup());

        /* Try to get the animated flag back. This is correct for all Cyan ages, but not for some fan ages. */
        if (physical->getMemberGroup() == plSimDefs::kGroupDynamic && (physical->getCollideGroup() & (1u << plSimDefs::kGroupDynamic))) {
            // examples: Personal psnlMystII: KickBoulder, city harbor: BeamCollidingWithShell
            retGroup |= 1u << kGroupAnimated;
        }
        /* Try to get the clickabke back. However:
         * city courtyard: ALYOrangeCone09 and Garrison grsnPrison: Bone-C-17 are identical for everything preserved, but the former has the clickable flag, the latter (and many similar ones) not.
         * city ferry: OuterSphere09 and spyroom spyroom: TelescopeNew01 are identical, but the latter (and many more) have the clickable flag, the former does not.
         * Kadish kdshPillars: pillarRoomCameraCollider and Personal psnlMYSTII: Dock are identical, but the former has the clickable flag, the latter any many more do not.
         * BahroCave YeeshaCave: Wedge-TeledahnExclude and Personal psnlMYSTII: ClosetCollider are identical, but the former has the clickable flag, the latter any many more do not.
         * Checking the modifiers does not help.
         */
        if (physical->getProperty(plSimulationInterface::kPinned)) { // one could add: && physical->getReportGroup() == 0
            if ((physical->getMemberGroup() == plSimDefs::kGroupDetector && (physical->getCollideGroup() & (1u << plSimDefs::kGroupDynamic)) && (physical->getLOSDBs() & plSimDefs::kLOSDBUIBlockers)) || // Personal psnlMYSTII: xRgnLibraryDoor
                    (physical->getMemberGroup() == plSimDefs::kGroupDetector && physical->getCollideGroup() == 0 && (physical->getLOSDBs() & plSimDefs::kLOSDBUIItems)) || // spyroom spyroom: TelescopeNew01
                    (physical->getMemberGroup() == plSimDefs::kGroupStatic && physical->getCollideGroup() == 0 && physical->getLOSDBs() == plSimDefs::kLOSDBNone)) // Garrison WallRoom: LadderBounds01
                retGroup |= 1u << kGroupClickable;
        }

        return retGroup;
    }
};
