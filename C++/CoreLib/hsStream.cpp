#include <string.h>
#include "hsStream.h"

hsStream::hsStream(const char* file, FileMode mode) {
    char* fm;
    switch (mode) {
      case fmRead:
        fm = "rb";
        break;
      case fmWrite:
        fm = "wb";
        break;
      case fmCreate:
        fm = "w+b";
        break;
      case fmReadWrite:
        fm = "r+b";
        break;
      default:
        fm = "";
        break;
    }
    F = fopen(file, fm);
}

hsStream::~hsStream() {
    fclose(F);
}

void hsStream::setVer(PlasmaVer pv) { ver = pv; }
PlasmaVer hsStream::getVer() { return ver; }

long long hsStream::size() {
    long register p = ftell(F);
    fseek(F, 0, SEEK_END);
    long long sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

long long hsStream::pos() {
    return ftell(F);
}

bool hsStream::eof() {
    return feof(F);
}

void hsStream::seek(long long pos) {
    fseek(F, pos, SEEK_SET);
}

void hsStream::fastForward(long long count) {
    fseek(F, count, SEEK_CUR);
}

void hsStream::rewind(long long count) {
    fseek(F, 0-count, SEEK_CUR);
}

char hsStream::readByte() {
    char v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

short hsStream::readShort() {
    short v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

int hsStream::readInt() {
    int v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

long long hsStream::readLong() {
    long long v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

float hsStream::readFloat() {
    float v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

double hsStream::readDouble() {
    double v;
    fread(&v, sizeof(v), 1, F);
    return v;
}

bool hsStream::readBool() {
    char v;
    fread(&v, sizeof(v), 1, F);
    return v ? true : false;
}

char* hsStream::readStr(int len) {
    char* buf = new char[len];
    fread(buf, sizeof(char), len, F);
    return buf;
}

char* hsStream::readStrZ(int len) {
    char* buf = new char[len+1];
    fread(buf, sizeof(char), len, F);
    buf[len] = '\0';
    return buf;
}

char* hsStream::readSafeStr() {
    unsigned short ssInfo = (unsigned short) readShort();
    char* buf;
    if (ver == pvEoa) {
        buf = readStrZ(ssInfo);
        for (int i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
    } else {
        if (!(ssInfo & 0xF000)) readByte(); // Discarded - debug
        buf = readStrZ(ssInfo & 0x0FFF);
        if (ssInfo & 0xF000) {
            for (int i=0; i<(ssInfo & 0x0FFF); i++)
                buf[i] = ~buf[i];
        }
    }
    return buf;
}

void hsStream::writeByte(const char v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeShort(const short v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeInt(const int v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeLong(const long long v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeFloat(const float v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeDouble(const double v) {
    fwrite(&v, sizeof(v), 1, F);
}

void hsStream::writeBool(const bool v) {
    char b = v ? 1 : 0;
    fwrite(&b, sizeof(b), 1, F);
}

void hsStream::writeStr(const char* buf, int len) {
    fwrite(buf, sizeof(char), len, F);
}

void hsStream::writeStr(const char* buf) {
    writeStr(buf, strlen(buf));
}

void hsStream::writeSafeStr(const char* buf) {
    unsigned short ssInfo = (unsigned short) strlen(buf);
    char* wbuf;
    if (ver == pvEoa) {
        writeShort(ssInfo);
        wbuf = new char[ssInfo];
        for (int i=0; i<ssInfo; i++)
            wbuf[i] = buf[i] ^ eoaStrKey[i%8];
        writeStr(wbuf, ssInfo);
    } else {
        ssInfo = (ssInfo & 0x0FFF) | 0xF000;
        writeShort(ssInfo);
        wbuf = new char[ssInfo & 0x0FFF];
        for (int i=0; i<(ssInfo & 0x0FFF); i++)
            wbuf[i] = ~buf[i];
        writeStr(wbuf, ssInfo & 0x0FFF);
    }
}
