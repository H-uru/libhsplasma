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

#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include <stdlib.h>
#include <stdio.h>
#include "Util/plString.h"
#include "Util/PlasmaVersions.h"
#include "Sys/Platform.h"
#include "PlasmaDefs.h"
#include "Debug/hsExceptions.h"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

DllClass hsStream {
protected:
    PlasmaVer ver;

public:
    explicit hsStream(int pv = PlasmaVer::pvUnknown);
    virtual ~hsStream() { }

    PlasmaVer getVer() const { return ver; }
    virtual void setVer(PlasmaVer pv) { ver = pv; }

    virtual hsUint32 size() const = 0;
    virtual hsUint32 pos() const = 0;
    virtual bool eof() const = 0;

    virtual void seek(hsUint32 pos) = 0;
    virtual void skip(hsInt32 count) = 0;
    virtual void fastForward() = 0;
    virtual void rewind() = 0;
    virtual void flush() { }

    virtual size_t read(size_t size, void* buf) = 0;
    virtual size_t write(size_t size, const void* buf) = 0;
    void writeFrom(hsStream* src);

    hsUbyte readByte();
    hsUint16 readShort();
    void readShorts(size_t count, hsUint16* buf);
    hsUint32 readInt();
    void readInts(size_t count, hsUint32* buf);
    hsUint32 readIntSwap();
    float readFloat();
    double readDouble();
    bool readBool();
    plString readStr(size_t len);
    plString readSafeStr();
    plString readSafeWStr();
    virtual plString readLine();

    void writeByte(hsUbyte v);
    void writeShort(hsUint16 v);
    void writeShorts(size_t count, const hsUint16* buf);
    void writeInt(hsUint32 v);
    void writeInts(size_t count, const hsUint32* buf);
    void writeIntSwap(hsUint32 v);
    void writeFloat(float v);
    void writeDouble(double v);
    void writeBool(bool v);
    void writeStr(const plString& str);
    void writeSafeStr(const plString& str);
    void writeSafeWStr(const plString& str);
    virtual void writeLine(const plString& ln, bool winEOL = false);
};

DllClass hsFileStream : public hsStream {
protected:
    FILE* F;
    FileMode fm;

public:
    explicit hsFileStream(int pv = PlasmaVer::pvUnknown);
    virtual ~hsFileStream();

    static bool FileExists(const char* file);

    virtual bool open(const char* file, FileMode mode);
    virtual void close();

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;

    virtual void seek(hsUint32 pos);
    virtual void skip(hsInt32 count);
    virtual void fastForward();
    virtual void rewind();
    virtual void flush();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    time_t getModTime() const;
};

DllClass hsFileReadException : public hsException {
public:
    hsFileReadException(const char* file, unsigned long line,
                        const char* filename = NULL) throw();
};

DllClass hsFileWriteException : public hsException {
public:
    hsFileWriteException(const char* file, unsigned long line,
                         const char* filename = NULL) throw();
};

#endif
