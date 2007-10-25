#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include <stdio.h>
#include "plString.h"
#include "../PlasmaDefs.h"
#include "../DynLib/PlasmaVersions.h"
#include "hsExceptions.h"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

DllClass hsStream {
protected:
    PlasmaVer ver;
    FILE* F;
    FileMode fm;

public:
    hsStream(PlasmaVer pv = pvUnknown);
    virtual ~hsStream();

    virtual bool open(const char* file, FileMode mode);
    virtual void close();

    virtual void setVer(PlasmaVer pv);
    PlasmaVer getVer() const;

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;
    
    virtual void seek(hsUint32 pos);
    virtual void skip(hsUint32 count);
    virtual void fastForward();
    virtual void rewind();

    virtual void read(size_t size, void* buf);
    virtual void write(size_t size, const void* buf);

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
    plString readStr(int len);
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

