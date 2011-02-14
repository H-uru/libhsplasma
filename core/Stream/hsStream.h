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

class PLASMA_DLL hsStream {
protected:
    PlasmaVer ver;

public:
    explicit hsStream(int pv = PlasmaVer::pvUnknown);
    virtual ~hsStream() { }

    PlasmaVer getVer() const { return ver; }
    virtual void setVer(PlasmaVer pv) { ver = pv; }

    virtual uint32_t size() const = 0;
    virtual uint32_t pos() const = 0;
    virtual bool eof() const = 0;

    virtual void seek(uint32_t pos) = 0;
    virtual void skip(int32_t count) = 0;
    virtual void fastForward() = 0;
    virtual void rewind() = 0;
    virtual void flush() { }

    virtual size_t read(size_t size, void* buf) = 0;
    virtual size_t write(size_t size, const void* buf) = 0;
    void writeFrom(hsStream* src);

    uint8_t readByte();
    uint16_t readShort();
    void readShorts(size_t count, uint16_t* buf);
    uint32_t readInt();
    void readInts(size_t count, uint32_t* buf);
    uint32_t readIntSwap();
    float readFloat();
    double readDouble();
    bool readBool();
    plString readStr(size_t len);
    plString readSafeStr();
    plString readSafeWStr();
    virtual plString readLine();

    void writeByte(uint8_t v);
    void writeShort(uint16_t v);
    void writeShorts(size_t count, const uint16_t* buf);
    void writeInt(uint32_t v);
    void writeInts(size_t count, const uint32_t* buf);
    void writeIntSwap(uint32_t v);
    void writeFloat(float v);
    void writeDouble(double v);
    void writeBool(bool v);
    void writeStr(const plString& str);
    void writeSafeStr(const plString& str);
    void writeSafeWStr(const plString& str);
    virtual void writeLine(const plString& ln, bool winEOL = false);
};

class PLASMA_DLL hsFileStream : public hsStream {
protected:
    FILE* F;
    FileMode fm;

public:
    explicit hsFileStream(int pv = PlasmaVer::pvUnknown);
    virtual ~hsFileStream();

    static bool FileExists(const char* file);

    virtual bool open(const char* file, FileMode mode);
    virtual void close();

    virtual uint32_t size() const;
    virtual uint32_t pos() const;
    virtual bool eof() const;

    virtual void seek(uint32_t pos);
    virtual void skip(int32_t count);
    virtual void fastForward();
    virtual void rewind();
    virtual void flush();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    time_t getModTime() const;
};

class PLASMA_DLL hsFileReadException : public hsException {
public:
    hsFileReadException(const char* file, unsigned long line,
                        const char* filename = NULL) throw();
};

class PLASMA_DLL hsFileWriteException : public hsException {
public:
    hsFileWriteException(const char* file, unsigned long line,
                         const char* filename = NULL) throw();
};

#endif
