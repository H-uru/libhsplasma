#include "plString.h"
#include <ctype.h>
#include <cstdlib>

plString::plString()
        : fStr(NULL), fLen(0), fHaveHash(false) { }

plString::plString(const plString& init)
        : fLen(init.fLen), fHash(init.fHash), fHaveHash(init.fHaveHash) {
    if (!init.empty()) {
        fStr = new char[fLen+1];
        strcpy(fStr, init.fStr);
    } else {
        fStr = NULL;
    }
}

plString::plString(const char* init)
        : fHaveHash(false) {
    if (init != NULL) {
        fLen = strlen(init);
        if (fLen > 0) {
            fStr = new char[fLen+1];
            strcpy(fStr, init);
        } else {
            fStr = NULL;
        }
    } else {
        fLen = 0;
        fStr = NULL;
    }
}

plString::plString(char c)
        : fLen(1), fHaveHash(false) {
    fStr = new char[2];
    fStr[0] = c;
    fStr[1] = 0;
}

plString::~plString() {
    if (fStr) delete[] fStr;
}

bool plString::empty() const { return (fStr == NULL) || (fLen == 0); }
size_t plString::len() const { return fLen; }

//char& plString::operator[](size_t idx) const { return fStr[idx]; }

plString& plString::operator=(const plString& other) {
    if (fStr) delete[] fStr;
    if (!other.empty()) {
        fLen = other.fLen;
        fStr = new char[fLen+1];
        strcpy(fStr, other.fStr);
    } else {
        fLen = 0;
        fStr = NULL;
    }
    fHash = other.fHash;
    fHaveHash = other.fHaveHash;
    return (*this);
}

plString& plString::operator=(const char* str) {
    if (fStr) delete[] fStr;
    if (str != NULL) {
        fLen = strlen(str);
        fStr = new char[fLen+1];
        strcpy(fStr, str);
    } else {
        fLen = 0;
        fStr = NULL;
    }
    fHaveHash = false;
    return (*this);
}

plString& plString::operator=(char c) {
    if (fStr) delete[] fStr;
    fLen = 1;
    fStr = new char[2];
    fStr[0] = c;
    fStr[1] = 0;
    fHaveHash = false;
    return (*this);
}

plString& plString::operator+=(const plString& other) {
    if (!other.empty()) {
        fLen += other.fLen;
        char* newStr = new char[fLen+1];
        if (empty()) {
            strcpy(newStr, other.fStr);
            fHash = other.fHash;
            fHaveHash = other.fHaveHash;
        } else {
            sprintf(newStr, "%s%s", fStr, other.fStr);
            fHaveHash = false;
        }
        if (fStr) delete[] fStr;
        fStr = newStr;
    }
    return (*this);
}

plString& plString::operator+=(const char* str) {
    if (str != NULL) {
        fLen += strlen(str);
        char* newStr = new char[fLen+1];
        if (empty())
            strcpy(newStr, str);
        else
            sprintf(newStr, "%s%s", fStr, str);
        fHaveHash = false;
        if (fStr) delete[] fStr;
        fStr = newStr;
    }
    return (*this);
}

plString& plString::operator+=(char c) {
    fLen++;
    char* newStr = new char[fLen+1];
    if (empty()) {
        newStr[0] = c;
        newStr[1] = 0;
    } else {
        strcpy(newStr, fStr);
        newStr[fLen-1] = c;
        newStr[fLen] = 0;
    }
    fHaveHash = false;
    if (fStr) delete[] fStr;
    fStr = newStr;
    return (*this);
}

plString plString::operator+(const plString& other) {
    plString result(*this);
    return (result += other);
}

plString plString::operator+(const char* str) {
    plString result(*this);
    return (result += str);
}

plString plString::operator+(char c) {
    plString result(*this);
    return (result += c);
}

bool plString::operator==(const plString& other) const {
    if (hash() != other.hash())
        return false;
    return (strcmp(fStr, other.fStr)==0);
}

