#include "plString.h"
#include "Sys/Platform.h"
#include "Debug/hsExceptions.h"
#include <ctype.h>
#include <wctype.h>
#include <cstdlib>
#include <cstdarg>
#include <cerrno>

#ifndef wcscasecmp
// Mac OSX doesn't have wcscasecmp :(
int wcscasecmp(const wchar_t* s1, const wchar_t* s2) {
    wint_t c1, c2;
    do {
        c1 = towlower(*s1++);
        c2 = towlower(*s2++);
    } while (c1 == c2 && c1 != 0);
    return c1 - c2;
}
#endif

/********************************** plString **********************************/
plString::plStrData::plStrData()
        : fStr(NULL), fLen(0), fHash(0), fRefs(1) { }

plString::plStrData::~plStrData() {
    if (fStr != NULL)
        delete[] fStr;
}

void plString::plStrData::ref() { fRefs++; }

void plString::plStrData::unref() {
    if (--fRefs == 0)
        delete this;
}

const char* plString::plStrData::get() const { return (fStr != NULL) ? fStr : ""; }

plString::plString() : fString(NULL) { }

plString::plString(const plString& init) : fString(init.fString) {
    if (fString != NULL)
        fString->ref();
}

plString::plString(const char* init) : fString(NULL) {
    if (init != NULL) {
        size_t len = strlen(init);
        if (len > 0) {
            fString = new plStrData();
            fString->fLen = len;
            fString->fStr = new char[len+1];
            strcpy(fString->fStr, init);
        }
    }
}

plString::plString(char c) {
    fString = new plStrData();
    fString->fLen = 1;
    fString->fStr = new char[2];
    fString->fStr[0] = c;
    fString->fStr[1] = 0;
}

plString::~plString() {
    if (fString != NULL)
        fString->unref();
}

bool plString::empty() const { return (fString == NULL) || (fString->fLen == 0); }
size_t plString::len() const { return (fString != NULL) ? fString->fLen : 0; }

//char& plString::operator[](size_t idx) const { return fStr[idx]; }

plString& plString::operator=(const plString& other) {
    if (fString != NULL)
        fString->unref();
    if (!other.empty()) {
        fString = other.fString;
        fString->ref();
    } else {
        fString = NULL;
    }
    return (*this);
}

plString& plString::operator=(const char* str) {
    if (fString != NULL)
        fString->unref();
    if (str != NULL) {
        size_t len = strlen(str);
        if (len > 0) {
            fString = new plStrData();
            fString->fLen = len;
            fString->fStr = new char[len+1];
            strcpy(fString->fStr, str);
        } else {
            fString = NULL;
        }
    } else {
        fString = NULL;
    }
    return (*this);
}

plString& plString::operator=(char c) {
    if (fString != NULL)
        fString->unref();
    fString = new plStrData();
    fString->fLen = 1;
    fString->fStr = new char[2];
    fString->fStr[0] = c;
    fString->fStr[1] = 0;
    return (*this);
}

plString& plString::operator+=(const plString& other) {
    if (other.empty())
        return (*this);
    if (empty()) {
        if (fString != NULL)
            fString->unref();
        fString = other.fString;
        if (fString != NULL)
            fString->ref();
        return (*this);
    }
    
    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + other.fString->fLen;
    newStr->fStr = new char[newStr->fLen + 1];
    strcpy(newStr->fStr, fString->fStr);
    strcpy(newStr->fStr + fString->fLen, other.fString->fStr);
    fString->unref();
    fString = newStr;
    return (*this);
}

plString& plString::operator+=(const char* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t len = strlen(str);
    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + len;
    newStr->fStr = new char[newStr->fLen + 1];
    strcpy(newStr->fStr, fString->fStr);
    strcpy(newStr->fStr + fString->fLen, str);
    fString->unref();
    fString = newStr;
    return (*this);
}

