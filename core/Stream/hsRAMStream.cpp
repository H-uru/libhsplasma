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

#include "hsRAMStream.h"
#include <cstring>

#define BLOCKSIZE 4096  // Common block size on x86 machines

hsRAMStream::~hsRAMStream()
{
    delete[] fData;
}

void hsRAMStream::stealFrom(void* data, size_t size)
{
    fSize = size;
    fMax = size;
    fPos = 0;
    delete[] fData;
    fData = (uint8_t*)data;
}

void hsRAMStream::copyFrom(const void* data, size_t size)
{
    if (size == 0) {
        stealFrom(nullptr, 0);
    } else {
        uint8_t* buffer = new uint8_t[size];
        memcpy(buffer, data, size);
        stealFrom(buffer, size);
    }
}

void hsRAMStream::copyTo(void* data, size_t size)
{
    size_t cpysize = (size < fSize) ? size : fSize;
    memcpy(data, fData, cpysize);
}

size_t hsRAMStream::read(size_t size, void* buf)
{
    if (size + fPos > fSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of buffer");
    memcpy(buf, fData + fPos, size);
    fPos += size;
    return size;
}

static size_t _blockalign(size_t size)
{
    return ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
}

size_t hsRAMStream::write(size_t size, const void* buf)
{
    if (size + fPos > fMax) {
        size_t newSize = (fMax == 0) ? BLOCKSIZE : _blockalign(fMax * 2);
        while (newSize < (size + fPos))
            newSize *= 2;
        resize(newSize);
    }
    memcpy(fData + fPos, buf, size);
    fPos += size;
    if (fPos > fSize)
        fSize = fPos;
    return size;
}

void hsRAMStream::resize(uint32_t newsize)
{
    uint8_t* newData = nullptr;

    if (newsize != 0) {
        newData = new uint8_t[newsize];
        uint32_t cpysize = 0;
        if (fData) {
            cpysize = (newsize < fSize) ? newsize : fSize;
            memcpy(newData, fData, cpysize);
        }
        if (newsize > cpysize)
            memset(newData + cpysize, 0, (newsize - cpysize));
    }
    delete[] fData;

    fMax = newsize;
    fData = newData;
    if (fSize > fMax)
        fSize = fMax;
}
