#ifndef _PLSTRING_H
#define _PLSTRING_H

#include <cstring>
#include <cstdio>
#include <vector>
#include <wchar.h>
#include "PlasmaDefs.h"

DllClass plString {
protected:
    struct plStrData {
        char* fStr;
        size_t fLen;
        unsigned int fHash, fRefs;

        plStrData();
        ~plStrData();
        void ref();
        void unref();
        const char* get() const;
    };
    plStrData* fString;

public:
    plString();
    plString(const plString& init);
    plString(const char* init);
    plString(char c);
    ~plString();

    bool empty() const;
    size_t len() const;

    //char& operator[](size_t idx) const;
    plString& operator=(const plString& other);
    plString& operator=(const char* str);
    plString& operator=(char c);
    plString& operator+=(const plString& other);
    plString& operator+=(const char* str);
    plString& operator+=(char c);
    plString operator+(const plString& other) const;
    plString operator+(const char* str) const;
    plString operator+(char c) const;
    bool operator==(const plString& other) const;
    bool operator==(const char* str) const;
    bool operator!=(const plString& other) const;
    bool operator!=(const char* str) const;
    bool operator<(const plString& other) const;
    bool operator<(const char* str) const;

    int compareTo(const plString& other, bool ignoreCase = false) const;
    int compareTo(const char* other, bool ignoreCase = false) const;
    bool startsWith(const plString& cmp, bool ignoreCase = false) const;
    bool startsWith(const char* cmp, bool ignoreCase = false) const;
    bool endsWith(const plString& cmp, bool ignoreCase = false) const;
    bool endsWith(const char* cmp, bool ignoreCase = false) const;

    const char* cstr() const;
    operator const char*() const;

    unsigned int hash() const;
    static unsigned int hash(const char* str);

    long find(char c) const;
    long find(const char* sub) const;
    long find(const plString& sub) const;
    long rfind(char c) const;
    long rfind(const char* sub) const;
    long rfind(const plString& sub) const;
    plString& toUpper();
    plString& toLower();
    plString left(size_t num) const;
    plString right(size_t num) const;
    plString mid(size_t idx, size_t num) const;
    plString mid(size_t idx) const;
    plString beforeFirst(char sep) const;
    plString afterFirst(char sep) const;
    plString beforeLast(char sep) const;
    plString afterLast(char sep) const;
    std::vector<plString> split(char sep) const;

    long toInt(int base = 0) const;
    unsigned long toUint(int base = 0) const;
    double toFloat() const;
    bool toBool() const;

    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

DllClass plWString {
protected:
    struct plStrData {
        wchar_t* fStr;
        size_t fLen;
        unsigned int fHash, fRefs;

        plStrData();
        ~plStrData();
        void ref();
        void unref();
        const wchar_t* get() const;
    };
    plStrData* fString;

public:
    plWString();
    plWString(const plWString& init);
    plWString(const wchar_t* init);
    plWString(wchar_t c);
    ~plWString();

    bool empty() const;
    size_t len() const;

    //wchar_t& operator[](size_t idx) const;
    plWString& operator=(const plWString& other);
    plWString& operator=(const wchar_t* str);
    plWString& operator=(wchar_t c);
    plWString& operator+=(const plWString& other);
    plWString& operator+=(const wchar_t* str);
    plWString& operator+=(wchar_t c);
    plWString operator+(const plWString& other) const;
    plWString operator+(const wchar_t* str) const;
    plWString operator+(wchar_t c) const;
    bool operator==(const plWString& other) const;
    bool operator==(const wchar_t* str) const;
    bool operator!=(const plWString& other) const;
    bool operator!=(const wchar_t* str) const;
    bool operator<(const plWString& other) const;
    bool operator<(const wchar_t* str) const;

    int compareTo(const plWString& other, bool ignoreCase = false) const;
    int compareTo(const wchar_t* other, bool ignoreCase = false) const;
    bool startsWith(const plWString& cmp, bool ignoreCase = false) const;
    bool startsWith(const wchar_t* cmp, bool ignoreCase = false) const;
    bool endsWith(const plWString& cmp, bool ignoreCase = false) const;
    bool endsWith(const wchar_t* cmp, bool ignoreCase = false) const;

    const wchar_t* cstr() const;
    operator const wchar_t*() const;

    unsigned int hash() const;
    static unsigned int hash(const wchar_t* str);

    long find(wchar_t c) const;
    long find(const wchar_t* sub) const;
    long find(const plWString& sub) const;
    long rfind(wchar_t c) const;
    long rfind(const wchar_t* sub) const;
    long rfind(const plWString& sub) const;
    plWString& toUpper();
    plWString& toLower();
    plWString left(size_t num) const;
    plWString right(size_t num) const;
    plWString mid(size_t idx, size_t num) const;
    plWString mid(size_t idx) const;
    plWString beforeFirst(wchar_t sep) const;
    plWString afterFirst(wchar_t sep) const;
    plWString beforeLast(wchar_t sep) const;
    plWString afterLast(wchar_t sep) const;
    std::vector<plWString> split(char sep) const;

    long toInt(int base = 0) const;
    unsigned long toUint(int base = 0) const;
    double toFloat() const;
    bool toBool() const;

    static plWString Format(const wchar_t* fmt, ...);
    static plWString FormatV(const wchar_t* fmt, va_list aptr);
};

plString DllExport hsWStringToString(const wchar_t* str);
plWString DllExport hsStringToWString(const char* str);

plString DllExport CleanFileName(const char* fname, bool allowPathChars = false);

#endif
