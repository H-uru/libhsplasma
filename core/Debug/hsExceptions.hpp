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
    hsException(const char* file, unsigned long line) throw()
        : fWhat("Undefined Plasma Exception"), fFile(file), fLine(line) { }
    virtual ~hsException() throw() { }

    hsException& operator=(const hsException& other) throw() {
        fWhat = other.fWhat;
        return *this;
    }

    const char* what() const throw() HS_OVERRIDE { return fWhat; }
    const char* File() const throw() { return fFile; }
    unsigned long Line() const throw() { return fLine; }

protected:
    hsException(const plString& w, const char* file, unsigned long line) throw()
        : fWhat(w), fFile(file), fLine(line) { }
};

class PLASMA_DLL hsNotImplementedException : public hsException {
public:
    hsNotImplementedException(const char* file, unsigned long line,
                              const char* feature = NULL) throw()
        : hsException(file, line)
    {
        if (feature == NULL)
            fWhat = "Not implemented";
        else
            fWhat = plString("`") + feature + "' not implemented";
    }
};

class PLASMA_DLL hsBadParamException : public hsException {
public:
    hsBadParamException(const char* file, unsigned long line,
                        const char* details = NULL) throw()
        : hsException(file, line)
    {
        fWhat = "Bad parameter";
        if (details != NULL)
            fWhat += plString(": ") + details;
    }
};

class PLASMA_DLL hsOutOfBoundsException : public hsException {
public:
    hsOutOfBoundsException(const char* file, unsigned long line) throw()
        : hsException(file, line) { fWhat = "Out of bounds"; }
};

class PLASMA_DLL hsBadVersionException : public hsException {
public:
    hsBadVersionException(const char* file, unsigned long line) throw()
        : hsException(file, line) { fWhat = "Unknown Plasma version"; }
};

class PLASMA_DLL hsVersionMismatchException : public hsException {
public:
    hsVersionMismatchException(const char* file, unsigned long line) throw()
        : hsException(file, line) { fWhat = "Plasma Versions don't match"; }
};

#endif
