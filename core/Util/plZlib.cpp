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

#include "plZlib.h"
#include <zlib.h>

bool plZlib::Uncompress(uint8_t* bufOut, size_t& bufLenOut, const uint8_t* bufIn, size_t bufLenIn)
{
    uLongf bufLenOut_zlib = (uLongf)bufLenOut;
    int result = ::uncompress(bufOut, &bufLenOut_zlib, bufIn, bufLenIn);
    bufLenOut = (size_t)bufLenOut_zlib;
    return result == Z_OK;
}

bool plZlib::Compress(uint8_t*& bufOut, size_t& bufLenOut, const uint8_t* bufIn, size_t bufLenIn)
{
    uLongf bufLenOut_zlib = ::compressBound(bufLenIn);
    bufOut = new uint8_t[bufLenOut_zlib];
    int result = ::compress(bufOut, &bufLenOut_zlib, bufIn, bufLenIn);
    bufLenOut = (size_t)bufLenOut_zlib;
    return result == Z_OK;
}
