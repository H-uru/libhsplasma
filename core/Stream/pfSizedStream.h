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

DllClass pfSizedStream : public hsStream {
private:
    hsStream* fBase;
    hsUint32 fLength; //!< the length of the substream - not the end position of it!
    hsUint32 fBegin;

public:
    pfSizedStream(hsStream* S, hsUint32 len);
    virtual ~pfSizedStream();

    virtual hsUint32 size() const { return fLength; }
    virtual hsUint32 pos() const { return fBase->pos() - fBegin; }
    virtual bool eof() const { return fBase->eof() || pos() == fLength; }

    virtual void seek(hsUint32 pos);
    virtual void skip(hsInt32 count);
    virtual void fastForward();
    virtual void rewind();
    virtual void flush();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);
};

#endif
