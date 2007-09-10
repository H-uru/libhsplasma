#ifndef _PLSTRING_H
#define _PLSTRING_H

#include <cstring>
#include <cstdio>

class plString {
private:
    char* fStr;
    size_t fLen;
    mutable unsigned int fHash;
    mutable bool fHaveHash;

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
    unsigned int hash() const;
    static unsigned int hash(const char* str);

    long find(char c) const;
    long find(const char* sub) const;
    long find(plString& sub) const;
    long rfind(char c) const;
    long rfind(const char* sub) const;
    long rfind(plString& sub) const;
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

    long toInt(int base = 0) const;
    unsigned long toUInt(int base = 0) const;
    double toFloat() const;

public:
    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

#endif
