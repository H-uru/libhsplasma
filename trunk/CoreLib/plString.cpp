#include "plString.h"

plString::plString()
        : fStr(NULL), fLen(0), fHaveHash(false) { }

plString::plString(const plString& init)
        : fLen(init.fLen), fHash(init.fHash), fHaveHash(init.fHaveHash) {
    fStr = new char[fLen+1];
    strcpy(fStr, init.fStr);
}

plString::plString(const char* init)
        : fHaveHash(false) {
    if (init != NULL) {
        fLen = strlen(init);
        fStr = new char[fLen+1];
        strcpy(fStr, init);
    } else {
        fLen = 0;
        fStr = NULL;
    }
}

plString::~plString() {
    if (fStr) delete[] fStr;
}

bool plString::empty() const { return (fStr == NULL) || (fLen == 0); }
size_t plString::len() const { return fLen; }

char& plString::operator[](size_t idx) const {
    return fStr[idx];
}

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

plString plString::operator+(const plString& other) {
    plString result(*this);
    return (result += other);
}

plString plString::operator+(const char* str) {
    plString result(*this);
    return (result += str);
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

const char* plString::find(char c) { return strchr(fStr, c); }
const char* plString::rfind(char c) { return strrchr(fStr, c); }
