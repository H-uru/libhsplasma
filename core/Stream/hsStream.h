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
#include <time.h>
#include <string_theory/string>
#include "Util/PlasmaVersions.h"
#include "Sys/Platform.h"
#include "PlasmaDefs.h"
#include "Debug/hsExceptions.hpp"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

class PLASMA_DLL hsStream
{
protected:
    PlasmaVer ver;

public:
    explicit hsStream(int pv = PlasmaVer::pvUnknown) { setVer(PlasmaVer(pv)); }
    virtual ~hsStream() { }

    virtual void close() { }

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
    ST::string readStr(size_t len);
    ST::string readSafeStr();
    ST::string readSafeWStr();
    virtual ST::string readLine();

    void writeByte(uint8_t v);
    void writeShort(uint16_t v);
    void writeShorts(size_t count, const uint16_t* buf);
    void writeInt(uint32_t v);
    void writeInts(size_t count, const uint32_t* buf);
    void writeIntSwap(uint32_t v);
    void writeFloat(float v);
    void writeDouble(double v);
    void writeBool(bool v);
    void writeStr(const ST::string& str);
    void writeSafeStr(const ST::string& str);
    void writeSafeWStr(const ST::string& str);
    virtual void writeLine(const ST::string& ln, bool winEOL = false);
};

class PLASMA_DLL hsFileStream : public hsStream {
protected:
    FILE* F;
    FileMode fm;

public:
    explicit hsFileStream(int pv = PlasmaVer::pvUnknown) : hsStream(pv), F() { }
    ~hsFileStream() { close(); }

    static bool FileExists(const ST::string& file);

    virtual bool open(const ST::string& file, FileMode mode);
    void close() HS_OVERRIDE;

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

    time_t getModTime() const;
};

class hsFileReadException : public hsException
{
public:
    inline hsFileReadException(const char* file, unsigned long line,
                               const char* filename = nullptr) HS_NOEXCEPT
        : hsException(ST_LITERAL("Error reading file"), file, line)
    {
        if (filename != nullptr)
            fWhat += ST_LITERAL(": ") + filename;
    }
};

class hsFileWriteException : public hsException
{
public:
    inline hsFileWriteException(const char* file, unsigned long line,
                                const char* filename = nullptr) HS_NOEXCEPT
        : hsException(ST_LITERAL("Error writing to file"), file, line)
    {
        if (filename != nullptr)
            fWhat += ST_LITERAL(": ") + filename;
    }
};

#endif
