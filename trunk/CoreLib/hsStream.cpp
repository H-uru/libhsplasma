#include <string.h>
#include "hsStream.h"
#include "../DynLib/Platform.h"

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

void hsStream::setVer(PlasmaVer pv) { ver = pv; }
PlasmaVer hsStream::getVer() const { return ver; }

uint32 hsStream::size() const {
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

uint32 hsStream::pos() const {
    return ftell(F);
}

bool hsStream::eof() const {
    return feof(F);
}

void hsStream::seek(uint32 pos) {
    fseek(F, pos, SEEK_SET);
}

void hsStream::skip(uint32 count) {
    fseek(F, count, SEEK_CUR);
}

void hsStream::fastForward() {
    fseek(F, 0, SEEK_SET);
}

void hsStream::rewind() {
    fseek(F, 0, SEEK_END);
}

void hsStream::read(size_t size, void* buf) {
    fread(buf, size, 1, F);
}

void hsStream::write(size_t size, const void* buf) {
    fwrite(buf, size, 1, F);
}

byte hsStream::readByte() {
    byte v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readBytes(size_t count, byte* buf) {
    read(count * sizeof(byte), buf);
}

int16 hsStream::readShort() {
    int16 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readShorts(size_t count, int16* buf) {
    read(count * sizeof(int16), buf);
}

int32 hsStream::readInt() {
    int32 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readInts(size_t count, int32* buf) {
    read(count * sizeof(int32), buf);
}

int32 hsStream::readIntSwap() {
    int32 v;
    read(sizeof(v), &v);
    return ENDSWAP32(v);
}

float hsStream::readFloat() {
    float v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readFloats(size_t count, float* buf) {
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

void hsStream::readBools(size_t count, bool* buf) {
    for (unsigned int i=0; i<count; i++)
        buf[i] = readBool();
}

plString hsStream::readStr(int len) {
    char* buf = new char[len+1];
    read(len * sizeof(char), buf);
    buf[len] = 0;
    plString str(buf);
    delete[] buf;
    return str;
}

plString hsStream::readSafeStr() {
    uint16 ssInfo = (uint16)readShort();
    char* buf;
    if (ver == pvEoa) {
        buf = new char[ssInfo+1];
        read(ssInfo, buf);
        for (int i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
        buf[ssInfo] = 0;
    } else {
        if (!(ssInfo & 0xF000)) readByte(); // Discarded - debug
        uint16 size = (ssInfo & 0x0FFF);
        buf = new char[size+1];
        read(ssInfo & 0x0FFF, buf);
        if (ssInfo & 0xF000) {
            for (int i=0; i<(ssInfo & 0x0FFF); i++)
                buf[i] = ~buf[i];
        }
        buf[size] = 0;
    }
    plString str(buf);
    delete[] buf;
    return str;
}

plString hsStream::readLine() {
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
    plString str(buf);
    delete[] buf;
    return str;
}

void hsStream::writeByte(const byte v) {
    write(sizeof(v), &v);
}

void hsStream::writeBytes(size_t count, const byte* buf) {
    write(count * sizeof(byte), buf);
}

void hsStream::writeShort(const int16 v) {
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const int16* buf) {
    write(count * sizeof(int16), buf);
}

void hsStream::writeInt(const int32 v) {
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const int32* buf) {
    write(count * sizeof(int32), buf);
}

void hsStream::writeIntSwap(const int32 v) {
    int tv = ENDSWAP32(v);
    write(sizeof(tv), &tv);
}

void hsStream::writeFloat(const float v) {
    write(sizeof(v), &v);
}

void hsStream::writeFloats(size_t count, const float* buf) {
    write(count * sizeof(float), buf);
}

void hsStream::writeDouble(const double v) {
    write(sizeof(v), &v);
}

void hsStream::writeBool(const bool v) {
    char b = v ? 1 : 0;
    write(sizeof(b), &b);
}

void hsStream::writeBools(size_t count, const bool* buf) {
    for (size_t i=0; i<count; i++)
        writeBool(buf[i]);
}

void hsStream::writeStr(const plString& str) {
    write(str.len(), str.cstr());
}

void hsStream::writeSafeStr(const plString& str) {
    uint16 ssInfo = (uint16)str.len();
    char* wbuf;
    if (ver == pvEoa) {
        writeShort(ssInfo);
        wbuf = new char[ssInfo];
        for (int i=0; i<ssInfo; i++)
            wbuf[i] = str[i] ^ eoaStrKey[i%8];
        write(ssInfo, wbuf);
    } else {
        ssInfo = (ssInfo & 0x0FFF) | 0xF000;
        writeShort(ssInfo);
        wbuf = new char[ssInfo & 0x0FFF];
        for (int i=0; i<(ssInfo & 0x0FFF); i++)
            wbuf[i] = ~str[i];
        write(ssInfo & 0x0FFF, wbuf);
    }
}

void hsStream::writeLine(const plString& ln, bool winEOL) {
    if (ln.len() > 4096)
        throw "Line too long!";
    writeStr(ln);
    if (winEOL)
        writeByte('\r');
    writeByte('\n');
}

