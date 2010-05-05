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

typedef unsigned short pl_wchar_t;

DllClass plString {
public:
    DllClass StrBuffer {
    private:
        char* fStr;
        size_t fLen;
        unsigned int fRefs;

    public:
        StrBuffer(char* str, size_t len);
        ~StrBuffer();
        void ref() { fRefs++; }
        void unref();

        const char* data() const { return fStr; }
        size_t len() const { return fLen; }
    };

    DllClass WideBuffer {
    private:
        pl_wchar_t* fStr;
        size_t fLen;
        unsigned int fRefs;

    public:
        WideBuffer(pl_wchar_t* str, size_t len);
        ~WideBuffer();
        void ref() { fRefs++; }
        void unref();

        const pl_wchar_t* data() const { return fStr; }
        size_t len() const { return fLen; }
    };

    DllClass Wide {
    private:
        WideBuffer* fString;
        static const pl_wchar_t* getNullStringBecauseVisualStudioIsStupid();

    public:
        explicit Wide(WideBuffer* init);
        Wide(const Wide& init);
        ~Wide();
        Wide& operator=(const Wide& other);

        bool empty() const { return (fString == NULL) || (fString->len() == 0); }
        bool null() const { return (fString == NULL); }
        size_t len() const { return (fString != NULL) ? fString->len() : 0; }
        const pl_wchar_t* data() const { return (fString != NULL) ? fString->data()
                                         : getNullStringBecauseVisualStudioIsStupid(); }
        operator const pl_wchar_t*() const { return data(); }
    };

private:
    StrBuffer* fString;

public:
    plString();
    plString(const plString& init);
    plString(const char* init, size_t len = (size_t)-1);
    plString(const pl_wchar_t* init, size_t len = (size_t)-1);
    ~plString();

    bool empty() const { return (fString == NULL) || (fString->len() == 0); }
    bool null() const { return (fString == NULL); }
    size_t len() const { return (fString != NULL) ? fString->len() : 0; }

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

    const char* cstr() const { return (fString != NULL) ? fString->data() : ""; }
    operator const char*() const { return cstr(); }
    Wide wstr() const;

    unsigned int hash() const;
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
    plString mid(size_t idx) const;
    plString beforeFirst(char sep) const;
    plString afterFirst(char sep) const;
    plString beforeLast(char sep) const;
    plString afterLast(char sep) const;
    plString replace(const char* src, const char* dest) const;
    std::vector<plString> split(char sep, size_t max = (size_t)-1) const;
    plString trim() const;

    long toInt(int base = 0) const;
    unsigned long toUint(int base = 0) const;
    double toFloat() const;
    bool toBool() const;

    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

plString DllExport CleanFileName(const char* fname, bool allowPathChars = false);
size_t DllExport plwcslen(const pl_wchar_t* str);
pl_wchar_t DllExport* plwcsdup(const pl_wchar_t* str);

#endif
