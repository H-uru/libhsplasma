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

#ifndef _HSRAMSTREAM_H
#define _HSRAMSTREAM_H

#include "hsStream.h"

#define BLOCKSIZE 4096  // Common block size on x86 machines

DllClass hsRAMStream : public hsStream {
protected:
    hsUbyte* fData;
    hsUint32 fSize, fMax, fPos;

public:
    hsRAMStream(int pv = PlasmaVer::pvUnknown);
    virtual ~hsRAMStream();

    void copyFrom(const void* data, size_t size);
    void copyTo(void* data, size_t size);

    virtual hsUint32 size() const { return fSize; }
    virtual hsUint32 pos() const { return fPos; }
    virtual bool eof() const { return (fPos >= fSize); }

    virtual void seek(hsUint32 pos) { fPos = pos; }
    virtual void skip(hsInt32 count) { fPos += count; }
    virtual void fastForward() { fPos = fSize; }
    virtual void rewind() { fPos = 0; }

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    virtual void resize(hsUint32 newsize);
};

#endif
