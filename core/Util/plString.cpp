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
#include "Debug/hsExceptions.h"
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
plString::StrBuffer::StrBuffer(char* str, size_t len)
        : fStr(str), fLen(len), fRefs(1) { }

plString::StrBuffer::~StrBuffer() {
    delete[] fStr;
}

void plString::StrBuffer::unref() {
    if (--fRefs == 0)
        delete this;
}


/* WideBuffer */
plString::WideBuffer::WideBuffer(pl_wchar_t* str, size_t len)
        : fStr(str), fLen(len), fRefs(1) { }

plString::WideBuffer::~WideBuffer() {
    delete[] fStr;
}

void plString::WideBuffer::unref() {
    if (--fRefs == 0)
        delete this;
}

const pl_wchar_t* plString::Wide::getNullStringBecauseVisualStudioIsStupid() {
    static pl_wchar_t _nullstr[] = { 0 };
    return _nullstr;
}

plString::Wide::Wide(WideBuffer* init) : fString(init) { }

plString::Wide::Wide(const Wide& init) : fString(init.fString) {
    if (fString != NULL)
        fString->ref();
}

plString::Wide::~Wide() {
    if (fString != NULL)
        fString->unref();
}

plString::Wide& plString::Wide::operator=(const Wide& other) {
    if (other.fString != NULL)
        other.fString->ref();
    if (fString != NULL)
        fString->unref();
    fString = other.fString;
    return *this;
}


/* plString */
plString::plString() : fString(NULL) { }

plString::plString(const plString& init) : fString(init.fString) {
    if (fString != NULL)
        fString->ref();
}

plString::plString(const char* init, size_t len) : fString(NULL) {
    if (init != NULL) {
        if (len == (size_t)-1)
            len = strlen(init);
        if (len != 0) {
            char* buf = new char[len+1];
            memcpy(buf, init, len);
            buf[len] = 0;
            fString = new StrBuffer(buf, len);
        }
    }
}

plString::plString(const pl_wchar_t* init, size_t len) : fString(NULL) {
    if (init != NULL) {
        if (len == (size_t)-1)
            len = plwcslen(init);
        if (len > 0) {
            size_t chlen = utf8len(init, len);
            char* buf = new char[chlen+1];
            utf8encode(buf, chlen, init, len);
            buf[chlen] = 0;
            fString = new StrBuffer(buf, chlen);
        }
    }
}

plString::~plString() {
    if (fString != NULL)
        fString->unref();
}

plString& plString::operator=(const plString& other) {
    if (other.fString != NULL)
        other.fString->ref();
    if (fString != NULL)
        fString->unref();
    fString = other.fString;
    return (*this);
}

plString& plString::operator=(const char* str) {
    if (fString != NULL)
        fString->unref();
    if (str != NULL) {
        size_t len = strlen(str);
        if (len > 0) {
            char* buf = new char[len+1];
            strncpy(buf, str, len);
            buf[len] = 0;
            fString = new StrBuffer(buf, len);
        } else {
            fString = NULL;
        }
    } else {
        fString = NULL;
    }
    return (*this);
}

plString& plString::operator=(const pl_wchar_t* str) {
    if (fString != NULL)
        fString->unref();
    if (str != NULL) {
        size_t len = plwcslen(str);
        if (len > 0) {
            size_t chlen = utf8len(str, len);
            char* buf = new char[chlen+1];
            utf8encode(buf, chlen, str, len);
            buf[chlen] = 0;
            fString = new StrBuffer(buf, chlen);
        } else {
            fString = NULL;
        }
    } else {
        fString = NULL;
    }
    return (*this);
}

plString& plString::operator+=(const plString& other) {
    if (other.empty())
        return (*this);
    if (empty())
        return operator=(other);

    size_t catlen = fString->len() + other.fString->len();
    char* buf = new char[catlen + 1];
    memcpy(buf, fString->data(), fString->len());
    memcpy(buf + fString->len(), other.fString->data(), other.fString->len());
    buf[catlen] = 0;
    fString->unref();
    fString = new StrBuffer(buf, catlen);
    return (*this);
}

plString& plString::operator+=(const char* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t slen = strlen(str);
    size_t catlen = fString->len() + slen;
    char* buf = new char[catlen + 1];
    memcpy(buf, fString->data(), fString->len());
    memcpy(buf + fString->len(), str, slen);
    buf[catlen] = 0;
    fString->unref();
    fString = new StrBuffer(buf, catlen);
    return (*this);
}

