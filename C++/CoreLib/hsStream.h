#ifndef _HSSTREAM_H
#define _HSSTREAM_H

#include <stdio.h>
#include "../DynLib/PlasmaVersions.h"

enum FileMode { fmRead, fmWrite, fmReadWrite, fmCreate };

static const char eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};

/**
 * Generic file-based stream -- don't mess with the other stream types for now
 **/
class hsStream {
protected:
    PlasmaVer ver;
    FILE * F;

public:
    hsStream(const char* file, FileMode mode);
    ~hsStream();

    void setVer(PlasmaVer pv);
    PlasmaVer getVer();

    long long size();
    long long pos();
    bool eof();
    
    void seek(long long pos);
    void fastForward(long long count);
    void rewind(long long count);

    char readByte();
    short readShort();
    int readInt();
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
