#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include <stdio.h>
#include "plString.h"
#include "../PlasmaDefs.h"
#include "../DynLib/PlasmaVersions.h"

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

    hsByte readByte();
    void readBytes(size_t count, hsByte* buf);
    hsInt16 readShort();
    void readShorts(size_t count, hsInt16* buf);
    hsInt32 readInt();
    void readInts(size_t count, hsInt32* buf);
    hsInt32 readIntSwap();
    float readFloat();
    void readFloats(size_t count, float* buf);
    double readDouble();
    bool readBool();
    void readBools(size_t count, bool* buf);
    plString readStr(int len);
    plString readSafeStr();
    virtual plString readLine();

    void writeByte(const hsByte v);
    void writeBytes(size_t count, const hsByte* buf);
    void writeShort(const hsInt16 v);
    void writeShorts(size_t count, const hsInt16* buf);
    void writeInt(const hsInt32 v);
    void writeInts(size_t count, const hsInt32* buf);
    void writeIntSwap(const hsInt32 v);
    void writeFloat(const float v);
    void writeFloats(size_t count, const float* buf);
    void writeDouble(const double v);
    void writeBool(const bool v);
    void writeBools(size_t count, const bool* buf);
    void writeStr(const plString& str);
    void writeSafeStr(const plString& str);
    virtual void writeLine(const plString& ln, bool winEOL = false);
};

#endif

