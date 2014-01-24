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

#include "plString.h"
#include "Sys/Platform.h"
#include "Debug/hsExceptions.hpp"
#include <ctype.h>
#include <cstdlib>
#include <cstdarg>
#include <cerrno>
#include <list>

/* Helper utils */
static size_t utf8len(const pl_wchar_t* str, size_t srclen) {
    if (str == NULL)
        return 0;

    size_t len = 0;
    const pl_wchar_t* end = str + srclen;
    while (str < end) {
        if (*str < 0x80) {
            len += 1;
        } else if (*str < 0x800) {
            len += 2;
        } else {
            len += 3;
        }
        str++;
    }
    return len;
}

static size_t ucs2len(const char* str, size_t srclen) {
    if (str == NULL)
        return 0;

    size_t len = 0;
    const char* end = str + srclen;
    while (str < end) {
        if ((*str & 0x80) == 0) {
            str += 1;
        } else if ((*str & 0xE0) == 0xC0) {
            if ((*(str+1) & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
            str += 2;
        } else if ((*str & 0xF0) == 0xE0) {
            if ((*(str+1) & 0xC0) != 0x80 || (*(str+2) & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
            str += 3;
        } else if ((*str & 0xF1) == 0xF0) {
            throw hsBadParamException(__FILE__, __LINE__, "Unicode character out of UCS-2 range");
        } else {
            throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 sequence");
        }
        len++;
    }
    return len;
}

static void utf8encode(char* dest, size_t length, const pl_wchar_t* src, size_t srclen) {
    unsigned int ch;
    char* end = dest + length;
    const pl_wchar_t* srcend = src + srclen;
    while (src < srcend) {
        if (*src < 0x80) {
            if (dest + 1 > end)
                break;
            *dest++ = *src++;
        } else if (*src < 0x800) {
            if (dest + 2 > end)
                break;
            ch = *src++;
            *dest++ = 0xC0 | ((ch >> 6) & 0x1F);
            *dest++ = 0x80 | ((ch     ) & 0x3F);
        } else {
            if (dest + 3 > end)
                break;
            ch = *src++;
            *dest++ = 0xE0 | ((ch >> 12) & 0x0F);
            *dest++ = 0x80 | ((ch >>  6) & 0x3F);
            *dest++ = 0x80 | ((ch      ) & 0x3F);
        }
    }
}

static void utf8decode(pl_wchar_t* dest, size_t length, const char* src, size_t srclen) {
    unsigned int ch;
    pl_wchar_t* end = dest + length;
    const char* srcend = src + srclen;
    while (src < srcend) {
        if ((*src & 0x80) == 0) {
            if (dest + 1 > end)
                break;
            *dest++ = *src++;
        } else if ((*src & 0xE0) == 0xC0) {
            if (dest + 1 > end)
                break;
            ch  = ((*src++ & 0x1F) << 6);
            ch |= ((*src++ & 0x3F)     );
            *dest++ = ch;
        } else if ((*src & 0xF0) == 0xE0) {
            if (dest + 1 > end)
                break;
            ch  = ((*src++ & 0x0F) << 12);
            ch |= ((*src++ & 0x3F) <<  6);
            ch |= ((*src++ & 0x3F)      );
            *dest++ = ch;
        }
    }
}


/* StrBuffer */
plString::StrBuffer::~StrBuffer() {
    delete[] fStr;
}

void plString::StrBuffer::unref() {
    if (--fRefs == 0)
        delete this;
}


/* WideBuffer */
plString::WideBuffer::~WideBuffer() {
    delete[] fStr;
}

void plString::WideBuffer::unref() {
    if (--fRefs == 0)
        delete this;
}

plString::Wide::Wide() : fLen(0) { memset(fShort, 0, sizeof(fShort)); }

plString::Wide::Wide(const Wide& init) : fLen(init.fLen) {
    memcpy(fShort, init.fShort, sizeof(fShort));
    if (haveACow())
        fString->ref();
}

plString::Wide::~Wide() {
    if (haveACow())
        fString->unref();
}

plString::Wide& plString::Wide::operator=(const Wide& other) {
    if (other.haveACow())
        other.fString->ref();
    if (haveACow())
        fString->unref();
    memcpy(fShort, other.fShort, sizeof(fShort));
    return *this;
}


/* plString */
plString::plString() : fLen(0) { memset(fShort, 0, SSO_CHARS); }

plString::plString(const plString& init) : fLen(init.fLen) {
    memcpy(fShort, init.fShort, SSO_CHARS);
    if (haveACow())
        fString->ref();
}

plString::plString(const char* init, size_t len) : fLen(0) {
    memset(fShort, 0, SSO_CHARS);
    if (init != NULL) {
        if (len == (size_t)-1)
            len = strlen(init);
        if (len != 0) {
            fLen = len;
            char* buf = haveACow() ? new char[fLen+1] : fShort;
            memcpy(buf, init, fLen);
            buf[fLen] = 0;
            if (haveACow())
                fString = new StrBuffer(buf);
        }
    }
}

plString::plString(const pl_wchar_t* init, size_t len) : fLen(0) {
    memset(fShort, 0, SSO_CHARS);
    if (init != NULL) {
        if (len == (size_t)-1)
            len = plwcslen(init);
        if (len > 0) {
            fLen = utf8len(init, len);
            char* buf = haveACow() ? new char[fLen+1] : fShort;
            utf8encode(buf, fLen, init, len);
            buf[fLen] = 0;
            if (haveACow())
                fString = new StrBuffer(buf);
        }
    }
}

plString::~plString() {
    if (haveACow())
        fString->unref();
}

plString& plString::operator=(const plString& other) {
    if (other.haveACow())
        other.fString->ref();
    if (haveACow())
        fString->unref();

    fLen = other.fLen;
    memcpy(fShort, other.fShort, SSO_CHARS);
    return (*this);
}

plString& plString::operator=(const char* str) {
    if (haveACow())
        fString->unref();
    memset(fShort, 0, SSO_CHARS);
    fLen = 0;

    if (str != NULL) {
        fLen = strlen(str);
        if (fLen > 0) {
            char* buf = haveACow() ? new char[fLen+1] : fShort;
            strncpy(buf, str, fLen);
            buf[fLen] = 0;
            if (haveACow())
                fString = new StrBuffer(buf);
        }
    }
    return (*this);
}

plString& plString::operator=(const pl_wchar_t* str) {
    if (haveACow())
        fString->unref();
    memset(fShort, 0, SSO_CHARS);
    fLen = 0;

    if (str != NULL) {
        size_t len = plwcslen(str);
        if (len > 0) {
            fLen = utf8len(str, len);
            char* buf = haveACow() ? new char[fLen+1] : fShort;
            utf8encode(buf, fLen, str, len);
            buf[fLen] = 0;
            if (haveACow())
                fString = new StrBuffer(buf);
        }
    }
    return (*this);
}

plString& plString::operator+=(const plString& other) {
    if (other.empty())
        return (*this);
    if (empty())
        return operator=(other);

    size_t catlen = fLen + other.fLen;
    if (catlen < SSO_CHARS) {
        // If catlen is less than SSO_CHARS, then both fLen and other.fLen
        // are also guaranteed shorter than SSO_CHARS
        memcpy(fShort + fLen, other.fShort, other.fLen);
        fShort[catlen] = 0;
    } else {
        char* buf = new char[catlen + 1];
        memcpy(buf, cstr(), fLen);
        memcpy(buf + fLen, other.cstr(), other.fLen);
        buf[catlen] = 0;
        if (haveACow())
            fString->unref();
        fString = new StrBuffer(buf);
    }
    fLen = catlen;
    return (*this);
}

plString& plString::operator+=(const char* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t slen = strlen(str);
    size_t catlen = fLen + slen;
    if (catlen < SSO_CHARS) {
        memcpy(fShort + fLen, str, slen);
        fShort[catlen] = 0;
    } else {
        char* buf = new char[catlen + 1];
        memcpy(buf, cstr(), fLen);
        memcpy(buf + fLen, str, slen);
        buf[catlen] = 0;
        if (haveACow())
            fString->unref();
        fString = new StrBuffer(buf);
    }
    fLen = catlen;
    return (*this);
}

plString& plString::operator+=(const pl_wchar_t* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t wlen = plwcslen(str);
    size_t slen = utf8len(str, wlen);
    size_t catlen = fLen + slen;
    if (catlen < SSO_CHARS) {
        utf8encode(fShort + fLen, slen, str, wlen);
        fShort[catlen] = 0;
    } else {
        char* buf = new char[catlen + 1];
        memcpy(buf, cstr(), fLen);
        utf8encode(buf + fLen, slen, str, wlen);
        buf[catlen] = 0;
        if (haveACow())
            fString->unref();
        fString = new StrBuffer(buf);
    }
    fLen = catlen;
    return (*this);
}

plString plString::operator+(const plString& other) const {
    plString result(*this);
    return (result += other);
}

plString plString::operator+(const char* str) const {
    plString result(*this);
    return (result += str);
}

plString plString::operator+(const pl_wchar_t* str) const {
    plString result(*this);
    return (result += str);
}

bool plString::operator==(const plString& other) const {
    if (other.empty())
        return empty();
    if (empty())
        return false;
    return (strcmp(cstr(), other.cstr()) == 0);
}

bool plString::operator==(const char* str) const {
    if (str == NULL)
        return empty();
    if (empty())
        return false;
    return (strcmp(cstr(), str) == 0);
}

bool plString::operator<(const plString& other) const {
    if (other.empty())
        return false;
    if (empty())
        return true;
    return (strcmp(cstr(), other.cstr()) < 0);
}

int plString::compareTo(const plString& other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(cstr(), other.cstr());
    } else {
        return strcmp(cstr(), other.cstr());
    }
}

int plString::compareTo(const char* other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(cstr(), other);
    } else {
        return strcmp(cstr(), other);
    }
}

bool plString::startsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty())
        return true;
    if (empty())
        return false;
    if (fLen < cmp.fLen)
        return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::startsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL)
        return true;
    if (empty())
        return false;
    if (fLen < strlen(cmp))
        return false;
    return (left(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty())
        return true;
    if (empty())
        return false;
    if (fLen < cmp.fLen)
        return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL)
        return true;
    if (empty())
        return false;
    if (fLen < strlen(cmp))
        return false;
    return (right(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

plString::Wide plString::wstr() const {
    if (empty())
        return Wide();

    Wide retn;
    retn.fLen = ucs2len(cstr(), fLen);
    if (retn.fLen < SSO_CHARS) {
        utf8decode(retn.fShort, retn.fLen, cstr(), fLen);
        retn.fShort[retn.fLen] = 0;
    } else {
        pl_wchar_t* buf = new pl_wchar_t[retn.fLen+1];
        utf8decode(buf, retn.fLen, cstr(), fLen);
        buf[retn.fLen] = 0;
        retn.fString = new WideBuffer(buf);
    }
    return retn;
}

unsigned int plString::hash(const char* str) {
    if (str == NULL)
        str = "";

    // djb2 hash
    unsigned int hash = 5381;
    while (*str++)
        hash = ((hash << 5) + hash) ^ *str;
    return hash;
}

long plString::find(char c) const {
    if (empty())
        return -1;
    const char* pos = strchr(cstr(), c);
    if (pos != NULL)
        return (long)(pos - cstr());
    return -1;
}

long plString::find(const char* sub) const {
    if (empty())
        return -1;
    if (sub == NULL)
        return 0;
    size_t len = strlen(sub);
    if (len > fLen)
        return -1;
    for (size_t i=0; i<(fLen - len); i++) {
        if (strncmp(cstr() + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plString::find(const plString& sub) const {
    if (empty())
        return -1;
    if (sub.empty())
        return 0;
    if (sub.fLen > fLen)
        return -1;
    for (size_t i=0; i<(fLen - sub.fLen); i++) {
        if (strncmp(cstr() + i, sub.cstr(), sub.fLen) == 0)
            return (long)i;
    }
    return -1;
}

long plString::rfind(char c) const {
    if (empty())
        return -1;
    const char* pos = strrchr(cstr(), c);
    if (pos != NULL)
        return (long)(pos - cstr());
    return -1;
}

long plString::rfind(const char* sub) const {
    if (empty())
        return -1;
    if (sub == NULL)
        return 0;
    size_t len = strlen(sub);
    if (len > fLen)
        return -1;
    for (size_t i=(fLen - len); i>0; i--) {
        if (strncmp(cstr() + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plString::rfind(const plString& sub) const {
    if (empty())
        return -1;
    if (sub.empty())
        return 0;
    if (sub.fLen > fLen)
        return -1;
    for (size_t i=(fLen - sub.fLen); i>0; i--) {
        if (strncmp(cstr() + (i-1), sub.cstr(), sub.fLen) == 0)
            return (long)(i-1);
    }
    return -1;
}

plString plString::toUpper() const {
    if (empty())
        return *this;

    plString result;
    if (fLen < SSO_CHARS) {
        for (size_t i=0; i<fLen; i++)
            result.fShort[i] = toupper(fShort[i]);
        result.fShort[fLen] = 0;
    } else {
        char* buf = new char[fLen + 1];
        const char* src = cstr();
        for (size_t i=0; i<fLen; i++)
            buf[i] = toupper(src[i]);
        buf[fLen] = 0;
        result.fString = new StrBuffer(buf);
    }
    result.fLen = fLen;
    return result;
}

plString plString::toLower() const {
    if (empty())
        return *this;

    plString result;
    if (fLen < SSO_CHARS) {
        for (size_t i=0; i<fLen; i++)
            result.fShort[i] = tolower(fShort[i]);
        result.fShort[fLen] = 0;
    } else {
        char* buf = new char[fLen + 1];
        const char* src = cstr();
        for (size_t i=0; i<fLen; i++)
            buf[i] = tolower(src[i]);
        buf[fLen] = 0;
        result.fString = new StrBuffer(buf);
    }
    result.fLen = fLen;
    return result;
}

plString plString::left(size_t num) const {
    if (empty())
        return plString();
    if (num >= fLen)
        return *this;

    plString retn;
    if (num < SSO_CHARS) {
        memcpy(retn.fShort, cstr(), num);
        retn.fShort[num] = 0;
    } else {
        char* buf = new char[num+1];
        memcpy(buf, cstr(), num);
        buf[num] = 0;
        retn.fString = new StrBuffer(buf);
    }
    retn.fLen = num;
    return retn;
}

plString plString::right(size_t num) const {
    if (empty())
        return plString();
    if (num >= fLen)
        return *this;

    plString retn;
    if (num < SSO_CHARS) {
        memcpy(retn.fShort, cstr() + (fLen - num), num);
        retn.fShort[num] = 0;
    } else {
        char* buf = new char[num+1];
        memcpy(buf, cstr() + (fLen - num), num);
        buf[num] = 0;
        retn.fString = new StrBuffer(buf);
    }
    retn.fLen = num;
    return retn;
}

plString plString::mid(size_t idx, size_t num) const {
    if (empty())
        return plString();
    if (idx > fLen)
        return plString();
    if (idx + num > fLen)
        num = fLen - idx;

    plString retn;
    if (num < SSO_CHARS) {
        memcpy(retn.fShort, cstr() + idx, num);
        retn.fShort[num] = 0;
    } else {
        char* buf = new char[num+1];
        memcpy(buf, cstr() + idx, num);
        buf[num] = 0;
        retn.fString = new StrBuffer(buf);
    }
    retn.fLen = num;
    return retn;
}

plString plString::beforeFirst(char sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return left(pos);
    else
        return *this;
}

plString plString::afterFirst(char sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return mid(pos+1);
    else
        return plString();
}

plString plString::beforeLast(char sep) const {
    long pos = rfind(sep);
    if (pos >= 0)
        return left(pos);
    else
        return plString();
}

plString plString::afterLast(char sep) const {
    long pos = rfind(sep);
    if (pos >= 0)
        return mid(pos+1);
    else
        return *this;
}

plString plString::replace(const char* src, const char* dest) const {
    if (empty() || src == NULL || dest == NULL)
        return *this;
    size_t len = strlen(src);
    if (len > fLen)
        return *this;

    plString result;
    const char* start = cstr();
    for ( ;; ) {
        const char* match = strstr(start, src);
        if (match == NULL)
            break;

        result += plString(start, match - start);
        result += dest;
        start = match + len;
    }

    if (*start != 0)
        result += start;
    return result;
}

std::vector<plString> plString::split(char sep, size_t max) const {
    std::list<plString> splits;

    plString cur = *this;
    while (max > 0) {
        long sp = cur.find(sep);
        if (sp >= 0) {
            splits.push_back(cur.left(sp));
            cur = cur.mid(sp+1);
            max--;
        } else {
            break;
        }
    }
    splits.push_back(cur);

    return std::vector<plString>(splits.begin(), splits.end());
}

plString plString::trim() const {
    if (empty())
        return *this;
    const char* cpL = cstr();
    const char* cpR = cstr() + fLen - 1;
    while ((cpL <= cpR) && (*cpL == ' ' || *cpL == '\r' || *cpL == '\n' || *cpL == '\t'))
        cpL++;
    while ((cpR > cpL) && (*cpR == ' ' || *cpR == '\r' || *cpR == '\n' || *cpR == '\t'))
        cpR--;
    return plString(cpL, (cpR - cpL) + 1);
}

plString& plString::pack() {
    if (empty())
        return *this;
    return operator=(plString(cstr()));
}

long plString::toInt(int base) const {
    if (empty())
        return 0;
    errno = 0;
    long value = strtol(cstr(), NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid conversion to int");
    return value;
}

unsigned long plString::toUint(int base) const {
    if (empty())
        return 0;
    errno = 0;
    unsigned long value = strtoul(cstr(), NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid conversion to uint");
    return value;
}

double plString::toFloat() const {
    if (empty())
        return 0.0;
    errno = 0;
    double value = strtod(cstr(), NULL);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid conversion to float");
    return value;
}

bool plString::toBool() const {
    if (compareTo("true", true) == 0)
        return true;
    if (compareTo("false", true) == 0)
        return false;
    return (toUint() != 0);
}

plString plString::Format(const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    plString str = FormatV(fmt, argptr);
    va_end(argptr);
    return str;
}

plString plString::FormatV(const char* fmt, va_list aptr) {
    char buf[256];
    int chars;

#ifdef _MSC_VER
    va_list aptr_save = aptr;
    chars = vsnprintf(buf, 256, fmt, aptr);
#else
    va_list aptr_copy;
    va_copy(aptr_copy, aptr);
    chars = vsnprintf(buf, 256, fmt, aptr_copy);
    va_end(aptr_copy);
#endif

    if (chars < 0) {
        // Old glibc and Micro$oft make this harder than it needs to be
        int size = 4096;
        for ( ;; ) {
            char* bigbuf = new char[size];
#ifdef _MSC_VER
            aptr = aptr_save;
            chars = vsnprintf(bigbuf, size, fmt, aptr);
#else
            va_copy(aptr_copy, aptr);
            chars = vsnprintf(bigbuf, size, fmt, aptr_copy);
            va_end(aptr_copy);
#endif
            if (chars >= 0) {
                plString strfmt(bigbuf);
                delete[] bigbuf;
                return strfmt;
            }
            size *= 2;
            delete[] bigbuf;
        }
    } else if (chars >= 256) {
        char* bigbuf = new char[chars+1];
#ifdef _MSC_VER
        aptr = aptr_save;
        vsnprintf(bigbuf, chars+1, fmt, aptr);
#else
        va_copy(aptr_copy, aptr);
        vsnprintf(bigbuf, chars+1, fmt, aptr_copy);
        va_end(aptr_copy);
#endif
        plString strfmt(bigbuf);
        delete[] bigbuf;
        return strfmt;
    }
    return plString(buf);
}


/* Other utilities */
plString CleanFileName(const char* fname, bool allowPathChars) {
    char* buf = strdup(fname);
    for (char* bp = buf; *bp; bp++) {
        if (*bp == '?' || *bp == '*' || *bp == '<' || *bp == '>' ||
            *bp == '"' || *bp == '|' || *bp < (char)0x20)
            *bp = '_';
        if (!allowPathChars && (*bp == '/' || *bp == '\\' || *bp == ':'))
            *bp = '_';
    }
    plString result(buf);
    free(buf);
    return result;
}

size_t plwcslen(const pl_wchar_t* str) {
    size_t len = 0;
    while (*str++ != 0)
        len++;
    return len;
}

pl_wchar_t* plwcsdup(const pl_wchar_t* str) {
    if (str == NULL)
        return NULL;

    size_t len = plwcslen(str);
    pl_wchar_t* buf = new pl_wchar_t[len+1];
    memcpy(buf, str, len * sizeof(pl_wchar_t));
    buf[len] = 0;
    return buf;
}
