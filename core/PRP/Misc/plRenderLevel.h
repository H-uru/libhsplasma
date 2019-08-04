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

#ifndef _PLRENDERLEVEL_H
#define _PLRENDERLEVEL_H

#include "PlasmaDefs.h"

namespace plRenderLevel
{
    enum
    {
        kOpaqueMajorLevel = 0x0,
        kFBMajorLevel = 0x1,
        kDefRendMajorLevel = 0x2,
        kBlendRendMajorLevel = 0x4,
        kLateRendMajorLevel = 0x8
    };

    enum { kMajorShift = 0x1C };

    enum
    {
        kDefRendMinorLevel = 0x0,
        kOpaqueMinorLevel = 0x0,
        kMinorLevelMask = 0x0FFFFFFF,
        kAvatarRendMinorLevel = 0x0FFFFFFE
    };
};

#endif
