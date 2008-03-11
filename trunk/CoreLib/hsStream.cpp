#include <string.h>
#include "hsStream.h"
#include "DynLib/Platform.h"

static const char eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};
static const wchar_t eoaWStrKey[8] = {L'm',L'y',L's',L't',L'n',L'e',L'r',L'd'};

// hsStream //
hsStream::hsStream(PlasmaVer pv) {
    setVer(pv);
}

hsStream::~hsStream() { }

void hsStream::setVer(PlasmaVer pv) { ver = pv; }
PlasmaVer hsStream::getVer() const { return ver; }

#define BLOCKSIZE 4096
void hsStream::writeFrom(hsStream* src) {
    unsigned char buf[BLOCKSIZE];
    for (size_t spos = 0; spos < (src->size() / BLOCKSIZE); spos++) {
        src->read(BLOCKSIZE, buf);
        write(BLOCKSIZE, buf);
    }
    size_t endsize = src->size() % BLOCKSIZE;
    src->read(endsize, buf);
    write(endsize, buf);
}

hsUbyte hsStream::readByte() {
    hsUbyte v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readBytes(size_t count, hsUbyte* buf) {
    read(count * sizeof(hsUbyte), buf);
}

hsUint16 hsStream::readShort() {
    hsUint16 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readShorts(size_t count, hsUint16* buf) {
    read(count * sizeof(hsUint16), buf);
}

hsUint32 hsStream::readInt() {
    hsUint32 v;
    read(sizeof(v), &v);
    return v;
}

void hsStream::readInts(size_t count, hsUint32* buf) {
    read(count * sizeof(hsUint32), buf);
}

hsUint32 hsStream::readIntSwap() {
    hsUint32 v;
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

plString hsStream::readStr(size_t len) {
    char* buf = new char[len+1];
    read(len * sizeof(char), buf);
    buf[len] = 0;
    plString str(buf);
    delete[] buf;
    return str;
}

plString hsStream::readSafeStr() {
    hsUint16 ssInfo = readShort();
    char* buf;
    if (ver == pvEoa) {
        buf = new char[ssInfo+1];
        read(ssInfo, buf);
        for (size_t i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
        buf[ssInfo] = 0;
    } else {
        if (!(ssInfo & 0xF000)) readShort(); // Discarded - debug
        hsUint16 size = (ssInfo & 0x0FFF);
        buf = new char[size+1];
        read(size, buf);
        if (buf[0] & 0x80) {
            for (size_t i=0; i<size; i++)
                buf[i] = ~buf[i];
        }
        buf[size] = 0;
    }
    plString str(buf);
    delete[] buf;
    return str;
}

plWString hsStream::readSafeWStr() {
    hsUint16 ssInfo = readShort();
    wchar_t* buf;
    if (ver == pvEoa) {
        buf = new wchar_t[ssInfo+1];
        for (size_t i=0; i<ssInfo; i++)
            buf[i] = (readShort() ^ eoaWStrKey[i%8]) & 0xFFFF;
        readShort();    // Terminator
        buf[ssInfo] = 0;
    } else {
        hsUint16 size = (ssInfo & 0x0FFF);
        buf = new wchar_t[size+1];
        for (size_t i=0; i<size; i++)
            buf[i] = (~readShort()) & 0xFFFF;
        readShort();    // Terminator
        buf[size] = 0;
    }
    plWString str(buf);
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

void hsStream::writeByte(const hsUbyte v) {
    write(sizeof(v), &v);
}

void hsStream::writeBytes(size_t count, const hsUbyte* buf) {
    write(count * sizeof(hsUbyte), buf);
}

void hsStream::writeShort(const hsUint16 v) {
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const hsUint16* buf) {
    write(count * sizeof(hsUint16), buf);
}

void hsStream::writeInt(const hsUint32 v) {
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const hsUint32* buf) {
    write(count * sizeof(hsUint32), buf);
}

void hsStream::writeIntSwap(const hsUint32 v) {
    hsUint32 tv = ENDSWAP32(v);
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
        for (size_t i=0; i<ssInfo; i++)
            wbuf[i] = str[i] ^ eoaStrKey[i%8];
    } else {
        ssInfo &= 0x0FFF;
        writeShort(ssInfo | 0xF000);
        wbuf = new char[ssInfo];
        for (size_t i=0; i<ssInfo; i++)
            wbuf[i] = ~str[i];
    }
    write(ssInfo, wbuf);
    delete[] wbuf;
}

void hsStream::writeSafeWStr(const plWString& str) {
    hsUint16 ssInfo = (hsUint16)str.len();
    if (ver == pvEoa) {
        writeShort(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(str[i] ^ eoaWStrKey[i%8]);
        writeShort(0);  // Terminator
    } else {
        ssInfo &= 0x0FFF;
        writeShort(ssInfo | 0xF000);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(~str[i]);
        writeShort(0);  // Terminator
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


// hsFileStream //
hsFileStream::hsFileStream(PlasmaVer pv) : F(NULL) { }

hsFileStream::~hsFileStream() {
    close();
}

bool hsFileStream::FileExists(const char* file) {
    FILE* eFile = fopen(file, "rb");
    bool exist = (eFile != NULL);
    if (exist)
        fclose(eFile);
    return exist;
}

bool hsFileStream::open(const char* file, FileMode mode) {
    const char* fms;
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
    } else if (fm == fmRead || fm == fmReadWrite) {
        throw hsFileReadException(__FILE__, __LINE__, "File does not exist");
    }
    return false;
}

void hsFileStream::close() {
    if (F) fclose(F);
    F = NULL;
}

hsUint32 hsFileStream::size() const {
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

hsUint32 hsFileStream::pos() const {
    return ftell(F);
}

bool hsFileStream::eof() const {
    int c = fgetc(F);
    ungetc(c, F);
    return (c == EOF);
}

void hsFileStream::seek(hsUint32 pos) {
    fseek(F, pos, SEEK_SET);
}

void hsFileStream::skip(hsInt32 count) {
    fseek(F, count, SEEK_CUR);
}

void hsFileStream::fastForward() {
    fseek(F, 0, SEEK_SET);
}

void hsFileStream::rewind() {
    fseek(F, 0, SEEK_END);
}

void hsFileStream::read(size_t size, void* buf) {
    if (fm == fmWrite)
        throw hsFileReadException(__FILE__, __LINE__);
    fread(buf, size, 1, F);
}

void hsFileStream::write(size_t size, const void* buf) {
    if (fm == fmRead)
        throw hsFileWriteException(__FILE__, __LINE__);
    fwrite(buf, size, 1, F);
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