plString& plString::operator+=(const pl_wchar_t* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t wlen = plwcslen(str);
    size_t slen = utf8len(str, wlen);
    size_t catlen = fString->len() + slen;
    char* buf = new char[catlen + 1];
    memcpy(buf, fString->data(), fString->len());
    utf8encode(buf + fString->len(), slen, str, wlen);
    buf[catlen] = 0;
    fString->unref();
    fString = new StrBuffer(buf, catlen);
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
    return (strcmp(fString->data(), other.fString->data()) == 0);
}

bool plString::operator==(const char* str) const {
    if (str == NULL)
        return empty();
    if (empty())
        return false;
    return (strcmp(fString->data(), str) == 0);
}

bool plString::operator<(const plString& other) const {
    if (other.empty())
        return false;
    if (empty())
        return true;
    return (strcmp(fString->data(), other.fString->data()) < 0);
}

int plString::compareTo(const plString& other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(fString->data(), other.fString->data());
    } else {
        return strcmp(fString->data(), other.fString->data());
    }
}

int plString::compareTo(const char* other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(fString->data(), other);
    } else {
        return strcmp(fString->data(), other);
    }
}

bool plString::startsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty())
        return true;
    if (empty())
        return false;
    if (fString->len() < cmp.fString->len())
        return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::startsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL)
        return true;
    if (empty())
        return false;
    if (fString->len() < strlen(cmp))
        return false;
    return (left(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty())
        return true;
    if (empty())
        return false;
    if (fString->len() < cmp.fString->len())
        return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL)
        return true;
    if (empty())
        return false;
    if (fString->len() < strlen(cmp))
        return false;
    return (right(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

plString::Wide plString::wstr() const {
    if (empty())
        return Wide(NULL);
    size_t wlen = ucs2len(fString->data(), fString->len());
    pl_wchar_t* buf = new pl_wchar_t[wlen+1];
    utf8decode(buf, wlen, fString->data(), fString->len());
    buf[wlen] = 0;
    return Wide(new WideBuffer(buf, wlen));
}

unsigned int plString::hash() const {
    if (fString != NULL)
        return hash(fString->data());
    return hash(NULL);
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
    const char* pos = strchr(fString->data(), c);
    if (pos != NULL)
        return (long)(pos - fString->data());
    return -1;
}

long plString::find(const char* sub) const {
    if (empty())
        return -1;
    if (sub == NULL)
        return 0;
    size_t len = strlen(sub);
    if (len > fString->len())
        return -1;
    for (size_t i=0; i<(fString->len() - len); i++) {
        if (strncmp(fString->data() + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plString::find(const plString& sub) const {
    if (empty())
        return -1;
    if (sub.empty())
        return 0;
    if (sub.fString->len() > fString->len())
        return -1;
    for (size_t i=0; i<(fString->len() - sub.fString->len()); i++) {
        if (strncmp(fString->data() + i, sub.fString->data(), sub.fString->len()) == 0)
            return (long)i;
    }
    return -1;
}

long plString::rfind(char c) const {
    if (empty())
        return -1;
    const char* pos = strrchr(fString->data(), c);
    if (pos != NULL)
        return (long)(pos - fString->data());
    return -1;
}

long plString::rfind(const char* sub) const {
    if (empty())
        return -1;
    if (sub == NULL)
        return 0;
    size_t len = strlen(sub);
    if (len > fString->len())
        return -1;
    for (size_t i=(fString->len() - len); i>0; i--) {
        if (strncmp(fString->data() + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plString::rfind(const plString& sub) const {
    if (empty())
        return -1;
    if (sub.empty())
        return 0;
    if (sub.fString->len() > fString->len())
        return -1;
    for (size_t i=(fString->len() - sub.fString->len()); i>0; i--) {
        if (strncmp(fString->data() + (i-1), sub.fString->data(), sub.fString->len()) == 0)
            return (long)(i-1);
    }
    return -1;
}

plString plString::toUpper() const {
    if (!empty()) {
        char* buf = new char[fString->len() + 1];
        memcpy(buf, fString->data(), fString->len());
        for (size_t i=0; i<fString->len(); i++)
            buf[i] = toupper(buf[i]);
        buf[fString->len()] = 0;

        plString result;
        result.fString = new StrBuffer(buf, fString->len());
        return result;
    }
    return *this;
}

plString plString::toLower() const {
    if (!empty()) {
        char* buf = new char[fString->len() + 1];
        memcpy(buf, fString->data(), fString->len());
        for (size_t i=0; i<fString->len(); i++)
            buf[i] = tolower(buf[i]);
        buf[fString->len()] = 0;

        plString result;
        result.fString = new StrBuffer(buf, fString->len());
        return result;
    }
    return *this;
}

plString plString::left(size_t num) const {
    if (empty())
        return plString();
    if (num >= fString->len())
        return *this;

    plString retn;
    char* buf = new char[num+1];
    memcpy(buf, fString->data(), num);
    buf[num] = 0;
    retn.fString = new StrBuffer(buf, num);
    return retn;
}

plString plString::right(size_t num) const {
    if (empty())
        return plString();
    if (num >= fString->len())
        return *this;

    plString retn;
    char* buf = new char[num+1];
    memcpy(buf, fString->data() + (fString->len() - num), num);
    buf[num] = 0;
    retn.fString = new StrBuffer(buf, num);
    return retn;
}

plString plString::mid(size_t idx, size_t num) const {
    if (empty())
        return plString();
    if (idx > fString->len())
        return plString();
    if (idx + num > fString->len())
        num = fString->len() - idx;

    plString retn;
    char* buf = new char[num+1];
    memcpy(buf, fString->data() + idx, num);
    buf[num] = 0;
    retn.fString = new StrBuffer(buf, num);
    return retn;
}

plString plString::mid(size_t idx) const {
    if (fString == NULL)
        return plString();
    return mid(idx, fString->len() - idx);
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
    if (len > fString->len())
        return *this;

    plString result;
    size_t begin = 0;
    size_t i = 0;
    while (i < (fString->len() - len)) {
        if (strncmp(fString->data() + i, src, len) == 0) {
            result += plString(fString->data() + begin, i - begin);
            result += dest;
            i += len;
            begin = i;
        } else {
            i++;
        }
    }
    return result + plString(fString->data() + begin, (i + 1) - begin);
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
    const char* cpL = fString->data();
    const char* cpR = fString->data() + fString->len() - 1;
    while ((cpL <= cpR) && (*cpL == ' ' || *cpL == '\r' || *cpL == '\n' || *cpL == '\t'))
        cpL++;
    while ((cpR > cpL) && (*cpR == ' ' || *cpR == '\r' || *cpR == '\n' || *cpR == '\t'))
        cpR--;
    return plString(cpL, (cpR - cpL) + 1);
}

plString& plString::pack() {
    if (empty())
        return *this;
    return operator=(plString(fString->data()));
}

long plString::toInt(int base) const {
    if (empty())
        return 0;
    errno = 0;
    long value = strtol(fString->data(), NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid conversion to int");
    return value;
}

unsigned long plString::toUint(int base) const {
    if (empty())
        return 0;
    errno = 0;
    unsigned long value = strtoul(fString->data(), NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid conversion to uint");
    return value;
}

double plString::toFloat() const {
    if (empty())
        return 0.0;
    errno = 0;
    double value = strtod(fString->data(), NULL);
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
    va_list aptr_save;
#ifdef WIN32
    aptr_save = aptr;
#else
    va_copy(aptr_save, aptr);
#endif
    int chars = vsnprintf(buf, 256, fmt, aptr);
    if (chars < 0) {
        // Old glibc and Micro$oft make this harder than it needs to be
        int size = 4096;
        for ( ;; ) {
#ifdef WIN32
            aptr = aptr_save;
#else
            va_copy(aptr, aptr_save);
#endif
            char* bigbuf = new char[size];
            chars = vsnprintf(bigbuf, size, fmt, aptr);
            if (chars >= 0) {
                plString strfmt(bigbuf);
                delete[] bigbuf;
                return strfmt;
            }
            size *= 2;
        }
    } else if (chars >= 256) {
#ifdef WIN32
        aptr = aptr_save;
#else
        va_copy(aptr, aptr_save);
#endif
        char* bigbuf = new char[chars+1];
        vsnprintf(bigbuf, chars+1, fmt, aptr);
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
