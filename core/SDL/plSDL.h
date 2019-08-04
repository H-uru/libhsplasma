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

#ifndef _PLSDL_H
#define _PLSDL_H

#include "PRP/plCreatable.h"

namespace plSDL
{
    enum ContentsFlags
    {
        kHasUoid = 0x1,
        kHasNotificationInfo = 0x2,
        kHasTimeStamp = 0x4,
        kSameAsDefault = 0x8,
        kHasDirtyFlag = 0x10,
        kWantTimeStamp = 0x20
    };

    unsigned int VariableLengthRead(hsStream* S, size_t size);
    void VariableLengthWrite(hsStream* S, size_t size, unsigned int value);
};

#endif
