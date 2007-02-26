#include <string.h>
#include "hsStream.h"

static const char eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};

hsStream::hsStream(PlasmaVer pv) : F(NULL) {
    setVer(pv);
}

hsStream::~hsStream() {
    close();
}

bool hsStream::open(const char* file, FileMode mode) {
    char* fms;
    switch (mode) {
      case fmRead:
        fms = "rb";
        break;
      case fmWrite:
        fms = "wb";
        break;
      case fmCreate:
        fms = "w+b";
        break;
      case fmReadWrite:
        fms = "r+b";
        break;
      default:
        fms = "";
        break;
    }
    F = fopen(file, fms);
    if (F != NULL) {
        fm = mode;
        return true;
    }
    return false;
}

void hsStream::close() {
    if (F) fclose(F);
    F = NULL;
}

void hsStream::setVer(PlasmaVer pv, bool mutate) { ver = pv; }
PlasmaVer hsStream::getVer() { return ver; }

unsigned int hsStream::size() {
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

unsigned int hsStream::pos() {
    return ftell(F);
}

bool hsStream::eof() {
    return feof(F);
}

void hsStream::seek(unsigned int pos) {
    fseek(F, pos, SEEK_SET);
}

void hsStream::skip(unsigned int count) {
    fseek(F, count, SEEK_CUR);
}

void hsStream::fastForward() {
    fseek(F, 0, SEEK_SET);
}

void hsStream::rewind() {
    fseek(F, 0, SEEK_END);
}

void hsStream::read(unsigned int size, void* buf) {
    fread(buf, size, 1, F);
}

void hsStream::write(unsigned int size, const void* buf) {
    fwrite(buf, size, 1, F);
}

void SwapByteOrder(int* value) {
    union {
        int i;
        char c[4];
    } v;
    v.i = *value;
    char t = v.c[3];
    v.c[3] = v.c[0];
    v.c[0] = t;
    t = v.c[2];
    v.c[2] = v.c[1];
    v.c[1] = t;
    *value = v.i;
}

char hsStream::readByte() {
    char v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readBytes(unsigned int count, char* buf) {
    read(count * sizeof(char), buf);
}

short hsStream::readShort() {
    short v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readShorts(unsigned int count, short* buf) {
    read(count * sizeof(short), buf);
}

int hsStream::readInt() {
    int v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readInts(unsigned int count, int* buf) {
    read(count * sizeof(int), buf);
}

int hsStream::readIntSwap() {
    int v;
    read(sizeof(v), &v);
    SwapByteOrder(&v);
    return v;
}

float hsStream::readFloat() {
    float v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readFloats(unsigned int count, float* buf) {
    read(count * sizeof(float), buf);
}

double hsStream::readDouble() {
    double v;
    read(sizeof(v), &v);
    return v;
}

bool hsStream::readBool() {
    return readByte() == 0 ? false : true;
}

void hsStream::readBools(unsigned int count, bool* buf) {
    for (unsigned int i=0; i<count; i++)
        buf[i] = readBool();
}

char* hsStream::readStr(int len) {
    char* buf = new char[len+1];
    read(len * sizeof(char), buf);
    buf[len] = 0;
    return buf;
}

char* hsStream::readSafeStr() {
    unsigned short ssInfo = (unsigned short) readShort();
    char* buf;
    if (ver == pvEoa) {
        buf = readStr(ssInfo);
        for (int i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
    } else {
        if (!(ssInfo & 0xF000)) readByte(); // Discarded - debug
        buf = readStr(ssInfo & 0x0FFF);
        if (ssInfo & 0xF000) {
            for (int i=0; i<(ssInfo & 0x0FFF); i++)
                buf[i] = ~buf[i];
        }
    }
    return buf;
}

char* hsStream::readLine() {
    char* buf = new char[4096];
    unsigned int i = 0;
    char c = readByte();
    while (c != '\n' && c != '\r') {
        buf[i++] = c;
        c = readByte();
        if (i >= 4096)
            throw "Line too long!";
    }
    buf[i] = 0;
    if (c == '\r')
        readByte(); // Eat the \n in Windows-style EOLs
    return buf;
}

void hsStream::writeByte(const char v) {
    write(sizeof(v), &v);
}

void hsStream::writeBytes(unsigned int count, const char* buf) {
    write(count * sizeof(char), buf);
}

void hsStream::writeShort(const short v) {
    write(sizeof(v), &v);
}

void hsStream::writeShorts(unsigned int count, const short* buf) {
    write(count * sizeof(short), buf);
}

void hsStream::writeInt(const int v) {
    write(sizeof(v), &v);
}

void hsStream::writeInts(unsigned int count, const int* buf) {
    write(count * sizeof(int), buf);
}

void hsStream::writeIntSwap(const int v) {
    int tv = v;
    SwapByteOrder(&tv);
    write(sizeof(tv), &tv);
}

void hsStream::writeFloat(const float v) {
    write(sizeof(v), &v);
}

void hsStream::writeFloats(unsigned int count, const float* buf) {
    write(count * sizeof(float), buf);
}

void hsStream::writeDouble(const double v) {
    write(sizeof(v), &v);
}

void hsStream::writeBool(const bool v) {
    char b = v ? 1 : 0;
    write(sizeof(b), &b);
}

void hsStream::writeBools(unsigned int count, const bool* buf) {
    for (unsigned int i=0; i<count; i++)
        writeBool(buf[i]);
}

void hsStream::writeStr(const char* buf, int len) {
    write(len * sizeof(char), buf);
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

void hsStream::writeLine(const char* ln, bool winEOL) {
    writeStr(ln, strlen(ln));
    if (winEOL)
        writeByte('\r');
    writeByte('\n');
}

