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

#ifndef _HSWINDOWSSTREAM_H
#define _HSWINDOWSSTREAM_H

#include "hsStream.h"

#ifdef _WIN32

class HSPLASMA_EXPORT hsWindowsStream : public hsStream
{
protected:
    /* HANDLE */ void* F;
    FileMode fm;

public:
    explicit hsWindowsStream(int pv = PlasmaVer::pvUnknown) : hsStream(pv), F(), fm() {}
    ~hsWindowsStream() { close(); }

    bool open(const ST::string& file, FileMode mode);
    void close();

    uint32_t size() const HS_OVERRIDE;
    uint32_t pos() const HS_OVERRIDE;
    bool eof() const HS_OVERRIDE;

    void seek(uint32_t pos) HS_OVERRIDE;
    void skip(int32_t count) HS_OVERRIDE;
    void fastForward() HS_OVERRIDE;
    void rewind() HS_OVERRIDE;
    void flush() HS_OVERRIDE;

    size_t read(size_t size, void* buf) HS_OVERRIDE;
    size_t write(size_t size, const void* buf) HS_OVERRIDE;
};

#endif

#endif
