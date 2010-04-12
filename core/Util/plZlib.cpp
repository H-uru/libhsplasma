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
#include "Stream/hsRAMStream.h"
#include <zlib.h>

bool plZlib::Uncompress(unsigned char* bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn) {
    return (::uncompress(bufOut, (uLongf*)&bufLenOut, bufIn, bufLenIn) == Z_OK);
}

bool plZlib::Compress(unsigned char*& bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn) {
    bufLenOut = ::compressBound(bufLenIn);
    bufOut = new unsigned char[bufLenOut];
    return (::compress(bufOut, (uLongf*)&bufLenOut, bufIn, bufLenIn) == Z_OK);
}
