/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <sys/stat.h>
#include "hsStream.h"
#include "Sys/Platform.h"
#include "Debug/plDebug.h"

static const int eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};

/* hsStream */
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

uint8_t hsStream::readByte() {
    uint8_t v;
    read(sizeof(v), &v);
    return v;
}

uint16_t hsStream::readShort() {
    uint16_t v;
    read(sizeof(v), &v);
    return LESWAP16(v);
}

void hsStream::readShorts(size_t count, uint16_t* buf) {
    read(sizeof(uint16_t) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP16(buf[i]);
#endif
}

uint32_t hsStream::readInt() {
    uint32_t v;
    read(sizeof(v), &v);
    return LESWAP32(v);
}

void hsStream::readInts(size_t count, uint32_t* buf) {
    read(sizeof(uint32_t) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP32(buf[i]);
#endif
}

uint32_t hsStream::readIntSwap() {
    uint32_t v;
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
    return readByte() != 0;
}

ST::string hsStream::readStr(size_t len) {
    ST::char_buffer result;
    char* buf = result.create_writable_buffer(len);
    read(len * sizeof(char), buf);
    buf[len] = 0;
    return result;
}

ST::string hsStream::readSafeStr() {
    char* buf;
    uint16_t ssInfo = readShort();
    if (ssInfo == 0) {
        if (ver < MAKE_VERSION(2, 0, 63, 5) && readShort() != 0) {
            skip(-2);
        }
        return ST::string::null;
    }

    ST::char_buffer result;
    if (ver.isUniversal()) {
        buf = result.create_writable_buffer(ssInfo);
        read(ssInfo, buf);
        buf[ssInfo] = 0;
    } else if (ver.isNewPlasma()) {
        buf = result.create_writable_buffer(ssInfo);
        read(ssInfo, buf);
        for (size_t i=0; i<ssInfo; i++)
            buf[i] ^= eoaStrKey[i%8];
        buf[ssInfo] = 0;
    } else {
        if (!(ssInfo & 0xF000))
            readShort(); // Discarded
        uint16_t size = (ssInfo & 0x0FFF);
        buf = result.create_writable_buffer(size);
        read(size, buf);
        if ((size > 0) && (buf[0] & 0x80)) {
            for (size_t i=0; i<size; i++)
                buf[i] = ~buf[i];
        }
        buf[size] = 0;
    }
    return result;
}

ST::string hsStream::readSafeWStr() {
    uint16_t ssInfo = readShort();
    ST::utf16_buffer result;
    char16_t* buf;
    if (ver.isUniversal()) {
        buf = result.create_writable_buffer(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            buf[i] = readShort() & 0xFFFF;
        readShort();    // Terminator
        buf[ssInfo] = 0;
    } else if (ver.isNewPlasma()) {
        buf = result.create_writable_buffer(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            buf[i] = (readShort() ^ eoaStrKey[i%8]) & 0xFFFF;
        readShort();    // Terminator
        buf[ssInfo] = 0;
    } else {
        uint16_t size = (ssInfo & 0x0FFF);
        buf = result.create_writable_buffer(size);
        for (size_t i=0; i<size; i++)
            buf[i] = (~readShort()) & 0xFFFF;
        readShort();    // Terminator
        buf[size] = 0;
    }
    return result;
}

ST::string hsStream::readLine() {
    ST::string_stream line;
    char c = readByte();
    while ((c != '\n') && (c != '\r') && !eof()) {
        line.append_char(c);
        c = readByte();
    }
    if (c != '\n' && c != '\r')
        line.append_char(c);
    if (c == '\r')
        readByte(); // Eat the \n in Windows-style EOLs
    return line.to_string();
}

void hsStream::writeByte(uint8_t v) {
    write(sizeof(v), &v);
}

void hsStream::writeShort(uint16_t v) {
    v = LESWAP16(v);
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const uint16_t* buf) {
#ifdef WORDS_BIGENDIAN
    uint16_t* swbuf = new uint16_t[count];
    for (size_t i=0; i<count; i++)
        swbuf[i] = LESWAP16(buf[i]);
    write(sizeof(uint16_t) * count, swbuf);
    delete[] swbuf;
#else
    write(sizeof(uint16_t) * count, buf);
#endif
}

void hsStream::writeInt(uint32_t v) {
    v = LESWAP32(v);
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const uint32_t* buf) {
#ifdef WORDS_BIGENDIAN
    uint32_t* swbuf = new uint32_t[count];
    for (size_t i=0; i<count; i++)
        swbuf[i] = LESWAP32(buf[i]);
    write(sizeof(uint32_t) * count, swbuf);
    delete[] swbuf;
#else
    write(sizeof(uint32_t) * count, buf);
#endif
}

void hsStream::writeIntSwap(uint32_t v) {
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

void hsStream::writeStr(const ST::string& str) {
    write(str.size(), str.c_str());
}

void hsStream::writeSafeStr(const ST::string& str) {
    if (str.size() > 0xFFF)
        plDebug::Warning("SafeString length is excessively long");

    if (!ver.isSafeVer())
        ver = PlasmaVer::GetSafestVersion(ver);

    uint16_t ssInfo = (uint16_t)str.size();
    char* wbuf;
    if (ver.isUniversal()) {
        writeShort(ssInfo);
        wbuf = new char[ssInfo];
        memcpy(wbuf, str.c_str(), ssInfo);
    } else if (ver.isNewPlasma()) {
        writeShort(ssInfo);
        wbuf = new char[ssInfo];
        for (size_t i=0; i<ssInfo; i++)
            wbuf[i] = str.char_at(i) ^ eoaStrKey[i%8];
    } else {
        ssInfo &= 0x0FFF;
        writeShort(ssInfo | 0xF000);
        wbuf = new char[ssInfo];
        for (size_t i=0; i<ssInfo; i++)
            wbuf[i] = ~str.char_at(i);
    }
    write(ssInfo, wbuf);
    delete[] wbuf;
}

void hsStream::writeSafeWStr(const ST::string& str) {
    ST::utf16_buffer buf = str.to_utf16();
    if (buf.size() > 0xFFF)
        plDebug::Warning("SafeWString length is excessively long");

    uint16_t ssInfo = (uint16_t)buf.size();
    if (ver.isUniversal()) {
        writeShort(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(buf.data()[i]);
        writeShort(0);  // Terminator
    } else if (ver.isNewPlasma()) {
        writeShort(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(buf.data()[i] ^ eoaStrKey[i%8]);
        writeShort(0);  // Terminator
    } else {
        ssInfo &= 0x0FFF;
        writeShort(ssInfo | 0xF000);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(~buf.data()[i]);
        writeShort(0);  // Terminator
    }
}

void hsStream::writeLine(const ST::string& ln, bool winEOL) {
    writeStr(ln);
    if (winEOL)
        writeByte('\r');
    writeByte('\n');
}


/* hsFileStream */
bool hsFileStream::FileExists(const ST::string& file) {
    FILE* eFile = fopen(file.c_str(), "rb");
    bool exist = (eFile != NULL);
    if (exist)
        fclose(eFile);
    return exist;
}

bool hsFileStream::open(const ST::string& file, FileMode mode) {
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
        throw hsBadParamException(__FILE__, __LINE__, "Invalid mode");
    }

    F = fopen(file.c_str(), fms);
    if (F != NULL) {
        fm = mode;
        return true;
    } else if (mode == fmRead || mode == fmReadWrite) {
        throw hsFileReadException(__FILE__, __LINE__, "File does not exist");
    }
    return false;
}

void hsFileStream::close() {
    if (F != NULL)
        fclose(F);
    F = NULL;
}

uint32_t hsFileStream::size() const {
    if (F == NULL)
        return 0;
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
    return sz;
}

uint32_t hsFileStream::pos() const {
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

void hsFileStream::seek(uint32_t pos) {
    if (F == NULL)
        return;
    fseek(F, pos, SEEK_SET);
}

void hsFileStream::skip(int32_t count) {
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
    if (F == NULL || fm == fmWrite || fm == fmCreate)
        throw hsFileReadException(__FILE__, __LINE__);
    size_t nread = fread(buf, 1, size, F);
    if (nread != size) {
        throw hsFileReadException(__FILE__, __LINE__,
                         ST::format("Read past end of file: {} bytes requested, {} available",
                         size, nread).c_str());
    }
    return nread;
}

size_t hsFileStream::write(size_t size, const void* buf) {
    if (F == NULL || fm == fmRead)
        throw hsFileWriteException(__FILE__, __LINE__);
    return fwrite(buf, 1, size, F);
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
                     unsigned long line, const char* filename) HS_NOEXCEPT
                   : hsException(file, line) {
    fWhat = "Error reading file";
    if (filename != NULL)
        fWhat += ST::string(": ") + filename;
}


/* hsFileWriteException */
hsFileWriteException::hsFileWriteException(const char* file,
                      unsigned long line, const char* filename) HS_NOEXCEPT
                    : hsException(file, line) {
    fWhat = "Error writing to file";
    if (filename != NULL)
        fWhat += ST::string(": ") + filename;
}