bool plString::operator==(const char* str) const {
    if (hash() != hash(str))
        return false;
    return (strcmp(fStr, str)==0);
}

bool plString::operator!=(const plString& other) const {
    if (hash() != other.hash())
        return true;
    return (strcmp(fStr, other.fStr)!=0);
}

bool plString::operator!=(const char* str) const {
    if (hash() != hash(str))
        return true;
    return (strcmp(fStr, str)!=0);
}

int plString::compareTo(plString& other, bool ignoreCase) {
    if (ignoreCase) {
        plString s1 = *this;
        plString s2 = other;
        return strcmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return strcmp(fStr, other.fStr);
    }
}

int plString::compareTo(const char* other, bool ignoreCase) {
    if (ignoreCase) {
        plString s1 = *this;
        plString s2 = other;
        return strcmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return strcmp(fStr, other);
    }
}

const char* plString::cstr() const { return fStr; }
plString::operator const char*() const { return fStr; }

unsigned int plString::hash() const {
    if (!fHaveHash) {
        fHash = hash(fStr);
        fHaveHash = true;
    }
    return fHash;
}

unsigned int plString::hash(const char* str) {
    // djb2 hash //
    unsigned int hash = 5381;
    while (*str++)
        hash = ((hash << 5) + hash) ^ *str;
    return hash;
}

long plString::find(char c) {
    char* pos = strchr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plString::find(const char* sub) {
    size_t len = strlen(sub);
    if (len > fLen) return -1;
    for (size_t i=0; i<(fLen - len); i++) {
        if (strncmp(fStr + i, sub, len) == 0)
            return i;
    }
    return -1;
}

long plString::find(plString& sub) {
    if (sub.fLen > fLen) return -1;
    for (size_t i=0; i<(fLen - sub.fLen); i++) {
        if (strncmp(fStr + i, sub.fStr, sub.fLen) == 0)
            return i;
    }
    return -1;
}

long plString::rfind(char c) {
    char* pos = strrchr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plString::rfind(const char* sub) {
    size_t len = strlen(sub);
    if (len > fLen) return -1;
    for (size_t i=(fLen - len); i>0; i--) {
        if (strncmp(fStr + (i-1), sub, len) == 0)
            return i-1;
    }
    return -1;
}

long plString::rfind(plString& sub) {
    if (sub.fLen > fLen) return -1;
    for (size_t i=(fLen - sub.fLen); i>0; i--) {
        if (strncmp(fStr + (i-1), sub.fStr, sub.fLen) == 0)
            return i-1;
    }
    return -1;
}

plString& plString::toUpper() {
    for (char* c=fStr; *c; c++)
        *c = toupper(*c);
    return (*this);
}

plString& plString::toLower() {
    for (char* c=fStr; *c; c++)
        *c = tolower(*c);
    return (*this);
}

plString plString::left(size_t num) {
    if (num > fLen) num = fLen;
    if (num == fLen) return plString(fStr);
    char* buf = new char[num+1];
    strncpy(buf, fStr, num);
    buf[num] = 0;
    return plString(buf);
}

plString plString::right(size_t num) {
    if (num > fLen) num = fLen;
    if (num == fLen) return plString(fStr);
    char* buf = new char[num+1];
    strncpy(buf, fStr + (fLen - num), num);
    buf[num] = 0;
    return plString(buf);
}

plString plString::mid(size_t idx, size_t num) {
    if (idx > fLen) return plString("");
    if (idx + num > fLen) num = fLen - idx;
    char* buf = new char[num+1];
    strncpy(buf, fStr + idx, num);
    buf[num] = 0;
    return plString(buf);
}

plString plString::mid(size_t idx) {
    return mid(idx, fLen - idx);
}

long plString::toInt() const {
    return strtol(fStr, NULL, 0);
}

double plString::toFloat() const {
    return strtod(fStr, NULL);
}

plString plString::Format(const char* fmt, ...) {
    ...
}

plString plString::FormatV(const char* fmt, va_list aptr) {
    ...
}
