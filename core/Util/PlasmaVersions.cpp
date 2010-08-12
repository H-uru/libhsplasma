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

#include "PlasmaVersions.h"

const char* GetVersionName(PlasmaVer ver) {
    switch (ver) {
        case pvPrime:
            return "Prime/UU";
        case pvPots:
            return "PotS/CC";
        case pvLive:
            return "MOUL";
        case pvEoa:
            return "Myst V/Crowthistle";
        case pvHex:
            return "Hex Isle";
        case pvUniversal:
            return "Universal";
        default:
            if (ver < pvPrime)
                return "Choru";
            if (ver > pvPots && ver < pvLive)
                return "MOUL Beta";
            else
                return "Unknown";
    }
}

PlasmaVer GetSafestVersion(PlasmaVer ver) {
    if (ver <= pvPrime)
        return pvPrime;
    else if (ver == pvPots)
        return pvPots;
    else if (ver <= pvLive)
        return pvLive;
    else if (ver == pvEoa)
        return pvEoa;
    else if (ver == pvHex)
        return pvHex;
    else
        return pvUniversal;
}
