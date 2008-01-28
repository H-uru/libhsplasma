#include "plString.h"
#include "DynLib/Platform.h"
#include <ctype.h>
#include <wctype.h>
#include <cstdlib>
#include <cstdarg>

/******************************** plStringBase ********************************/
plStringBase::plStringBase() : fLen(0), fHaveHash(false) { }
plStringBase::plStringBase(const plStringBase& init)
            : fLen(init.fLen), fHash(init.fHash), fHaveHash(init.fHaveHash) { }
plStringBase::~plStringBase() { }

size_t plStringBase::len() const { return fLen; }


/********************************** plString **********************************/
plString::plString() : fStr(NULL) { }

plString::plString(const plString& init) : plStringBase(init) {
    if (!init.empty()) {
        fStr = new char[fLen+1];
        strcpy(fStr, init.fStr);
    } else {
        fStr = NULL;
    }
}

plString::plString(const char* init) : plStringBase() {
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

plString::plString(char c) : plStringBase() {
    fLen = 1;
    fStr = new char[2];
    fStr[0] = c;
    fStr[1] = 0;
}

plString::~plString() {
    if (fStr) delete[] fStr;
}

bool plString::empty() const { return (fStr == NULL) || (fLen == 0); }

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
            snprintf(newStr, fLen+1, "%s%s", fStr, other.fStr);
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
            snprintf(newStr, fLen+1, "%s%s", fStr, str);
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
    if (other.empty()) return empty();
    if (hash() != other.hash())
        return false;
    return (strcmp(fStr, other.fStr)==0);
}

bool plString::operator==(const char* str) const {
    if (str == NULL) return empty();
    if (hash() != hash(str))
        return false;
    return (strcmp(fStr, str)==0);
}

bool plString::operator!=(const plString& other) const {
    if (other.empty()) return !empty();
    if (hash() != other.hash())
        return true;
    return (strcmp(fStr, other.fStr)!=0);
}

bool plString::operator!=(const char* str) const {
    if (str == NULL) return !empty();
    if (hash() != hash(str))
        return true;
    return (strcmp(fStr, str)!=0);
}

bool plString::operator<(const plString& other) const {
    if (other.empty()) return false;
    if (empty()) return true;
    return (strcmp(fStr, other.fStr) < 0);
}

bool plString::operator<(const char* str) const {
    if (str == NULL) return false;
    if (empty()) return true;
    return (strcmp(fStr, str) < 0);
}

int plString::compareTo(const plString& other, bool ignoreCase) const {
    if (ignoreCase) {
        plString s1 = *this;
        plString s2 = other;
        return strcmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return strcmp(fStr, other.fStr);
    }
}

int plString::compareTo(const char* other, bool ignoreCase) const {
    if (ignoreCase) {
        plString s1 = *this;
        plString s2 = other;
        return strcmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return strcmp(fStr, other);
    }
}

