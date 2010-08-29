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

hsRAMStream::hsRAMStream(int pv)
           : hsStream(pv), fData(NULL), fSize(0), fMax(0), fPos(0) { }

hsRAMStream::~hsRAMStream() {
    delete[] fData;
}

void hsRAMStream::copyFrom(const void* data, size_t size) {
    fSize = size;
    fMax = ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
    fPos = 0;
    delete[] fData;
    if (size == 0) {
        fData = NULL;
    } else {
        fData = new hsUbyte[size];
        memcpy(fData, data, size);
    }
}

void hsRAMStream::copyTo(void* data, size_t size) {
    size_t cpysize = (size < fSize) ? size : fSize;
    memcpy(data, fData, cpysize);
}

size_t hsRAMStream::read(size_t size, void* buf) {
    if (size + fPos > fSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of buffer");
    memcpy(buf, fData + fPos, size);
    fPos += size;
    return size;
}

size_t hsRAMStream::write(size_t size, const void* buf) {
    if (size + fPos > fMax) {
        size_t newSize = (fMax == 0) ? BLOCKSIZE : fMax * 2;
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

void hsRAMStream::resize(hsUint32 newsize) {
    hsUbyte* newData = NULL;

    if (newsize != 0) {
        newData = new hsUbyte[newsize];
        hsUint32 cpysize = 0;
        if (fData != NULL) {
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
