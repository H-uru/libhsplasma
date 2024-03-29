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

#ifndef _PLZLIB_H
#define _PLZLIB_H

#include "PlasmaDefs.h"

#include <cstddef> // for size_t

class HSPLASMA_EXPORT plZlib
{
public:
    static bool Uncompress(uint8_t* bufOut, size_t& bufLenOut, const uint8_t* bufIn, size_t bufLenIn);
    static bool Compress(uint8_t*& bufOut, size_t& bufLenOut, const uint8_t* bufIn, size_t bufLenIn);
};

#endif
