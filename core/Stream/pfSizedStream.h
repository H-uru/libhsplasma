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

#ifndef _PFSIZEDSTREAM_H
#define _PFSIZEDSTREAM_H

#include "hsStream.h"

class PLASMA_DLL pfSizedStream : public hsStream
{
private:
    hsStream* fBase;
    uint32_t fLength; //!< the length of the substream - not the end position of it!
    uint32_t fBegin;

public:
    pfSizedStream(hsStream* S, uint32_t len);
    ~pfSizedStream() { } // Do NOT free fBase!!!

    uint32_t size() const HS_OVERRIDE { return fLength; }
    uint32_t pos() const HS_OVERRIDE { return fBase->pos() - fBegin; }
    bool eof() const HS_OVERRIDE { return fBase->eof() || pos() == fLength; }

    void seek(uint32_t pos) HS_OVERRIDE;
    void skip(int32_t count) HS_OVERRIDE;
    void fastForward() HS_OVERRIDE { fBase->seek(fBegin + fLength); }
    void rewind() HS_OVERRIDE { fBase->seek(fBegin); }
    void flush() HS_OVERRIDE { fBase->flush(); }

    size_t read(size_t size, void* buf) HS_OVERRIDE;
    size_t write(size_t size, const void* buf) HS_OVERRIDE;
};

#endif
