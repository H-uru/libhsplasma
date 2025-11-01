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

#include <catch2/catch.hpp>

#include "PRP/KeyedObject/plLocation.h"

#define CHECK_LOCATION(version, seqNum, valid, virt, seqPrefix, pageNum)    \
    do {                                                                    \
        plLocation loc(version);                                            \
        loc.parse(seqNum);                                                  \
        CHECK(loc.isValid() == valid);                                      \
        CHECK(loc.isVirtual() == virt);                                     \
        CHECK(loc.getSeqPrefix() == seqPrefix);                             \
        CHECK(loc.getPageNum() == pageNum);                                 \
        CHECK(loc.unparse() == seqNum);                                     \
    } while (false)

#define CHECK_LOCATION_MOUL(seqNum, seqPrefix, pageNum)                     \
    CHECK_LOCATION(PlasmaVer::pvMoul, seqNum, true, false, seqPrefix, pageNum)

#define CHECK_LOCATION_CLASSIC(seqNum, seqPrefix, pageNum)                  \
    CHECK_LOCATION(PlasmaVer::pvPrime, seqNum, true, false, seqPrefix, pageNum)

TEST_CASE("plLocation packing and unpacking", "[location]")
{
    SECTION("Uru Live format plLocations") {
        CHECK_LOCATION(PlasmaVer::pvMoul, 0, true, true, 0, 0);
        CHECK_LOCATION(PlasmaVer::pvMoul, 0xFFFF'FFFF, false, false, 0, 0);

        CHECK_LOCATION_MOUL(0x0000'0021, 0, 0);
        CHECK_LOCATION_MOUL(0x0000'0022, 0, 1);
        CHECK_LOCATION_MOUL(0x0000'7FFF, 0, 0x7FDE);
        CHECK_LOCATION_MOUL(0x0000'8020, 0, 0x7FFF);
        CHECK_LOCATION_MOUL(0x0001'0000, 0, 0xFFDF);
        CHECK_LOCATION_MOUL(0x0001'0001, 0, -32);   // 0, 0xFFE0
        CHECK_LOCATION_MOUL(0x0001'0020, 0, -1);    // 0, 0xFFFF

        CHECK_LOCATION_MOUL(0x0001'0021, 1, 0);
        CHECK_LOCATION_MOUL(0x00FF'0021, 255, 0);
        CHECK_LOCATION_MOUL(0x0100'0020, 255, -1);
        CHECK_LOCATION_MOUL(0x7FFF'0021, 0x7FFF, 0);
        CHECK_LOCATION_MOUL(0xFEFF'0021, 0xFEFF, 0);
        CHECK_LOCATION_MOUL(0xFF00'0020, 0xFEFF, -1);

        CHECK_LOCATION_MOUL(0xFF01'0001, -1, 0);
        CHECK_LOCATION_MOUL(0xFF01'0002, -1, 1);
        CHECK_LOCATION_MOUL(0xFF01'8000, -1, 0x7FFF);
        CHECK_LOCATION_MOUL(0xFF02'0000, -1, -1);
        CHECK_LOCATION_MOUL(0xFFFE'0001, -254, 0);
        CHECK_LOCATION_MOUL(0xFFFF'0000, -254, -1);

        // Examples from real PRPs
        CHECK_LOCATION_MOUL(0x0006'0022, 6, 1);         // city:canyon
        CHECK_LOCATION_MOUL(0x0006'0086, 6, 101);       // city:museumDoor
        CHECK_LOCATION_MOUL(0x0007'001F, 6, -2);        // city:BuiltIn
        CHECK_LOCATION_MOUL(0x0007'0020, 6, -1);        // city:Textures
        CHECK_LOCATION_MOUL(0x04D2'0026, 1234, 5);      // GoMePubNew:Entry
        CHECK_LOCATION_MOUL(0x9C44'0022, 40004, 1);     // VeeTsah:Temple
        CHECK_LOCATION_MOUL(0x9C45'0020, 40004, -1);    // VeeTsah:Textures
        CHECK_LOCATION_MOUL(0xFF01'0009, -1, 8);        // GlobalAnimations:MaleIdle
        CHECK_LOCATION_MOUL(0xFF01'01B4, -1, 435);      // GlobalAnimations:FemaleSwimDockExit
        CHECK_LOCATION_MOUL(0xFF06'0004, -6, 3);        // GlobalAvatars:Audio
    }

    SECTION("Classic format plLocations") {
        CHECK_LOCATION(PlasmaVer::pvPrime, 0, true, true, 0, 0);
        CHECK_LOCATION(PlasmaVer::pvPrime, 0xFFFF'FFFF, false, false, 0, 0);

        CHECK_LOCATION_CLASSIC(0x0000'0021, 0, 0);
        CHECK_LOCATION_CLASSIC(0x0000'0022, 0, 1);
        CHECK_LOCATION_CLASSIC(0x0000'007F, 0, 0x5E);
        CHECK_LOCATION_CLASSIC(0x0000'00A0, 0, 0x7F);
        CHECK_LOCATION_CLASSIC(0x0000'0100, 0, 0xDF);
        CHECK_LOCATION_CLASSIC(0x0000'0101, 0, -32);   // 0, 0xE0
        CHECK_LOCATION_CLASSIC(0x0000'0120, 0, -1);    // 0, 0xFF

        CHECK_LOCATION_CLASSIC(0x0000'0121, 1, 0);
        CHECK_LOCATION_CLASSIC(0x0000'FF21, 255, 0);
        CHECK_LOCATION_CLASSIC(0x0001'0020, 255, -1);
        CHECK_LOCATION_CLASSIC(0x007F'FF21, 0x7FFF, 0);
        CHECK_LOCATION_CLASSIC(0x00FE'FF21, 0xFEFF, 0);
        CHECK_LOCATION_CLASSIC(0x00FF'0020, 0xFEFF, -1);
        CHECK_LOCATION_CLASSIC(0xFFFE'FF21, 0xFF'FEFF, 0);
        CHECK_LOCATION_CLASSIC(0xFFFF'0020, 0xFF'FEFF, -1);

        CHECK_LOCATION_CLASSIC(0xFFFF'0101, -1, 0);
        CHECK_LOCATION_CLASSIC(0xFFFF'0102, -1, 1);
        CHECK_LOCATION_CLASSIC(0xFFFF'0180, -1, 0x7F);
        CHECK_LOCATION_CLASSIC(0xFFFF'0200, -1, -1);
        CHECK_LOCATION_CLASSIC(0xFFFF'FE01, -254, 0);
        CHECK_LOCATION_CLASSIC(0xFFFF'FF00, -254, -1);

        // Examples from real PRPs
        CHECK_LOCATION_CLASSIC(0x0000'0622, 6, 1);      // city:canyon
        CHECK_LOCATION_CLASSIC(0x0000'065E, 6, 61);     // city:islmLibBanners03Vis
        CHECK_LOCATION_CLASSIC(0x0000'071F, 6, -2);     // city:BuiltIn
        CHECK_LOCATION_CLASSIC(0x0000'0720, 6, -1);     // city:Textures
        CHECK_LOCATION_CLASSIC(0x0000'2727, 39, 6);     // GreatZero:CalibrationMarkerGameGUI
        CHECK_LOCATION_CLASSIC(0x0000'2820, 39, -1);    // GreatZero:Textures
        CHECK_LOCATION_CLASSIC(0xFFFF'0109, -1, 8);     // GlobalAnimations:MaleIdle
        CHECK_LOCATION_CLASSIC(0xFFFF'0604, -6, 3);     // GlobalAvatars:Audio

        // The below test case reveals a fault in the Plasma data files -- the
        // suffix (page) number overflows the maximum range of the encoding
        // and ends up overlapping with <-2|11>, and therefore can't actually
        // be decoded correctly.
        //CHECK_LOCATION_CLASSIC(0xFFFF'020C, -1, 267);   // GlobalAnimations:FemaleBallPushWalk
        CHECK_LOCATION_CLASSIC(0xFFFF'020C, -2, 11);   // GlobalAnimations:FemaleBallPushWalk
    }
}
