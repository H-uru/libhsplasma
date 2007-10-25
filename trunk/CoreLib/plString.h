#ifndef _PLSTRING_H
#define _PLSTRING_H

#include <cstring>
#include <cstdio>
#include <wchar.h>
#include "../PlasmaDefs.h"

DllClass plStringBase {
protected:
    size_t fLen;
    mutable unsigned int fHash;
    mutable bool fHaveHash;

public:
    plStringBase();
    plStringBase(const plStringBase& init);
    virtual ~plStringBase();

    virtual bool empty() const =0;
    virtual size_t len() const;

    virtual unsigned int hash() const =0;

    virtual long toInt(int base = 0) const =0;
    virtual unsigned long toUInt(int base = 0) const =0;
    virtual double toFloat() const =0;
};

DllClass plString : public plStringBase {
protected:
    char* fStr;

public:
    plString();
    plString(const plString& init);
    plString(const char* init);
    plString(char c);
    virtual ~plString();

    virtual bool empty() const;

    //char& operator[](size_t idx) const;
    plString& operator=(const plString& other);
    plString& operator=(const char* str);
    plString& operator=(char c);
    plString& operator+=(const plString& other);
    plString& operator+=(const char* str);
    plString& operator+=(char c);
    plString operator+(const plString& other);
    plString operator+(const char* str);
    plString operator+(char c);
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
    char* copybuf() const;

    virtual unsigned int hash() const;
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

    virtual long toInt(int base = 0) const;
    virtual unsigned long toUInt(int base = 0) const;
    virtual double toFloat() const;

    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

DllClass plWString : public plStringBase {
protected:
    wchar_t* fStr;

public:
    plWString();
    plWString(const plWString& init);
    plWString(const wchar_t* init);
    plWString(wchar_t c);
    virtual ~plWString();

    virtual bool empty() const;

    //wchar_t& operator[](size_t idx) const;
    plWString& operator=(const plWString& other);
    plWString& operator=(const wchar_t* str);
    plWString& operator=(wchar_t c);
    plWString& operator+=(const plWString& other);
    plWString& operator+=(const wchar_t* str);
    plWString& operator+=(wchar_t c);
    plWString operator+(const plWString& other);
    plWString operator+(const wchar_t* str);
    plWString operator+(wchar_t c);
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
    wchar_t* copybuf() const;

    virtual unsigned int hash() const;
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

    virtual long toInt(int base = 0) const;
    virtual unsigned long toUInt(int base = 0) const;
    virtual double toFloat() const;

    static plWString Format(const wchar_t* fmt, ...);
    static plWString FormatV(const wchar_t* fmt, va_list aptr);
};

plString hsWStringToString(const wchar_t* str);
plWString hsStringToWString(const char* str);

#endif
