#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include <stdio.h>
#include "../DynLib/PlasmaVersions.h"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

static const char eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};

class hsStream {
protected:
    PlasmaVer ver;
    FILE * F;

public:
    hsStream();
    ~hsStream();

    void open(const char* file, FileMode mode);
    void close();

    void setVer(PlasmaVer pv, bool mutate=false);
    PlasmaVer getVer();

    long long size();
    long long pos();
    bool eof();
    
    void seek(long long pos);
    void skip(long long count);
    void fastForward();
    void rewind();

    char readByte();
    short readShort();
    int readInt();
    int readIntSwap();
    long long readLong();
    float readFloat();
    double readDouble();
    bool readBool();
    char* readStr(int len);
    char* readStrZ(int len);
    char* readSafeStr();

    void writeByte(const char v);
    void writeShort(const short v);
    void writeInt(const int v);
    void writeIntSwap(const int v);
    void writeLong(const long long v);
    void writeFloat(const float v);
    void writeDouble(const double v);
    void writeBool(const bool v);
    void writeStr(const char* buf, int len);
    void writeStr(const char* buf);
    //void writeZStr(char* buf);
    void writeSafeStr(const char* buf);
};

#endif
