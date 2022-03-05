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
#include <string_theory/exceptions>
#include "hsStream.h"
#include "Sys/Platform.h"
#include "Debug/plDebug.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#endif

static const int eoaStrKey[8] = {'m','y','s','t','n','e','r','d'};

/* hsStream */
#define BLOCKSIZE 4096
void hsStream::writeFrom(hsStream* src)
{
    unsigned char buf[BLOCKSIZE];
    for (size_t spos = 0; spos < (src->size() / BLOCKSIZE); spos++) {
        src->read(BLOCKSIZE, buf);
        write(BLOCKSIZE, buf);
    }
    size_t endsize = src->size() % BLOCKSIZE;
    src->read(endsize, buf);
    write(endsize, buf);
}

uint8_t hsStream::readByte()
{
    uint8_t v;
    read(sizeof(v), &v);
    return v;
}

uint16_t hsStream::readShort()
{
    uint16_t v;
    read(sizeof(v), &v);
    return LESWAP16(v);
}

void hsStream::readShorts(size_t count, uint16_t* buf)
{
    read(sizeof(uint16_t) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP16(buf[i]);
#endif
}

uint32_t hsStream::readInt()
{
    uint32_t v;
    read(sizeof(v), &v);
    return LESWAP32(v);
}

void hsStream::readInts(size_t count, uint32_t* buf)
{
    read(sizeof(uint32_t) * count, buf);
#ifdef WORDS_BIGENDIAN
    for (size_t i=0; i<count; i++)
        buf[i] = LESWAP32(buf[i]);
#endif
}

uint32_t hsStream::readIntSwap()
{
    uint32_t v;
    read(sizeof(v), &v);
    return BESWAP32(v);
}

float hsStream::readFloat()
{
    float v;
    read(sizeof(v), &v);
    return LESWAPF(v);
}

double hsStream::readDouble()
{
    double v;
    read(sizeof(v), &v);
    return LESWAPD(v);
}

bool hsStream::readBool()
{
    return readByte() != 0;
}

ST::string hsStream::readStr(size_t len)
{
    ST::char_buffer result;
    result.allocate(len);
    read(len * sizeof(char), result.data());

    try {
        return result;
    } catch (ST::unicode_error&) {
        fprintf(stderr, "WARNING: String \"%s\" contained invalid unicode characters.\n"
                "Treating as Latin-1 instead.  If you save this file, the string will be\n"
                "converted to UTF-8!\n", result.data());
        return ST::string::from_latin_1(result);
    }
}

ST::string hsStream::readSafeStr()
{
    uint16_t ssInfo = readShort();
    if (ssInfo == 0) {
        if (ver < MAKE_VERSION(2, 0, 63, 5) && readShort() != 0) {
            skip(-2);
        }
        return ST::string();
    }

    ST::char_buffer result;
    if (ver.isUniversal()) {
        result.allocate(ssInfo);
        read(ssInfo, result.data());
    } else if (ver.isNewPlasma()) {
        result.allocate(ssInfo);
        read(ssInfo, result.data());
        for (size_t i=0; i<ssInfo; i++)
            result[i] ^= eoaStrKey[i%8];
    } else {
        if (!(ssInfo & 0xF000))
            readShort(); // Discarded
        uint16_t size = (ssInfo & 0x0FFF);
        result.allocate(size);
        read(size, result.data());
        if ((size > 0) && (result.front() & 0x80)) {
            for (size_t i=0; i<size; i++)
                result[i] = ~result[i];
        }
    }

    try {
        return result;
    } catch (ST::unicode_error&) {
        fprintf(stderr, "WARNING: String \"%s\" contained invalid unicode characters.\n"
                "Treating as Latin-1 instead.  If you save this file, the string will be \n"
                "converted to UTF-8!\n", result.data());
        return ST::string::from_latin_1(result);
    }
}

ST::string hsStream::readSafeWStr()
{
    uint16_t ssInfo = readShort();
    ST::utf16_buffer result;
    if (ver.isUniversal()) {
        result.allocate(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            result[i] = readShort();
        readShort();    // Terminator
    } else if (ver.isNewPlasma()) {
        result.allocate(ssInfo);
        for (size_t i=0; i<ssInfo; i++)
            result[i] = readShort() ^ eoaStrKey[i%8];
        readShort();    // Terminator
    } else {
        uint16_t size = (ssInfo & 0x0FFF);
        result.allocate(size);
        for (size_t i=0; i<size; i++)
            result[i] = ~readShort();
        readShort();    // Terminator
    }
    return result;
}

ST::string hsStream::readLine()
{
    ST::string_stream line;
    char c = readByte();
    while ((c != '\n') && (c != '\r') && !eof()) {
        line.append_char(c);
        c = readByte();
    }
    if (c != '\n' && c != '\r')
        line.append_char(c);
    if (c == '\r') {
        if (!eof()) {
            // Eat the \n in Windows-style EOLs
            char nextChar = readByte();
            if (nextChar != '\n') {
                // Old-school MacOS carriage return without line feed...
                // Rewind one character.
                skip(-1);
            }
        }
    }
    return line.to_string();
}

void hsStream::writeByte(uint8_t v)
{
    write(sizeof(v), &v);
}

void hsStream::writeShort(uint16_t v)
{
    v = LESWAP16(v);
    write(sizeof(v), &v);
}

void hsStream::writeShorts(size_t count, const uint16_t* buf)
{
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

void hsStream::writeInt(uint32_t v)
{
    v = LESWAP32(v);
    write(sizeof(v), &v);
}

void hsStream::writeInts(size_t count, const uint32_t* buf)
{
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

void hsStream::writeIntSwap(uint32_t v)
{
    v = BESWAP32(v);
    write(sizeof(v), &v);
}

void hsStream::writeFloat(float v)
{
    v = LESWAPF(v);
    write(sizeof(v), &v);
}

void hsStream::writeDouble(double v)
{
    v = LESWAPD(v);
    write(sizeof(v), &v);
}

void hsStream::writeBool(bool v)
{
    char b = v ? 1 : 0;
    write(sizeof(b), &b);
}

void hsStream::writeStr(const ST::string& str)
{
    write(str.size(), str.c_str());
}

void hsStream::writeSafeStr(const ST::string& str)
{
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

void hsStream::writeSafeWStr(const ST::string& str)
{
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
            writeShort(buf[i] ^ eoaStrKey[i%8]);
        writeShort(0);  // Terminator
    } else {
        ssInfo &= 0x0FFF;
        writeShort(ssInfo | 0xF000);
        for (size_t i=0; i<ssInfo; i++)
            writeShort(~buf.data()[i]);
        writeShort(0);  // Terminator
    }
}

void hsStream::writeLine(const ST::string& ln, bool winEOL)
{
    writeStr(ln);
    if (winEOL)
        writeByte('\r');
    writeByte('\n');
}


/* hsFileStream */
bool hsFileStream::FileExists(const ST::string& file)
{
#ifdef _WIN32
    HANDLE eFile = CreateFileW(file.to_wchar().data(), GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (eFile == INVALID_HANDLE_VALUE)
        return false;
    CloseHandle(eFile);
    return true;
#else
    FILE* eFile = fopen(file.c_str(), "rb");
    bool exist = (eFile != nullptr);
    if (exist)
        fclose(eFile);
    return exist;
#endif
}

bool hsFileStream::open(const ST::string& file, FileMode mode)
{
#ifdef _WIN32
    DWORD access, disposition;
    switch (mode) {
    case FileMode::fmRead:
        access = GENERIC_READ;
        disposition = OPEN_EXISTING;
        break;
    case FileMode::fmWrite:
        access = GENERIC_WRITE;
        disposition = OPEN_ALWAYS;
        break;
    case FileMode::fmCreate:
        access = GENERIC_READ | GENERIC_WRITE;
        disposition = CREATE_ALWAYS;
        break;
    case FileMode::fmReadWrite:
        access = GENERIC_READ | GENERIC_WRITE;
        disposition = OPEN_EXISTING;
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Invalid mode");
    }

    F = CreateFileW(file.to_wchar().data(), access, FILE_SHARE_READ, nullptr,
        disposition, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (F == INVALID_HANDLE_VALUE) {
        F = nullptr;
        if (mode == fmRead || mode == fmReadWrite)
            throw hsFileReadException(__FILE__, __LINE__, "File does not exist");
        return false;
    }

    fm = mode;
    return true;
#else
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
    if (F) {
        fm = mode;
        return true;
    } else if (mode == fmRead || mode == fmReadWrite) {
        throw hsFileReadException(__FILE__, __LINE__, "File does not exist");
    }
#endif
    return false;
}

void hsFileStream::close()
{
    if (F) {
#ifdef _WIN32
        CloseHandle(F);
#else
        fclose(F);
#endif
    }
    F = nullptr;
}

uint32_t hsFileStream::size() const
{
    if (F == nullptr)
        return 0;

#ifdef _WIN32
    auto sz = static_cast<uint32_t>(GetFileSize(F, nullptr));
#else
    unsigned int p = ftell(F);
    fseek(F, 0, SEEK_END);
    unsigned int sz = ftell(F);
    fseek(F, p, SEEK_SET);
#endif
    return sz;
}

uint32_t hsFileStream::pos() const
{
    if (F == nullptr)
        return 0;
#ifdef _WIN32
    return SetFilePointer(F, 0, nullptr, FILE_CURRENT);
#else
    return ftell(F);
#endif
}

bool hsFileStream::eof() const
{
    if (F == nullptr)
        return true;

#ifdef _WIN32
    uint8_t buf;
    DWORD nread = 0;
    BOOL result = ReadFile(F, &buf, 1, &nread, nullptr);
    if (result == TRUE && nread == 0)
        return true;
    SetFilePointer(F, -1, nullptr, FILE_CURRENT);
    return false;
#else
    int c = fgetc(F);
    ungetc(c, F);
    return (c == EOF);
#endif
}

void hsFileStream::seek(uint32_t pos)
{
    if (F == nullptr)
        return;
#ifdef _WIN32
    SetFilePointer(F, pos, nullptr, FILE_BEGIN);
#else
    fseek(F, pos, SEEK_SET);
#endif
}

void hsFileStream::skip(int32_t count)
{
    if (F == nullptr)
        return;
#ifdef _WIN32
    SetFilePointer(F, count, nullptr, FILE_CURRENT);
#else
    fseek(F, count, SEEK_CUR);
#endif
}

void hsFileStream::fastForward()
{
    if (F == nullptr)
        return;
#ifdef _WIN32
    SetFilePointer(F, 0, nullptr, FILE_END);
#else
    fseek(F, 0, SEEK_END);
#endif
}

void hsFileStream::rewind()
{
    if (F == nullptr)
        return;
#ifdef _WIN32
    SetFilePointer(F, 0, nullptr, FILE_BEGIN);
#else
    fseek(F, 0, SEEK_SET);
#endif
}

void hsFileStream::flush()
{
    if (F == nullptr)
        return;
#ifdef _WIN32
    FlushFileBuffers(F);
#else
    fflush(F);
#endif
}

size_t hsFileStream::read(size_t size, void* buf)
{
    if (F == nullptr || fm == fmWrite || fm == fmCreate)
        throw hsFileReadException(__FILE__, __LINE__);
#ifdef _WIN32
    DWORD nread = 0;
    ReadFile(F, buf, size, &nread, nullptr);
#else
    size_t nread = fread(buf, 1, size, F);
#endif
    if (nread != size) {
        throw hsFileReadException(__FILE__, __LINE__,
                         ST::format("Read past end of file: {} bytes requested, {} available",
                         size, nread).c_str());
    }
    return nread;
}

size_t hsFileStream::write(size_t size, const void* buf)
{
    if (F == nullptr || fm == fmRead)
        throw hsFileWriteException(__FILE__, __LINE__);
#ifdef _WIN32
    DWORD nwrite = 0;
    WriteFile(F, buf, size, &nwrite, nullptr);
    return nwrite;
#else
    return fwrite(buf, 1, size, F);
#endif
}

time_t hsFileStream::getModTime() const
{
    if (F == nullptr)
        return 0;

#ifdef _WIN32
    FILETIME modTime;
    GetFileTime(F, nullptr, nullptr, &modTime);
    return ((time_t)modTime.dwHighDateTime << 32) | modTime.dwLowDateTime;
#else
    struct stat stbuf;
    fstat(fileno(F), &stbuf);
    return stbuf.st_mtime;
#endif
}
