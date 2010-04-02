#include <string.h>
#include <sys/stat.h>
#include "hsStream.h"
#include "Sys/Platform.h"

static const char eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};
static const wchar_t eoaWStrKey[8] = {L'm',L'y',L's',L't',L'n',L'e',L'r',L'd'};

/* hsStream */
hsStream::hsStream(PlasmaVer pv) {
    setVer(pv);
}

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

hsUint16 hsStream::readShort() {
    hsUint16 v;
    read(sizeof(v), &v);
    return LESWAP16(v);
}

void hsStream::readShorts(size_t count, hsUint16* buf) {
    read(sizeof(hsUint16) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP16(buf[i]);
#endif
}

hsUint32 hsStream::readInt() {
    hsUint32 v;
    read(sizeof(v), &v);
    return LESWAP32(v);
}

void hsStream::readInts(size_t count, hsUint32* buf) {
    read(sizeof(hsUint32) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP32(buf[i]);
#endif
}

hsUint32 hsStream::readIntSwap() {
    hsUint32 v;
    read(sizeof(v), &v);
    return BESWAP32(v);
}

float hsStream::readFloat() {
    float v;
    read(sizeof(v), &v);
    return LESWAPF(v);
}

double hsStream::readDouble() {
    double v;
    read(sizeof(v), &v);
    return LESWAPD(v);
}

bool hsStream::readBool() {
    return readByte() == 0 ? false : true;
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
    if (ver == pvUniversal) {
        buf = new char[ssInfo+1];
        read(ssInfo, buf);
        buf[ssInfo] = 0;
    } else if (ver >= pvEoa) {
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
        if ((size > 0) && (buf[0] & 0x80)) {
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
    if (ver == pvUniversal) {
        buf = new wchar_t[ssInfo+1];
        for (size_t i=0; i<ssInfo; i++)
            buf[i] = readShort() & 0xFFFF;
        readShort();    // Terminator
        buf[ssInfo] = 0;
    } else if (ver >= pvEoa) {
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
    while ((c != '\n') && (c != '\r') && !eof()) {
        buf[i++] = c;
        c = readByte();
        if (i >= 4096)
            throw hsFileReadException(__FILE__, __LINE__, "Line too long");
    }
    if (c != '\n' && c != '\r')
        buf[i++] = c;
    buf[i] = 0;
    if (c == '\r')
        readByte(); // Eat the \n in Windows-style EOLs
    plString str(buf);
    delete[] buf;
    return str;
}

void hsStream::writeByte(hsUbyte v) {
    write(sizeof(v), &v);
}

void hsStream::writeShort(hsUint16 v) {
    v = LESWAP16(v);
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const hsUint16* buf) {
#ifdef WORDS_BIGENDIAN
    hsUint16* swbuf = new hsUint16[count];
    for (size_t i=0; i<count; i++)
        swbuf[i] = LESWAP16(buf[i]);
    write(sizeof(hsUint16) * count, swbuf);
    delete[] swbuf;
#else
    write(sizeof(hsUint16) * count, buf);
#endif
}

void hsStream::writeInt(hsUint32 v) {
    v = LESWAP32(v);
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const hsUint32* buf) {
#ifdef WORDS_BIGENDIAN
    hsUint32* swbuf = new hsUint32[count];
    for (size_t i=0; i<count; i++)
        swbuf[i] = LESWAP32(buf[i]);
    write(sizeof(hsUint32) * count, swbuf);
    delete[] swbuf;
#else
    write(sizeof(hsUint32) * count, buf);
#endif
}

void hsStream::writeIntSwap(hsUint32 v) {
    v = BESWAP32(v);
    write(sizeof(v), &v);
}

void hsStream::writeFloat(float v) {
    v = LESWAPF(v);
    write(sizeof(v), &v);
}

void hsStream::writeDouble(double v) {
    v = LESWAPD(v);
    write(sizeof(v), &v);
}

void hsStream::writeBool(bool v) {
    char b = v ? 1 : 0;
    write(sizeof(b), &b);
}

void hsStream::writeStr(const plString& str) {
    write(str.len(), str.cstr());
}

void hsStream::writeSafeStr(const plString& str) {
    hsUint16 ssInfo = (hsUint16)str.len();
    char* wbuf;
    if (ver == pvUniversal) {
        writeShort(ssInfo);
        wbuf = new char[ssInfo];
        memcpy(wbuf, str.cstr(), ssInfo);
    } else if (ver >= pvEoa) {
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
    if (ver == pvUniversal) {
        writeShort(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(str[i]);
        writeShort(0);  // Terminator
    } else if (ver >= pvEoa) {
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


/* hsFileStream */
hsFileStream::hsFileStream(PlasmaVer pv) : hsStream(pv), F(NULL) { }

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
    if (F != NULL)
        fclose(F);
    F = NULL;
}

hsUint32 hsFileStream::size() const {
    if (F == NULL)
        return 0;
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

hsUint32 hsFileStream::pos() const {
    if (F == NULL)
        return 0;
    return ftell(F);
}

bool hsFileStream::eof() const {
    if (F == NULL)
        return true;
    int c = fgetc(F);
    ungetc(c, F);
    return (c == EOF);
}

void hsFileStream::seek(hsUint32 pos) {
    if (F == NULL)
        return;
    fseek(F, pos, SEEK_SET);
}

void hsFileStream::skip(hsInt32 count) {
    if (F == NULL)
        return;
    fseek(F, count, SEEK_CUR);
}

void hsFileStream::fastForward() {
    if (F == NULL)
        return;
    fseek(F, 0, SEEK_END);
}

void hsFileStream::rewind() {
    if (F == NULL)
        return;
    fseek(F, 0, SEEK_SET);
}

void hsFileStream::flush() {
    if (F == NULL)
        return;
    fflush(F);
}

size_t hsFileStream::read(size_t size, void* buf) {
    if (F == NULL || fm == fmWrite)
        throw hsFileReadException(__FILE__, __LINE__);
    return fread(buf, size, 1, F);
}

size_t hsFileStream::write(size_t size, const void* buf) {
    if (F == NULL || fm == fmRead)
        throw hsFileWriteException(__FILE__, __LINE__);
    return fwrite(buf, size, 1, F);
}

time_t hsFileStream::getModTime() const {
    if (F == NULL)
        return 0;

    struct stat stbuf;
    fstat(fileno(F), &stbuf);
    return stbuf.st_mtime;
}


/* hsFileReadException */
hsFileReadException::hsFileReadException(const char* file,
                     unsigned long line, const char* filename) throw()
                   : hsException(file, line) {
    fWhat = "Error reading file";
    if (filename != NULL)
        fWhat += plString(": ") + filename;
}


/* hsFileWriteException */
hsFileWriteException::hsFileWriteException(const char* file,
                      unsigned long line, const char* filename) throw()
                    : hsException(file, line) {
    fWhat = "Error writing to file";
    if (filename != NULL)
        fWhat += plString(": ") + filename;
}
