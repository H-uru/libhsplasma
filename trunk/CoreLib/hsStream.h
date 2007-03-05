#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include "../PlasmaDefs.h"
#include <stdio.h>
#include "../DynLib/PlasmaVersions.h"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

class DllExport hsStream {
protected:
    PlasmaVer ver;
    FILE * F;
    FileMode fm;

public:
    hsStream(PlasmaVer pv = pvUnknown);
    virtual ~hsStream();

    virtual bool open(const char* file, FileMode mode);
    virtual void close();

    virtual void setVer(PlasmaVer pv, bool mutate=false);
    PlasmaVer getVer();

    virtual unsigned int size();
    virtual unsigned int pos();
    virtual bool eof();
    
    virtual void seek(unsigned int pos);
    virtual void skip(unsigned int count);
    virtual void fastForward();
    virtual void rewind();

    virtual void read(unsigned int size, void* buf);
    virtual void write(unsigned int size, const void* buf);

    char readByte();
    void readBytes(unsigned int count, char* buf);
    short readShort();
    void readShorts(unsigned int count, short* buf);
    int readInt();
    void readInts(unsigned int count, int* buf);
    int readIntSwap();
    float readFloat();
    void readFloats(unsigned int count, float* buf);
    double readDouble();
    bool readBool();
    void readBools(unsigned int count, bool* buf);
    char* readStr(int len);
    char* readSafeStr();
    virtual char* readLine();

    void writeByte(const char v);
    void writeBytes(unsigned int count, const char* buf);
    void writeShort(const short v);
    void writeShorts(unsigned int count, const short* buf);
    void writeInt(const int v);
    void writeInts(unsigned int count, const int* buf);
    void writeIntSwap(const int v);
    void writeFloat(const float v);
    void writeFloats(unsigned int count, const float* buf);
    void writeDouble(const double v);
    void writeBool(const bool v);
    void writeBools(unsigned int count, const bool* buf);
    void writeStr(const char* buf, int len);
    void writeStr(const char* buf);
    void writeSafeStr(const char* buf);
    virtual void writeLine(const char* ln, bool winEOL = false);
};

#endif

