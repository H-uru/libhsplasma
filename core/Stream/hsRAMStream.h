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

class PLASMA_DLL hsRAMStream : public hsStream {
protected:
    uint8_t* fData;
    uint32_t fSize, fMax, fPos;

public:
    explicit hsRAMStream(int pv = PlasmaVer::pvUnknown)
        : hsStream(pv), fData(), fSize(), fMax(), fPos() { }
    ~hsRAMStream() HS_OVERRIDE;

    void stealFrom(void* data, size_t size);
    void copyFrom(const void* data, size_t size);
    void copyTo(void* data, size_t size);

    uint32_t size() const HS_OVERRIDE { return fSize; }
    uint32_t pos() const HS_OVERRIDE { return fPos; }
    bool eof() const HS_OVERRIDE { return (fPos >= fSize); }

    void seek(uint32_t pos) HS_OVERRIDE { fPos = pos; }
    void skip(int32_t count) HS_OVERRIDE { fPos += count; }
    void fastForward() HS_OVERRIDE { fPos = fSize; }
    void rewind() HS_OVERRIDE { fPos = 0; }

    size_t read(size_t size, void* buf) HS_OVERRIDE;
    size_t write(size_t size, const void* buf) HS_OVERRIDE;

    const uint8_t* data() const { return fData; }

    virtual void resize(uint32_t newsize);
};

#endif
