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

    virtual uint32 size() const;
    virtual uint32 pos() const;
    virtual bool eof() const;
    
    virtual void seek(uint32 pos);
    virtual void skip(uint32 count);
    virtual void fastForward();
    virtual void rewind();

    virtual void read(size_t size, void* buf);
    virtual void write(size_t size, const void* buf);

    byte readByte();
    void readBytes(size_t count, byte* buf);
    int16 readShort();
    void readShorts(size_t count, int16* buf);
    int32 readInt();
    void readInts(size_t count, int32* buf);
    int32 readIntSwap();
    float readFloat();
    void readFloats(size_t count, float* buf);
    double readDouble();
    bool readBool();
    void readBools(size_t count, bool* buf);
    plString readStr(int len);
    plString readSafeStr();
    virtual plString readLine();

    void writeByte(const byte v);
    void writeBytes(size_t count, const byte* buf);
    void writeShort(const int16 v);
    void writeShorts(size_t count, const int16* buf);
    void writeInt(const int32 v);
    void writeInts(size_t count, const int32* buf);
    void writeIntSwap(const int32 v);
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

