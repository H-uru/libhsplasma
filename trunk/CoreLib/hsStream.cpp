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

hsUint32 hsStream::size() const {
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

hsUint32 hsStream::pos() const {
    return ftell(F);
}

bool hsStream::eof() const {
    return feof(F);
}

void hsStream::seek(hsUint32 pos) {
    fseek(F, pos, SEEK_SET);
}

void hsStream::skip(hsUint32 count) {
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

hsByte hsStream::readByte() {
    hsByte v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readBytes(size_t count, hsByte* buf) {
    read(count * sizeof(hsByte), buf);
}

hsInt16 hsStream::readShort() {
    hsInt16 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readShorts(size_t count, hsInt16* buf) {
    read(count * sizeof(hsInt16), buf);
}

hsInt32 hsStream::readInt() {
    hsInt32 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readInts(size_t count, hsInt32* buf) {
    read(count * sizeof(hsInt32), buf);
}

hsInt32 hsStream::readIntSwap() {
    hsInt32 v;
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
    hsUint16 ssInfo = (hsUint16)readShort();
    char* buf;
    if (ver == pvEoa) {
        buf = new char[ssInfo+1];
        read(ssInfo, buf);
        for (int i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
        buf[ssInfo] = 0;
    } else {
        if (!(ssInfo & 0xF000)) readByte(); // Discarded - debug
        hsUint16 size = (ssInfo & 0x0FFF);
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
            throw hsFileReadException(__FILE__, __LINE__, "Line too long");
    }
    buf[i] = 0;
    if (c == '\r')
        readByte(); // Eat the \n in Windows-style EOLs
    plString str(buf);
    delete[] buf;
    return str;
}

void hsStream::writeByte(const hsByte v) {
    write(sizeof(v), &v);
}

void hsStream::writeBytes(size_t count, const hsByte* buf) {
    write(count * sizeof(hsByte), buf);
}

void hsStream::writeShort(const hsInt16 v) {
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const hsInt16* buf) {
    write(count * sizeof(hsInt16), buf);
}

void hsStream::writeInt(const hsInt32 v) {
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const hsInt32* buf) {
    write(count * sizeof(hsInt32), buf);
}

void hsStream::writeIntSwap(const hsInt32 v) {
    hsInt32 tv = ENDSWAP32(v);
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
    hsUint16 ssInfo = (hsUint16)str.len();
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
        throw hsFileWriteException(__FILE__, __LINE__, "Line too long!");
    writeStr(ln);
    if (winEOL)
        writeByte('\r');
    writeByte('\n');
}


// hsFileReadException //
hsFileReadException::hsFileReadException(const char* file,
                     unsigned long line, const char* filename) throw()
                   : hsException(file, line) {
    fWhat = "Error reading file";
    if (filename != NULL)
        fWhat += plString(": ") + filename;
}


// hsFileWriteException //
hsFileWriteException::hsFileWriteException(const char* file,
                      unsigned long line, const char* filename) throw()
                    : hsException(file, line) {
    fWhat = "Error writing to file";
    if (filename != NULL)
        fWhat += plString(": ") + filename;
}
