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

    int compareTo(plString& other, bool ignoreCase = false);
    int compareTo(const char* other, bool ignoreCase = false);

    const char* cstr() const;
    operator const char*() const;
    unsigned int hash() const;
    static unsigned int hash(const char* str);

    long find(char c);
    long find(const char* sub);
    long find(plString& sub);
    long rfind(char c);
    long rfind(const char* sub);
    long rfind(plString& sub);
    plString& toUpper();
    plString& toLower();
    plString left(size_t num);
    plString right(size_t num);
    plString mid(size_t idx, size_t num);
    plString mid(size_t idx);

    long toInt() const;
    double toFloat() const;

public:
    static plString Format(const char* fmt, ...);
    static plString FormatV(const char* fmt, va_list aptr);
};

#endif
