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

#include <string_theory/st_string.h>
#include <exception>

class PLASMA_DLL hsException : public std::exception {
protected:
    ST::string fWhat;
    const char* fFile;
    unsigned long fLine;

public:
    hsException(const char* file, unsigned long line) HS_NOEXCEPT
        : fWhat("Undefined Plasma Exception"), fFile(file), fLine(line) { }
    virtual ~hsException() HS_NOEXCEPT { }

    hsException& operator=(const hsException& other) HS_NOEXCEPT {
        fWhat = other.fWhat;
        return *this;
    }

    const char* what() const HS_NOEXCEPT HS_OVERRIDE { return fWhat.c_str(); }
    const char* File() const HS_NOEXCEPT { return fFile; }
    unsigned long Line() const HS_NOEXCEPT { return fLine; }

protected:
    hsException(const ST::string& w, const char* file, unsigned long line) HS_NOEXCEPT
        : fWhat(w), fFile(file), fLine(line) { }
};

class PLASMA_DLL hsNotImplementedException : public hsException {
public:
    hsNotImplementedException(const char* file, unsigned long line,
                              const ST::string& feature = ST::string::null) HS_NOEXCEPT
        : hsException(file, line)
    {
        if (feature.is_empty())
            fWhat = "Not implemented";
        else
            fWhat = ST::string("`") + feature + "' not implemented";
    }
};

class PLASMA_DLL hsBadParamException : public hsException {
public:
    hsBadParamException(const char* file, unsigned long line,
                        const ST::string& details = ST::string::null) HS_NOEXCEPT
        : hsException(file, line)
    {
        fWhat = "Bad parameter";
        if (!details.is_empty())
            fWhat += ST::string(": ") + details;
    }
};

class PLASMA_DLL hsOutOfBoundsException : public hsException {
public:
    hsOutOfBoundsException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(file, line) { fWhat = "Out of bounds"; }
};

class PLASMA_DLL hsBadVersionException : public hsException {
public:
    hsBadVersionException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(file, line) { fWhat = "Unknown Plasma version"; }
};

class PLASMA_DLL hsVersionMismatchException : public hsException {
public:
    hsVersionMismatchException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(file, line) { fWhat = "Plasma Versions don't match"; }
};

#endif
