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

#include <string_theory/string>
#include <exception>

class hsException : public std::exception
{
protected:
    ST::string fWhat;
    const char* fFile;
    unsigned long fLine;

public:
    inline hsException(const char* file, unsigned long line) HS_NOEXCEPT
        : fWhat("Undefined Plasma Exception"), fFile(file), fLine(line) { }

    inline hsException& operator=(const hsException& other) HS_NOEXCEPT
    {
        fWhat = other.fWhat;
        return *this;
    }

    inline const char* what() const HS_NOEXCEPT HS_OVERRIDE { return fWhat.c_str(); }
    inline const char* File() const HS_NOEXCEPT { return fFile; }
    inline unsigned long Line() const HS_NOEXCEPT { return fLine; }

protected:
    inline hsException(const ST::string& w, const char* file, unsigned long line) HS_NOEXCEPT
        : fWhat(w), fFile(file), fLine(line) { }
};

class hsNotImplementedException : public hsException {
public:
    inline hsNotImplementedException(const char* file, unsigned long line,
                                     const ST::string& feature = {}) HS_NOEXCEPT
        : hsException(file, line)
    {
        if (feature.empty())
            fWhat = ST_LITERAL("Not implemented");
        else
            fWhat = ST_LITERAL("`") + feature + ST_LITERAL("' not implemented");
    }
};

class hsBadParamException : public hsException {
public:
    inline hsBadParamException(const char* file, unsigned long line,
                               const ST::string& details = {}) HS_NOEXCEPT
        : hsException(ST_LITERAL("Bad parameter"), file, line)
    {
        if (!details.empty())
            fWhat += ST_LITERAL(": ") + details;
    }
};

class hsOutOfBoundsException : public hsException {
public:
    inline hsOutOfBoundsException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(ST_LITERAL("Out of bounds"), file, line) { }
};

class hsBadVersionException : public hsException {
public:
    inline hsBadVersionException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(ST_LITERAL("Unknown Plasma version"), file, line) { }
};

class hsVersionMismatchException : public hsException {
public:
    inline hsVersionMismatchException(const char* file, unsigned long line) HS_NOEXCEPT
        : hsException(ST_LITERAL("Plasma Versions don't match"), file, line) { }
};

#endif
