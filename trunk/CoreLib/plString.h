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
    ~plString();

    bool empty() const;
    size_t len() const;

    char& operator[](size_t idx) const;
    plString& operator=(const plString& other);
    plString& operator=(const char* str);
    plString& operator+=(const plString& other);
    plString& operator+=(const char* str);
    plString operator+(const plString& other);
    plString operator+(const char* str);
    bool operator==(const plString& other) const;
    bool operator==(const char* str) const;
    bool operator!=(const plString& other) const;
    bool operator!=(const char* str) const;

    const char* cstr() const;
    operator const char*() const;

    unsigned int hash() const;
    static unsigned int hash(const char* str);
    const char* find(char c);
    const char* rfind(char c);
};

#endif
