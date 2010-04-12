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

#include "hsTokenStream.h"
#include <cstring>

/* hsTokenStream::Region */
hsTokenStream::Region::Region(const plString& start, const plString& end)
                     : fStart(start), fEnd(end) { }


/* hsTokenStream */
hsTokenStream::hsTokenStream(hsStream* stream)
             : fStream(stream), fIOwnStream(false), fInComment(-1) { }

hsTokenStream::hsTokenStream(const plString& filename)
             : fIOwnStream(true), fInComment(-1) {
    fStream = new hsFileStream();
    ((hsFileStream*)fStream)->open(filename, fmRead);
}

hsTokenStream::~hsTokenStream() {
    if (fIOwnStream)
        delete fStream;
}

plString hsTokenStream::next() {
    if (hasNext())
        return fLineTokens.pop();
    return "";
}

bool hsTokenStream::hasNext() {
    if (fLineTokens.empty())
        getLine();
    return !(fLineTokens.empty());
}

plString hsTokenStream::peekNext() {
    if (hasNext())
        return fLineTokens.top();
    return "";
}

void hsTokenStream::setDelimiters(const char* delims) {
    size_t nDelims = strlen(delims);
    fDelims.setSize(nDelims);
    for (size_t i=0; i<nDelims; i++)
        fDelims[i] = delims[i];
}

void hsTokenStream::setCommentMarkers(const hsTArray<Region>& comments) {
    fCommentMarkers.setSize(comments.getSize());
    for (size_t i=0; i<fCommentMarkers.getSize(); i++)
        fCommentMarkers[i] = comments[i];
}

void hsTokenStream::setStringMarkers(const hsTArray<Region>& strMarkers) {
    fStringMarkers.setSize(strMarkers.getSize());
    for (size_t i=0; i<fStringMarkers.getSize(); i++)
        fStringMarkers[i] = strMarkers[i];
}

void hsTokenStream::getLine() {
    fLineTokens.clear();
    if (fStream->eof())
        return;

    plString line = fStream->readLine() + "\n";
    size_t beg=0, end=0;
    int tokType;
    while (end < line.len()) {
        beg = end;
        if (fInComment == -1) {
            while (beg < line.len() && getCharType(line[beg]) == kCharNone)
                beg++;
        }
        for (size_t i=0; i<fStringMarkers.getSize(); i++) {
            if (line.mid(beg).startsWith(fStringMarkers[i].fStart)) {
                long strEnd = line.mid(beg + fStringMarkers[i].fStart.len()).find(fStringMarkers[i].fEnd);
                if (strEnd == -1)
                    throw hsBadParamException(__FILE__, __LINE__);
                unsigned long markerLen = fStringMarkers[i].fStart.len() + fStringMarkers[i].fEnd.len();
                fLineTokens.rpush(line.mid(beg, strEnd + markerLen));
                beg += strEnd + markerLen;
            }
        }
        for (size_t i=0; i<fCommentMarkers.getSize(); i++) {
            if (fInComment == -1 && line.mid(beg).startsWith(fCommentMarkers[i].fStart)) {
                fInComment = i;
                beg += fCommentMarkers[i].fStart.len();
            }
        }
        if (fInComment == -1) {
            while (beg < line.len() && getCharType(line[beg]) == kCharNone)
                beg++;
        }
        end = beg;
        if (fInComment != -1) {
            tokType = kCharComment;
            while (end < line.len() && fInComment != -1) {
                if (line.mid(end).startsWith(fCommentMarkers[fInComment].fEnd)) {
                    end += fCommentMarkers[fInComment].fEnd.len();
                    fInComment = -1;
                } else {
                    end++;
                }
            }
        } else {
            tokType = getCharType(line[beg]);
            while (end < line.len() && getCharType(line[end]) == tokType) {
                end++;
                if (tokType == kCharDelim) break; // Only return one Delimiter
            }
            if (end != beg)
                fLineTokens.rpush(line.mid(beg, end-beg));
        }
    }

    // Check for a blank line and skip it
    if (fLineTokens.empty())
        getLine();
}

int hsTokenStream::getCharType(const char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
        return kCharNone;
    for (size_t i=0; i<fDelims.getSize(); i++)
        if (ch == fDelims[i]) return kCharDelim;
    return kCharIdent;
}