bool plString::startsWith(const plString& cmp, bool ignoreCase) const {
    if (fLen < cmp.fLen) return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::startsWith(const char* cmp, bool ignoreCase) const {
    if (fLen < strlen(cmp)) return false;
    return (left(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const plString& cmp, bool ignoreCase) const {
    if (fLen < cmp.fLen) return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plString::endsWith(const char* cmp, bool ignoreCase) const {
    if (fLen < strlen(cmp)) return false;
    return (right(strlen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

const char* plString::cstr() const { return (fStr != NULL) ? fStr : ""; }
plString::operator const char*() const { return cstr(); }

char* plString::copybuf() const {
    if (empty()) return NULL;
    char* buf = new char[fLen+1];
    strncpy(buf, fStr, fLen);
    buf[fLen] = 0;
    return buf;
}

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

long plString::find(char c) const {
    if (empty()) return -1;
    char* pos = strchr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plString::find(const char* sub) const {
    if (empty()) return -1;
    size_t len = strlen(sub);
    if (len > fLen) return -1;
    for (size_t i=0; i<(fLen - len); i++) {
        if (strncmp(fStr + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plString::find(const plString& sub) const {
    if (empty()) return -1;
    if (sub.fLen > fLen) return -1;
    for (size_t i=0; i<(fLen - sub.fLen); i++) {
        if (strncmp(fStr + i, sub.fStr, sub.fLen) == 0)
            return (long)i;
    }
    return -1;
}

long plString::rfind(char c) const {
    if (empty()) return -1;
    char* pos = strrchr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plString::rfind(const char* sub) const {
    if (empty()) return -1;
    size_t len = strlen(sub);
    if (len > fLen) return -1;
    for (size_t i=(fLen - len); i>0; i--) {
        if (strncmp(fStr + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plString::rfind(const plString& sub) const {
    if (empty()) return -1;
    if (sub.fLen > fLen) return -1;
    for (size_t i=(fLen - sub.fLen); i>0; i--) {
        if (strncmp(fStr + (i-1), sub.fStr, sub.fLen) == 0)
            return (long)(i-1);
    }
    return -1;
}

plString& plString::toUpper() {
    if (!empty()) {
        for (char* c=fStr; *c; c++)
            *c = toupper(*c);
    }
    return (*this);
}

plString& plString::toLower() {
    if (!empty()) {
        for (char* c=fStr; *c; c++)
            *c = tolower(*c);
    }
    return (*this);
}

plString plString::left(size_t num) const {
    if (num > fLen) num = fLen;
    if (num == fLen) return plString(fStr);
    char* buf = new char[num+1];
    strncpy(buf, fStr, num);
    buf[num] = 0;
    plString retn(buf);
    delete[] buf;
    return retn;
}

plString plString::right(size_t num) const {
    if (num > fLen) num = fLen;
    if (num == fLen) return plString(fStr);
    char* buf = new char[num+1];
    strncpy(buf, fStr + (fLen - num), num);
    buf[num] = 0;
    plString retn(buf);
    delete[] buf;
    return retn;
}

plString plString::mid(size_t idx, size_t num) const {
    if (idx > fLen) return plString("");
    if (idx + num > fLen) num = fLen - idx;
    char* buf = new char[num+1];
    strncpy(buf, fStr + idx, num);
    buf[num] = 0;
    plString retn(buf);
    delete[] buf;
    return retn;
}

plString plString::mid(size_t idx) const {
    return mid(idx, fLen - idx);
}

plString plString::beforeFirst(char sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return left(pos);
    else
        return plString(*this);
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
        return plString(*this);
}

long plString::toInt(int base) const {
    if (empty()) return 0;
    return strtol(fStr, NULL, base);
}

unsigned long plString::toUint(int base) const {
    if (empty()) return 0;
    return strtoul(fStr, NULL, base);
}

double plString::toFloat() const {
    if (empty()) return 0.0;
    return strtod(fStr, NULL);
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
plWString::plWString() : fStr(NULL) { }

plWString::plWString(const plWString& init) : plStringBase(init) {
    if (!init.empty()) {
        fStr = new wchar_t[fLen+1];
        wcscpy(fStr, init.fStr);
    } else {
        fStr = NULL;
    }
}

plWString::plWString(const wchar_t* init) : plStringBase() {
    if (init != NULL) {
        fLen = wcslen(init);
        if (fLen > 0) {
            fStr = new wchar_t[fLen+1];
            wcscpy(fStr, init);
        } else {
            fStr = NULL;
        }
    } else {
        fLen = 0;
        fStr = NULL;
    }
}

plWString::plWString(wchar_t c) : plStringBase() {
    fLen = 1;
    fStr = new wchar_t[2];
    fStr[0] = c;
    fStr[1] = 0;
}

plWString::~plWString() {
    if (fStr) delete[] fStr;
}

bool plWString::empty() const { return (fStr == NULL) || (fLen == 0); }

//wchar_t& plWString::operator[](size_t idx) const { return fStr[idx]; }

plWString& plWString::operator=(const plWString& other) {
    if (fStr) delete[] fStr;
    if (!other.empty()) {
        fLen = other.fLen;
        fStr = new wchar_t[fLen+1];
        wcscpy(fStr, other.fStr);
    } else {
        fLen = 0;
        fStr = NULL;
    }
    fHash = other.fHash;
    fHaveHash = other.fHaveHash;
    return (*this);
}

plWString& plWString::operator=(const wchar_t* str) {
    if (fStr) delete[] fStr;
    if (str != NULL) {
        fLen = wcslen(str);
        fStr = new wchar_t[fLen+1];
        wcscpy(fStr, str);
    } else {
        fLen = 0;
        fStr = NULL;
    }
    fHaveHash = false;
    return (*this);
}

plWString& plWString::operator=(wchar_t c) {
    if (fStr) delete[] fStr;
    fLen = 1;
    fStr = new wchar_t[2];
    fStr[0] = c;
    fStr[1] = 0;
    fHaveHash = false;
    return (*this);
}

plWString& plWString::operator+=(const plWString& other) {
    if (!other.empty()) {
        fLen += other.fLen;
        wchar_t* newStr = new wchar_t[fLen+1];
        if (empty()) {
            wcscpy(newStr, other.fStr);
            fHash = other.fHash;
            fHaveHash = other.fHaveHash;
        } else {
            swprintf(newStr, fLen+1, L"%s%s", fStr, other.fStr);
            fHaveHash = false;
        }
        if (fStr) delete[] fStr;
        fStr = newStr;
    }
    return (*this);
}

plWString& plWString::operator+=(const wchar_t* str) {
    if (str != NULL) {
        fLen += wcslen(str);
        wchar_t* newStr = new wchar_t[fLen+1];
        if (empty())
            wcscpy(newStr, str);
        else
            swprintf(newStr, fLen+1, L"%s%s", fStr, str);
        fHaveHash = false;
        if (fStr) delete[] fStr;
        fStr = newStr;
    }
    return (*this);
}

plWString& plWString::operator+=(wchar_t c) {
    fLen++;
    wchar_t* newStr = new wchar_t[fLen+1];
    if (empty()) {
        newStr[0] = c;
        newStr[1] = 0;
    } else {
        wcscpy(newStr, fStr);
        newStr[fLen-1] = c;
        newStr[fLen] = 0;
    }
    fHaveHash = false;
    if (fStr) delete[] fStr;
    fStr = newStr;
    return (*this);
}

plWString plWString::operator+(const plWString& other) {
    plWString result(*this);
    return (result += other);
}

plWString plWString::operator+(const wchar_t* str) {
    plWString result(*this);
    return (result += str);
}

plWString plWString::operator+(wchar_t c) {
    plWString result(*this);
    return (result += c);
}

bool plWString::operator==(const plWString& other) const {
    if (other.empty()) return empty();
    if (hash() != other.hash())
        return false;
    return (wcscmp(fStr, other.fStr)==0);
}

bool plWString::operator==(const wchar_t* str) const {
    if (str == NULL) return empty();
    if (hash() != hash(str))
        return false;
    return (wcscmp(fStr, str)==0);
}

bool plWString::operator!=(const plWString& other) const {
    if (other.empty()) return !empty();
    if (hash() != other.hash())
        return true;
    return (wcscmp(fStr, other.fStr)!=0);
}

bool plWString::operator!=(const wchar_t* str) const {
    if (str == NULL) return !empty();
    if (hash() != hash(str))
        return true;
    return (wcscmp(fStr, str)!=0);
}

bool plWString::operator<(const plWString& other) const {
    if (other.empty()) return false;
    if (empty()) return true;
    return (wcscmp(fStr, other.fStr) < 0);
}

bool plWString::operator<(const wchar_t* str) const {
    if (str == NULL) return false;
    if (empty()) return true;
    return (wcscmp(fStr, str) < 0);
}

int plWString::compareTo(const plWString& other, bool ignoreCase) const {
    if (ignoreCase) {
        plWString s1 = *this;
        plWString s2 = other;
        return wcscmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return wcscmp(fStr, other.fStr);
    }
}

int plWString::compareTo(const wchar_t* other, bool ignoreCase) const {
    if (ignoreCase) {
        plWString s1 = *this;
        plWString s2 = other;
        return wcscmp(s1.toUpper().cstr(), s2.toUpper().cstr());
    } else {
        return wcscmp(fStr, other);
    }
}

bool plWString::startsWith(const plWString& cmp, bool ignoreCase) const {
    if (fLen < cmp.fLen) return false;
    return (left(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::startsWith(const wchar_t* cmp, bool ignoreCase) const {
    if (fLen < wcslen(cmp)) return false;
    return (left(wcslen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::endsWith(const plWString& cmp, bool ignoreCase) const {
    if (fLen < cmp.fLen) return false;
    return (right(cmp.len()).compareTo(cmp, ignoreCase) == 0);
}

bool plWString::endsWith(const wchar_t* cmp, bool ignoreCase) const {
    if (fLen < wcslen(cmp)) return false;
    return (right(wcslen(cmp)).compareTo(cmp, ignoreCase) == 0);
}

const wchar_t* plWString::cstr() const { return (fStr != NULL) ? fStr : L""; }
plWString::operator const wchar_t*() const { return cstr(); }

wchar_t* plWString::copybuf() const {
    if (empty()) return NULL;
    wchar_t* buf = new wchar_t[fLen+1];
    wcsncpy(buf, fStr, fLen);
    buf[fLen] = 0;
    return buf;
}

unsigned int plWString::hash() const {
    if (!fHaveHash) {
        fHash = hash(fStr);
        fHaveHash = true;
    }
    return fHash;
}

unsigned int plWString::hash(const wchar_t* str) {
    // djb2 hash //
    // hopefully this works as well on wstrings as on strings... //
    unsigned int hash = 5381;
    while (*str++)
        hash = ((hash << 5) + hash) ^ *str;
    return hash;
}

long plWString::find(wchar_t c) const {
    if (empty()) return -1;
    wchar_t* pos = wcschr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plWString::find(const wchar_t* sub) const {
    if (empty()) return -1;
    size_t len = wcslen(sub);
    if (len > fLen) return -1;
    for (size_t i=0; i<(fLen - len); i++) {
        if (wcsncmp(fStr + i, sub, len) == 0)
            return (long)i;
    }
    return -1;
}

long plWString::find(const plWString& sub) const {
    if (empty()) return -1;
    if (sub.fLen > fLen) return -1;
    for (size_t i=0; i<(fLen - sub.fLen); i++) {
        if (wcsncmp(fStr + i, sub.fStr, sub.fLen) == 0)
            return (long)i;
    }
    return -1;
}

long plWString::rfind(wchar_t c) const {
    if (empty()) return -1;
    wchar_t* pos = wcsrchr(fStr, c);
    if (pos != NULL)
        return (long)(pos - fStr);
    return -1;
}

long plWString::rfind(const wchar_t* sub) const {
    if (empty()) return -1;
    size_t len = wcslen(sub);
    if (len > fLen) return -1;
    for (size_t i=(fLen - len); i>0; i--) {
        if (wcsncmp(fStr + (i-1), sub, len) == 0)
            return (long)(i-1);
    }
    return -1;
}

long plWString::rfind(const plWString& sub) const {
    if (empty()) return -1;
    if (sub.fLen > fLen) return -1;
    for (size_t i=(fLen - sub.fLen); i>0; i--) {
        if (wcsncmp(fStr + (i-1), sub.fStr, sub.fLen) == 0)
            return (long)(i-1);
    }
    return -1;
}

plWString& plWString::toUpper() {
    if (!empty()) {
        for (wchar_t* c=fStr; *c; c++)
            *c = towupper(*c);
    }
    return (*this);
}

plWString& plWString::toLower() {
    if (!empty()) {
        for (wchar_t* c=fStr; *c; c++)
            *c = towlower(*c);
    }
    return (*this);
}

plWString plWString::left(size_t num) const {
    if (num > fLen) num = fLen;
    if (num == fLen) return plWString(fStr);
    wchar_t* buf = new wchar_t[num+1];
    wcsncpy(buf, fStr, num);
    buf[num] = 0;
    plWString retn(buf);
    delete[] buf;
    return retn;
}

plWString plWString::right(size_t num) const {
    if (num > fLen) num = fLen;
    if (num == fLen) return plWString(fStr);
    wchar_t* buf = new wchar_t[num+1];
    wcsncpy(buf, fStr + (fLen - num), num);
    buf[num] = 0;
    plWString retn(buf);
    delete[] buf;
    return retn;
}

plWString plWString::mid(size_t idx, size_t num) const {
    if (idx > fLen) return plWString(L"");
    if (idx + num > fLen) num = fLen - idx;
    wchar_t* buf = new wchar_t[num+1];
    wcsncpy(buf, fStr + idx, num);
    buf[num] = 0;
    plWString retn(buf);
    delete[] buf;
    return retn;
}

plWString plWString::mid(size_t idx) const {
    return mid(idx, fLen - idx);
}

plWString plWString::beforeFirst(wchar_t sep) const {
    long pos = find(sep);
    if (pos >= 0)
        return left(pos);
    else
        return plWString(*this);
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
        return plWString(*this);
}

long plWString::toInt(int base) const {
    if (empty()) return 0;
    return wcstol(fStr, NULL, base);
}

unsigned long plWString::toUint(int base) const {
    if (empty()) return 0;
    return wcstoul(fStr, NULL, base);
}

double plWString::toFloat() const {
    if (empty()) return 0.0;
    return wcstod(fStr, NULL);
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


/**************************** Conversion Functions ****************************/
plString hsWStringToString(const wchar_t* str) {
    size_t cnvLen = wcstombs(NULL, str, 0);
    if (cnvLen > 0 && cnvLen != (size_t)(-1)) {
        char* buf = new char[cnvLen+1];
        wcstombs(buf, str, cnvLen+1);
        plString result = buf;
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
        plWString result = buf;
        delete[] buf;
        return result;
    } else {
        return L"";
    }
}