plString& plString::operator+=(char c) {
    if (empty())
        return operator=(c);

    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + 1;
    newStr->fStr = new char[newStr->fLen + 1];
    strcpy(newStr->fStr, fString->fStr);
    newStr->fStr[fString->fLen] = c;
    newStr->fStr[fString->fLen + 1] = 0;
    fString->unref();
    fString = newStr;
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

plString plString::operator+(char c) const {
    plString result(*this);
    return (result += c);
}

bool plString::operator==(const plString& other) const {
    if (other.empty()) return empty();
    if (empty()) return false;
    return (strcmp(fString->fStr, other.fString->fStr)==0);
}

bool plString::operator==(const char* str) const {
    if (str == NULL) return empty();
    if (empty()) return false;
    return (strcmp(fString->fStr, str)==0);
}

bool plString::operator!=(const plString& other) const {
    if (other.empty()) return !empty();
    if (empty()) return true;
    return (strcmp(fString->fStr, other.fString->fStr)!=0);
}

bool plString::operator!=(const char* str) const {
    if (str == NULL) return !empty();
    if (empty()) return true;
    return (strcmp(fString->fStr, str)!=0);
}

bool plString::operator<(const plString& other) const {
    if (other.empty()) return false;
    if (empty()) return true;
    return (strcmp(fString->fStr, other.fString->fStr) < 0);
}

bool plString::operator<(const char* str) const {
    if (str == NULL) return false;
    if (empty()) return true;
    return (strcmp(fString->fStr, str) < 0);
}

int plString::compareTo(const plString& other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(fString->fStr, other.fString->fStr);
    } else {
        return strcmp(fString->fStr, other.fString->fStr);
    }
}

int plString::compareTo(const char* other, bool ignoreCase) const {
    if (ignoreCase) {
        return strcasecmp(fString->fStr, other);
    } else {
        return strcmp(fString->fStr, other);
    }
}

