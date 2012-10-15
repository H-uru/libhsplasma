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

#ifndef _PLSTRING_H
#define _PLSTRING_H

#include "PlasmaDefs.h"
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <vector>

#define SSO_CHARS (16)

typedef unsigned short pl_wchar_t;

class PLASMA_DLL plString {
public:
    class PLASMA_DLL StrBuffer {
    private:
        char* fStr;
        unsigned int fRefs;

    public:
        StrBuffer(char* str) : fStr(str), fRefs(1) { }
        ~StrBuffer();
        void ref() { fRefs++; }
        void unref();

        const char* data() const { return fStr; }
    };

    class PLASMA_DLL WideBuffer {
    private:
        pl_wchar_t* fStr;
        unsigned int fRefs;

    public:
        WideBuffer(pl_wchar_t* str) : fStr(str), fRefs(1) { }
        ~WideBuffer();
        void ref() { fRefs++; }
        void unref();

        const pl_wchar_t* data() const { return fStr; }
    };

    class PLASMA_DLL Wide {
    private:
        size_t fLen;
        union {
            WideBuffer* fString;
            pl_wchar_t fShort[SSO_CHARS];
        };

        bool haveACow() const { return fLen >= SSO_CHARS; }

    public:
        Wide(const Wide& init);
        ~Wide();
        Wide& operator=(const Wide& other);

        bool empty() const { return (fLen == 0); }
        size_t len() const { return fLen; }
        const pl_wchar_t* data() const { return (fLen < SSO_CHARS) ? fShort : fString->data(); }
        operator const pl_wchar_t*() const { return data(); }

    private:
        friend class plString;
        explicit Wide();
    };

private:
    size_t fLen;
    union {
        StrBuffer* fString;
        char fShort[SSO_CHARS];
    };

    bool haveACow() const { return fLen >= SSO_CHARS; }

public:
    plString();
    plString(const plString& init);
    plString(const char* init, size_t len = (size_t)-1);
    plString(const pl_wchar_t* init, size_t len = (size_t)-1);
    ~plString();

    bool empty() const { return (fLen == 0); }
    size_t len() const { return fLen; }

    plString& operator=(const plString& other);
    plString& operator=(const char* str);
    plString& operator=(const pl_wchar_t* str);
    plString& operator+=(const plString& other);
    plString& operator+=(const char* str);
    plString& operator+=(const pl_wchar_t* str);
    plString operator+(const plString& other) const;
    plString operator+(const char* str) const;
    plString operator+(const pl_wchar_t* str) const;
    bool operator==(const plString& other) const;
    bool operator==(const char* str) const;
    bool operator!=(const plString& other) const { return !operator==(other); }
    bool operator!=(const char* str) const { return !operator==(str); }
    bool operator<(const plString& other) const;

    int compareTo(const plString& other, bool ignoreCase = false) const;
    int compareTo(const char* other, bool ignoreCase = false) const;
    bool startsWith(const plString& cmp, bool ignoreCase = false) const;
    bool startsWith(const char* cmp, bool ignoreCase = false) const;
    bool endsWith(const plString& cmp, bool ignoreCase = false) const;
    bool endsWith(const char* cmp, bool ignoreCase = false) const;

    const char* cstr() const { return (fLen < SSO_CHARS) ? fShort : fString->data(); }
    operator const char*() const { return cstr(); }
    Wide wstr() const;

    unsigned int hash() const { return hash(cstr()); }
    static unsigned int hash(const char* str);

    long find(char c) const;
    long find(const char* sub) const;
    long find(const plString& sub) const;
    long rfind(char c) const;
    long rfind(const char* sub) const;
    long rfind(const plString& sub) const;

    plString toUpper() const;
    plString toLower() const;
    plString left(size_t num) const;
    plString right(size_t num) const;
    plString mid(size_t idx, size_t num) const;
    plString mid(size_t idx) const { return mid(idx, fLen - idx); }
    plString beforeFirst(char sep) const;
    plString afterFirst(char sep) const;
    plString beforeLast(char sep) const;
    plString afterLast(char sep) const;
    plString replace(const char* src, const char* dest) const;
    std::vector<plString> split(char sep, size_t max = (size_t)-1) const;
    plString trim() const;
    plString& pack();

    long toInt(int base = 0) const;
    unsigned long toUint(int base = 0) const;
    double toFloat() const;
    bool toBool() const;

    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

plString PLASMA_DLL CleanFileName(const char* fname, bool allowPathChars = false);
size_t PLASMA_DLL plwcslen(const pl_wchar_t* str);
pl_wchar_t PLASMA_DLL* plwcsdup(const pl_wchar_t* str);

#endif
