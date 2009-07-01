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
    explicit hsStream(PlasmaVer pv = pvUnknown);
    virtual ~hsStream();

    virtual void setVer(PlasmaVer pv);
    PlasmaVer getVer() const;

    virtual hsUint32 size() const = 0;
    virtual hsUint32 pos() const = 0;
    virtual bool eof() const = 0;

    virtual void seek(hsUint32 pos) = 0;
    virtual void skip(hsInt32 count) = 0;
    virtual void fastForward() = 0;
    virtual void rewind() = 0;
    virtual void flush();

    virtual size_t read(size_t size, void* buf) = 0;
    virtual size_t write(size_t size, const void* buf) = 0;
    void writeFrom(hsStream* src);

    hsUbyte readByte();
    void readBytes(size_t count, hsUbyte* buf);
    hsUint16 readShort();
    void readShorts(size_t count, hsUint16* buf);
    hsUint32 readInt();
    void readInts(size_t count, hsUint32* buf);
    hsUint32 readIntSwap();
    float readFloat();
    void readFloats(size_t count, float* buf);
    double readDouble();
    bool readBool();
    void readBools(size_t count, bool* buf);
    plString readStr(size_t len);
    plString readSafeStr();
    plWString readSafeWStr();
    virtual plString readLine();

    void writeByte(const hsUbyte v);
    void writeBytes(size_t count, const hsUbyte* buf);
    void writeShort(const hsUint16 v);
    void writeShorts(size_t count, const hsUint16* buf);
    void writeInt(const hsUint32 v);
    void writeInts(size_t count, const hsUint32* buf);
    void writeIntSwap(const hsUint32 v);
    void writeFloat(const float v);
    void writeFloats(size_t count, const float* buf);
    void writeDouble(const double v);
    void writeBool(const bool v);
    void writeBools(size_t count, const bool* buf);
    void writeStr(const plString& str);
    void writeSafeStr(const plString& str);
    void writeSafeWStr(const plWString& str);
    virtual void writeLine(const plString& ln, bool winEOL = false);
};

DllClass hsFileStream : public hsStream {
protected:
    FILE* F;
    FileMode fm;

public:
    explicit hsFileStream(PlasmaVer pv = pvUnknown);
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
