/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HSEXCEPTIONS_H
#define _HSEXCEPTIONS_H

#include "Util/plString.h"
#include <exception>

class PLASMA_DLL hsException : public std::exception {
protected:
    plString fWhat;
    const char* fFile;
    unsigned long fLine;

public:
    hsException(const char* file, unsigned long line) throw();
    hsException(const hsException& e) throw();
    virtual ~hsException() throw() { }

    hsException& operator=(const hsException& other) throw();

    virtual const char* what() const throw() { return fWhat; }
    const char* File() const throw() { return fFile; }
    unsigned long Line() const throw() { return fLine; }

protected:
    hsException(const plString& w, const char* file,
                unsigned long line) throw();
};

class PLASMA_DLL hsNotImplementedException : public hsException {
public:
    hsNotImplementedException(const char* file, unsigned long line,
                              const char* feature = NULL) throw();
};

class PLASMA_DLL hsBadParamException : public hsException {
public:
    hsBadParamException(const char* file, unsigned long line,
                        const char* details = NULL) throw();
};

class PLASMA_DLL hsOutOfBoundsException : public hsException {
public:
    hsOutOfBoundsException(const char* file, unsigned long line) throw();
};

class PLASMA_DLL hsBadVersionException : public hsException {
public:
    hsBadVersionException(const char* file, unsigned long line) throw();
};

class PLASMA_DLL hsVersionMismatchException : public hsException {
public:
    hsVersionMismatchException(const char* file, unsigned long line) throw();
};

#endif
