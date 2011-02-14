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

#ifndef _HSTOKENSTREAM_H
#define _HSTOKENSTREAM_H

#include "hsStream.h"
#include "Util/hsTList.hpp"
#include "Util/hsTArray.hpp"

class PLASMA_DLL hsTokenStream {
public:
    struct PLASMA_DLL Region {
        plString fStart;
        plString fEnd;

        Region(const plString& start, const plString& end);
        Region() { }
    };

protected:
    enum { kCharNone, kCharIdent, kCharDelim, kCharString, kCharComment };

    hsStream* fStream;
    bool fIOwnStream;
    hsTList<plString> fLineTokens;
    hsTArray<char> fDelims;
    hsTArray<Region> fCommentMarkers;
    hsTArray<Region> fStringMarkers;
    int fInComment;

public:
    hsTokenStream(hsStream* stream);
    hsTokenStream(const plString& filename);
    ~hsTokenStream();

    plString next();
    bool hasNext();
    plString peekNext();

    void setDelimiters(const char* delims);
    void setCommentMarkers(const hsTArray<Region>& comments);
    void setStringMarkers(const hsTArray<Region>& strMarkers);

protected:
    void getLine();
    int getCharType(const char ch);
};

#endif
