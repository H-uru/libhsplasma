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

#include "pfSizedStream.h"
#include "Debug/plDebug.h"

pfSizedStream::pfSizedStream(hsStream* S, hsUint32 len)
        : fBase(S), fLength(len) {
    if (S != NULL) {
        ver = S->getVer();

        fBegin = S->pos();

        if (S->size() - fBegin < len) {
            throw hsBadParamException(__FILE__, __LINE__, "Stream too small");
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__, "Null Stream");
    }
}

pfSizedStream::~pfSizedStream() { } // Do NOT free fBase!!!

void pfSizedStream::seek(hsUint32 pos) {
    if (pos > fLength) {
        plDebug::Warning("Seek past end of stream. %d requested, %d maximum",
                         pos, fLength);
    }

    fBase->seek(fBegin + pos);
}

void pfSizedStream::skip(hsInt32 count) {
    if (pos() + count > fLength) { // pos() is the index in the sub-stream
        throw hsFileReadException(__FILE__, __LINE__, plString::Format("Seek out of range: %d bytes requested, %d available",
                         count, (fLength - pos())));
    }

    fBase->skip(count);
}

void pfSizedStream::fastForward() {
    fBase->seek(fBegin + fLength);
}

void pfSizedStream::rewind() {
    fBase->seek(fBegin);
}

void pfSizedStream::flush() {
    fBase->flush();
}

size_t pfSizedStream::read(size_t size, void* buf) {
    if (pos() + size > fLength) { // pos() is the index in the sub-stream
        throw hsFileReadException(__FILE__, __LINE__, plString::Format("Read past end of sized stream: %d bytes requested, %d available",
                         size, (fLength - pos())));
    }

    return fBase->read(size, buf);
}

size_t pfSizedStream::write(size_t size, const void* buf) {
    if (pos() + size > fLength) { // pos() is the index in the sub-stream
        throw hsFileReadException(__FILE__, __LINE__, plString::Format("Write past end of sized stream: %d bytes requested, %d available",
                         size, (fLength - pos())));
    }

    return fBase->write(size, buf);
}
