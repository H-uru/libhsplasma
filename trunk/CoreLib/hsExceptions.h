#ifndef _HSEXCEPTIONS_H
#define _HSEXCEPTIONS_H

#include <exception>
#include "plString.h"

DllClass hsException : public std::exception {
protected:
    plString fWhat;
    const char* fFile;
    unsigned long fLine;

public:
    hsException(const char* file, unsigned long line) throw();
    hsException(const hsException& e) throw();
    virtual ~hsException() throw();

    hsException& operator=(const hsException& other) throw();
    virtual const char* what() const throw();

    const char* File() const throw();
    unsigned long Line() const throw();

protected:
    hsException(const plString& w, const char* file,
                unsigned long line) throw();
};

DllClass hsNotImplementedException : public hsException {
public:
    hsNotImplementedException(const char* file, unsigned long line,
                              const char* feature = NULL) throw();
};

DllClass hsBadParamException : public hsException {
public:
    hsBadParamException(const char* file, unsigned long line) throw();
};

DllClass hsOutOfBoundsException : public hsException {
public:
    hsOutOfBoundsException(const char* file, unsigned long line) throw();
};

DllClass hsBadVersionException : public hsException {
public:
    hsBadVersionException(const char* file, unsigned long line) throw();
};

DllClass hsVersionMismatchException : public hsException {
public:
    hsVersionMismatchException(const char* file, unsigned long line) throw();
};

#endif