bool plString::startsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty()) return true;
    if (empty()) return false;
    if (fString->fLen < cmp.fString->fLen) return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::startsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL) return true;
    if (empty()) return false;
    if (fString->fLen < strlen(cmp)) return false;
    return (left(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const plString& cmp, bool ignoreCase) const {
    if (cmp.empty()) return true;
    if (empty()) return false;
    if (fString->fLen < cmp.fString->fLen) return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const char* cmp, bool ignoreCase) const {
    if (cmp == NULL) return true;
    if (empty()) return false;
    if (fString->fLen < strlen(cmp)) return false;
    return (right(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

const char* plString::cstr() const { return (fString != NULL) ? fString->get() : ""; }
plString::operator const char*() const { return cstr(); }

unsigned int plString::hash() const {
    if (fString != NULL) {
        if (fString->fHash == 0)
            fString->fHash = hash(fString->fStr);
        return fString->fHash;
    }
    return hash(NULL);
}

unsigned int plString::hash(const char* str) {
    if (str == NULL) str = "";
    
    // djb2 hash //
    unsigned int hash = 5381;
    while (*str++)
        hash = ((hash << 5) + hash) ^ *str;
    return hash;
}

long plString::find(char c) const {
    if (empty()) return -1;
    char* pos = strchr(fString->fStr, c);
    if (pos != NULL)
        return (long)(pos - fString->fStr);
    return -1;
}

long plString::find(const char* sub) const {
    if (empty()) return -1;
    if (sub == NULL) return 0;
    size_t len = strlen(sub);
    if (len > fString->fLen) return -1;
    for (size_t i=0; i<(fString->fLen - len); i++) {
        if (strncmp(fString->fStr + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plString::find(const plString& sub) const {
    if (empty()) return -1;
    if (sub.empty()) return 0;
    if (sub.fString->fLen > fString->fLen) return -1;
    for (size_t i=0; i<(fString->fLen - sub.fString->fLen); i++) {
        if (strncmp(fString->fStr + i, sub.fString->fStr, sub.fString->fLen) == 0)
            return (long)i;
    }
    return -1;
}

long plString::rfind(char c) const {
    if (empty()) return -1;
    char* pos = strrchr(fString->fStr, c);
    if (pos != NULL)
        return (long)(pos - fString->fStr);
    return -1;
}

long plString::rfind(const char* sub) const {
    if (empty()) return -1;
    if (sub == NULL) return 0;
    size_t len = strlen(sub);
    if (len > fString->fLen) return -1;
    for (size_t i=(fString->fLen - len); i>0; i--) {
        if (strncmp(fString->fStr + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plString::rfind(const plString& sub) const {
    if (empty()) return -1;
    if (sub.empty()) return 0;
    if (sub.fString->fLen > fString->fLen) return -1;
    for (size_t i=(fString->fLen - sub.fString->fLen); i>0; i--) {
        if (strncmp(fString->fStr + (i-1), sub.fString->fStr, sub.fString->fLen) == 0)
            return (long)(i-1);
    }
    return -1;
}

plString& plString::toUpper() {
    if (!empty()) {
        plStrData* upper = new plStrData();
        upper->fLen = fString->fLen;
        upper->fStr = new char[upper->fLen + 1];
        char* d = upper->fStr;
        for (char* c=fString->fStr; *c; c++)
            *d++ = toupper(*c);
        *d = 0;
        fString->unref();
        fString = upper;
    }
    return (*this);
}

plString& plString::toLower() {
    if (!empty()) {
        plStrData* lower = new plStrData();
        lower->fLen = fString->fLen;
        lower->fStr = new char[lower->fLen + 1];
        char* d = lower->fStr;
        for (char* c=fString->fStr; *c; c++)
            *d++ = tolower(*c);
        *d = 0;
        fString->unref();
        fString = lower;
    }
    return (*this);
}

plString plString::left(size_t num) const {
    if (empty()) return plString();
    if (num > fString->fLen) num = fString->fLen;
    if (num == fString->fLen) return *this;
    
    plString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new char[num+1];
    strncpy(retn.fString->fStr, fString->fStr, num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plString plString::right(size_t num) const {
    if (empty()) return plString();
    if (num > fString->fLen) num = fString->fLen;
    if (num == fString->fLen) return *this;

    plString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new char[num+1];
    strncpy(retn.fString->fStr, fString->fStr + (fString->fLen - num), num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plString plString::mid(size_t idx, size_t num) const {
    if (empty()) return plString();
    if (idx > fString->fLen) return plString();
    if (idx + num > fString->fLen) num = fString->fLen - idx;

    plString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new char[num+1];
    strncpy(retn.fString->fStr, fString->fStr + idx, num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plString plString::mid(size_t idx) const {
    if (fString == NULL) return plString();
    return mid(idx, fString->fLen - idx);
}

plString plString::beforeFirst(char sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return left(pos);
    else
        return (*this);
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
        return (*this);
}

std::vector<plString> plString::split(char sep) const {
    std::vector<plString> splits;
    if (!empty()) {
        splits.push_back(beforeFirst(sep));
        plString rest(afterFirst(sep));
        std::vector<plString> spRight = rest.split(sep);
        splits.resize(1 + spRight.size());
        for (size_t i=0; i<spRight.size(); i++)
            splits[1 + i] = spRight[i];
    }
    return splits;
}

long plString::toInt(int base) const {
    if (empty()) return 0;
    errno = 0;
    long value = strtol(fString->fStr, NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
    return value;
}

unsigned long plString::toUint(int base) const {
    if (empty()) return 0;
    errno = 0;
    unsigned long value = strtoul(fString->fStr, NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
    return value;
}

double plString::toFloat() const {
    if (empty()) return 0.0;
    errno = 0;
    double value = strtod(fString->fStr, NULL);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
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
    char buf[4096];
    vsnprintf(buf, 4096, fmt, aptr);
    return plString(buf);
}


/********************************* plWString *********************************/
plWString::plStrData::plStrData()
         : fStr(NULL), fLen(0), fHash(0), fRefs(1) { }

plWString::plStrData::~plStrData() {
    if (fStr != NULL)
        delete[] fStr;
}

void plWString::plStrData::ref() { fRefs++; }

void plWString::plStrData::unref() {
    if (--fRefs == 0)
        delete this;
}

const wchar_t* plWString::plStrData::get() const { return (fStr != NULL) ? fStr : L""; }

plWString::plWString() : fString(NULL) { }

plWString::plWString(const plWString& init) : fString(init.fString) {
    if (fString != NULL)
        fString->ref();
}

plWString::plWString(const wchar_t* init) : fString(NULL) {
    if (init != NULL) {
        size_t len = wcslen(init);
        if (len > 0) {
            fString = new plStrData();
            fString->fLen = len;
            fString->fStr = new wchar_t[len+1];
            wcscpy(fString->fStr, init);
        }
    }
}

plWString::plWString(wchar_t c) {
    fString = new plStrData();
    fString->fLen = 1;
    fString->fStr = new wchar_t[2];
    fString->fStr[0] = c;
    fString->fStr[1] = 0;
}

plWString::~plWString() {
    if (fString != NULL)
        fString->unref();
}

bool plWString::empty() const { return (fString == NULL) || (fString->fLen == 0); }
size_t plWString::len() const { return (fString != NULL) ? fString->fLen : 0; }

//wchar_t& plWString::operator[](size_t idx) const { return fStr[idx]; }

plWString& plWString::operator=(const plWString& other) {
    if (fString != NULL)
        fString->unref();
    if (!other.empty()) {
        fString = other.fString;
        if (fString != NULL);
            fString->ref();
    } else {
        fString = NULL;
    }
    return (*this);
}

plWString& plWString::operator=(const wchar_t* str) {
    if (fString != NULL)
        fString->unref();
    if (str != NULL) {
        size_t len = wcslen(str);
        if (len > 0) {
            fString = new plStrData();
            fString->fLen = len;
            fString->fStr = new wchar_t[len+1];
            wcscpy(fString->fStr, str);
        } else {
            fString = NULL;
        }
    } else {
        fString = NULL;
    }
    return (*this);
}

plWString& plWString::operator=(wchar_t c) {
    if (fString != NULL)
        fString->unref();
    fString = new plStrData();
    fString->fLen = 1;
    fString->fStr = new wchar_t[2];
    fString->fStr[0] = c;
    fString->fStr[1] = 0;
    return (*this);
}

plWString& plWString::operator+=(const plWString& other) {
    if (other.empty())
        return (*this);
    if (empty()) {
        if (fString != NULL)
            fString->unref();
        fString = other.fString;
        if (fString != NULL)
            fString->ref();
        return (*this);
    }

    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + other.fString->fLen;
    newStr->fStr = new wchar_t[newStr->fLen + 1];
    wcscpy(newStr->fStr, fString->fStr);
    wcscpy(newStr->fStr + fString->fLen, other.fString->fStr);
    fString->unref();
    fString = newStr;
    return (*this);
}

plWString& plWString::operator+=(const wchar_t* str) {
    if (str == NULL)
        return (*this);
    if (empty())
        return operator=(str);

    size_t len = wcslen(str);
    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + len;
    newStr->fStr = new wchar_t[newStr->fLen + 1];
    wcscpy(newStr->fStr, fString->fStr);
    wcscpy(newStr->fStr + fString->fLen, str);
    fString->unref();
    fString = newStr;
    return (*this);
}

plWString& plWString::operator+=(wchar_t c) {
    if (empty())
        return operator=(c);

    plStrData* newStr = new plStrData();
    newStr->fLen = fString->fLen + 1;
    newStr->fStr = new wchar_t[newStr->fLen + 1];
    newStr->fStr[fString->fLen] = c;
    newStr->fStr[fString->fLen + 1] = 0;
    fString->unref();
    fString = newStr;
    return (*this);
}

plWString plWString::operator+(const plWString& other) const {
    plWString result(*this);
    return (result += other);
}

plWString plWString::operator+(const wchar_t* str) const {
    plWString result(*this);
    return (result += str);
}

plWString plWString::operator+(wchar_t c) const {
    plWString result(*this);
    return (result += c);
}

bool plWString::operator==(const plWString& other) const {
    if (other.empty()) return empty();
    if (empty()) return false;
    return (wcscmp(fString->fStr, other.fString->fStr)==0);
}

bool plWString::operator==(const wchar_t* str) const {
    if (str == NULL) return empty();
    if (empty()) return false;
    return (wcscmp(fString->fStr, str)==0);
}

bool plWString::operator!=(const plWString& other) const {
    if (other.empty()) return !empty();
    if (empty()) return true;
    return (wcscmp(fString->fStr, other.fString->fStr)!=0);
}

bool plWString::operator!=(const wchar_t* str) const {
    if (str == NULL) return !empty();
    if (empty()) return true;
    return (wcscmp(fString->fStr, str)!=0);
}

bool plWString::operator<(const plWString& other) const {
    if (other.empty()) return false;
    if (empty()) return true;
    return (wcscmp(fString->fStr, other.fString->fStr) < 0);
}

bool plWString::operator<(const wchar_t* str) const {
    if (str == NULL) return false;
    if (empty()) return true;
    return (wcscmp(fString->fStr, str) < 0);
}

int plWString::compareTo(const plWString& other, bool ignoreCase) const {
    if (ignoreCase) {
        return wcscasecmp(fString->fStr, other.fString->fStr);
    } else {
        return wcscmp(fString->fStr, other.fString->fStr);
    }
}

int plWString::compareTo(const wchar_t* other, bool ignoreCase) const {
    if (ignoreCase) {
        return wcscasecmp(fString->fStr, other);
    } else {
        return wcscmp(fString->fStr, other);
    }
}

bool plWString::startsWith(const plWString& cmp, bool ignoreCase) const {
    if (cmp.empty()) return true;
    if (empty()) return false;
    if (fString->fLen < cmp.fString->fLen) return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::startsWith(const wchar_t* cmp, bool ignoreCase) const {
    if (cmp == NULL) return true;
    if (empty()) return false;
    if (fString->fLen < wcslen(cmp)) return false;
    return (left(wcslen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::endsWith(const plWString& cmp, bool ignoreCase) const {
    if (cmp.empty()) return true;
    if (empty()) return false;
    if (fString->fLen < cmp.fString->fLen) return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::endsWith(const wchar_t* cmp, bool ignoreCase) const {
    if (cmp == NULL) return true;
    if (empty()) return false;
    if (fString->fLen < wcslen(cmp)) return false;
    return (right(wcslen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

const wchar_t* plWString::cstr() const { return (fString != NULL) ? fString->get() : L""; }
plWString::operator const wchar_t*() const { return cstr(); }

unsigned int plWString::hash() const {
    if (fString != NULL) {
        if (fString->fHash == 0)
            fString->fHash = hash(fString->fStr);
        return fString->fHash;
    }
    return hash(NULL);
}

unsigned int plWString::hash(const wchar_t* str) {
    if (str == NULL)
        str = L"";

    // djb2 hash //
    // hopefully this works as well on wstrings as on strings... //
    unsigned int hash = 5381;
    while (*str++)
        hash = ((hash << 5) + hash) ^ *str;
    return hash;
}

long plWString::find(wchar_t c) const {
    if (empty()) return -1;
    wchar_t* pos = wcschr(fString->fStr, c);
    if (pos != NULL)
        return (long)(pos - fString->fStr);
    return -1;
}

long plWString::find(const wchar_t* sub) const {
    if (empty()) return -1;
    if (sub == NULL) return 0;
    size_t len = wcslen(sub);
    if (len > fString->fLen) return -1;
    for (size_t i=0; i<(fString->fLen - len); i++) {
        if (wcsncmp(fString->fStr + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plWString::find(const plWString& sub) const {
    if (empty()) return -1;
    if (sub.empty()) return 0;
    if (sub.fString->fLen > fString->fLen) return -1;
    for (size_t i=0; i<(fString->fLen - sub.fString->fLen); i++) {
        if (wcsncmp(fString->fStr + i, sub.fString->fStr, sub.fString->fLen) == 0)
            return (long)i;
    }
    return -1;
}

long plWString::rfind(wchar_t c) const {
    if (empty()) return -1;
    wchar_t* pos = wcsrchr(fString->fStr, c);
    if (pos != NULL)
        return (long)(pos - fString->fStr);
    return -1;
}

long plWString::rfind(const wchar_t* sub) const {
    if (empty()) return -1;
    if (sub == NULL) return 0;
    size_t len = wcslen(sub);
    if (len > fString->fLen) return -1;
    for (size_t i=(fString->fLen - len); i>0; i--) {
        if (wcsncmp(fString->fStr + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plWString::rfind(const plWString& sub) const {
    if (empty()) return -1;
    if (sub.empty()) return 0;
    if (sub.fString->fLen > fString->fLen) return -1;
    for (size_t i=(fString->fLen - sub.fString->fLen); i>0; i--) {
        if (wcsncmp(fString->fStr + (i-1), sub.fString->fStr, sub.fString->fLen) == 0)
            return (long)(i-1);
    }
    return -1;
}

plWString& plWString::toUpper() {
    if (!empty()) {
        plStrData* upper = new plStrData();
        upper->fLen = fString->fLen;
        upper->fStr = new wchar_t[upper->fLen + 1];
        wchar_t* d = upper->fStr;
        for (wchar_t* c=fString->fStr; *c; c++)
            *d++ = towupper(*c);
        *d = 0;
        fString->unref();
        fString = upper;
    }
    return (*this);
}

plWString& plWString::toLower() {
    if (!empty()) {
        plStrData* lower = new plStrData();
        lower->fLen = fString->fLen;
        lower->fStr = new wchar_t[lower->fLen + 1];
        wchar_t* d = lower->fStr;
        for (wchar_t* c=fString->fStr; *c; c++)
            *d++ = towlower(*c);
        *d = 0;
        fString->unref();
        fString = lower;
    }
    return (*this);
}

plWString plWString::left(size_t num) const {
    if (empty()) return plWString();
    if (num > fString->fLen) num = fString->fLen;
    if (num == fString->fLen) return *this;

    plWString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new wchar_t[num+1];
    wcsncpy(retn.fString->fStr, fString->fStr, num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plWString plWString::right(size_t num) const {
    if (empty()) return plWString();
    if (num > fString->fLen) num = fString->fLen;
    if (num == fString->fLen) return *this;

    plWString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new wchar_t[num+1];
    wcsncpy(retn.fString->fStr, fString->fStr + (fString->fLen - num), num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plWString plWString::mid(size_t idx, size_t num) const {
    if (empty()) return plWString();
    if (idx > fString->fLen) return plWString();
    if (idx + num > fString->fLen) num = fString->fLen - idx;

    plWString retn;
    retn.fString = new plStrData();
    retn.fString->fLen = num;
    retn.fString->fStr = new wchar_t[num+1];
    wcsncpy(retn.fString->fStr, fString->fStr + idx, num);
    retn.fString->fStr[num] = 0;
    return retn;
}

plWString plWString::mid(size_t idx) const {
    if (fString == NULL) return plWString();
    return mid(idx, fString->fLen - idx);
}

plWString plWString::beforeFirst(wchar_t sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return left(pos);
    else
        return (*this);
}

plWString plWString::afterFirst(wchar_t sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return mid(pos+1);
    else
        return plWString();
}

plWString plWString::beforeLast(wchar_t sep) const {
    long pos = rfind(sep);
    if (pos >= 0)
        return left(pos);
    else
        return plWString();
}

plWString plWString::afterLast(wchar_t sep) const {
    long pos = rfind(sep);
    if (pos >= 0)
        return mid(pos+1);
    else
        return (*this);
}

std::vector<plWString> plWString::split(char sep) const {
    std::vector<plWString> splits;
    if (!empty()) {
        splits.push_back(beforeFirst(sep));
        plWString rest(afterFirst(sep));
        std::vector<plWString> spRight = rest.split(sep);
        splits.resize(1 + spRight.size());
        for (size_t i=0; i<spRight.size(); i++)
            splits[1 + i] = spRight[i];
    }
    return splits;
}

long plWString::toInt(int base) const {
    if (empty()) return 0;
    errno = 0;
    long value = wcstol(fString->fStr, NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
    return value;
}

unsigned long plWString::toUint(int base) const {
    if (empty()) return 0;
    errno = 0;
    unsigned long value = wcstoul(fString->fStr, NULL, base);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
    return value;
}

double plWString::toFloat() const {
    if (empty()) return 0.0;
    errno = 0;
    double value = wcstod(fString->fStr, NULL);
    if (errno == ERANGE || errno == EINVAL)
        throw hsBadParamException(__FILE__, __LINE__);
    return value;
}

bool plWString::toBool() const {
    if (compareTo(L"true", true) == 0)
        return true;
    if (compareTo(L"false", true) == 0)
        return false;
    return (toUint() != 0);
}

plWString plWString::Format(const wchar_t* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    plWString str = FormatV(fmt, argptr);
    va_end(argptr);
    return str;
}

plWString plWString::FormatV(const wchar_t* fmt, va_list aptr) {
    wchar_t buf[4096];
    vswprintf(buf, 4096, fmt, aptr);
    return plWString(buf);
}


/***************************** Utility Functions ******************************/
plString hsWStringToString(const wchar_t* str) {
    size_t cnvLen = wcstombs(NULL, str, 0);
    if (cnvLen > 0 && cnvLen != (size_t)(-1)) {
        char* buf = new char[cnvLen+1];
        wcstombs(buf, str, cnvLen+1);
        plString result(buf);
        delete[] buf;
        return result;
    } else {
        return "";
    }
}

plWString hsStringToWString(const char* str) {
    size_t cnvLen = mbstowcs(NULL, str, 0);
    if (cnvLen > 0 && cnvLen != (size_t)(-1)) {
        wchar_t* buf = new wchar_t[cnvLen+1];
        mbstowcs(buf, str, cnvLen+1);
        plWString result(buf);
        delete[] buf;
        return result;
    } else {
        return L"";
    }
}

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
