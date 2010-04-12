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

#ifndef _HSSTDIOSTREAM_H
#define _HSSTDIOSTREAM_H

#include "hsStream.h"

DllClass hsStdioStream : public hsFileStream {
protected:
    FILE* Fin;
    FILE* Fout;

public:
    explicit hsStdioStream(bool useStdErr = false);

    virtual bool open(const char*, FileMode) { return false; }
    virtual void close() { }

    virtual hsUint32 size() const { return 0; }
    virtual hsUint32 pos() const { return 0; }
    virtual bool eof() const { return false; }

    virtual void seek(hsUint32 pos);
    virtual void skip(hsInt32 count);
    virtual void fastForward() { }
    virtual void rewind() { }
    virtual void flush();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    void setFiles(FILE* in, FILE* out) { Fin = in; Fout = out; }
    FILE* getInFile() { return Fin; }
    FILE* getOutFile() { return Fout; }
};

#endif
