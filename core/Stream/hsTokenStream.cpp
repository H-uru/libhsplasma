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

/* hsTokenStream */
hsTokenStream::hsTokenStream(const ST::string& filename)
    : fIOwnStream(true), fInComment(-1)
{
    fStream = new hsFileStream();
    ((hsFileStream*)fStream)->open(filename, fmRead);
}

hsTokenStream::~hsTokenStream()
{
    if (fIOwnStream)
        delete fStream;
}

ST::string hsTokenStream::next()
{
    if (hasNext()) {
        ST::string s = fLineTokens.front();
        fLineTokens.pop();
        return s;
    }
    return "";
}

bool hsTokenStream::hasNext()
{
    if (fLineTokens.empty())
        getLine();
    return !(fLineTokens.empty());
}

ST::string hsTokenStream::peekNext()
{
    if (hasNext())
        return fLineTokens.front();
    return ST::string();
}

void hsTokenStream::setDelimiters(const char* delims)
{
    fDelims = std::vector<char>(delims, delims + strlen(delims));
}

void hsTokenStream::setCommentMarkers(const std::vector<Region>& comments)
{
    fCommentMarkers = comments;
}

void hsTokenStream::setStringMarkers(const std::vector<Region>& strMarkers)
{
    fStringMarkers = strMarkers;
}

void hsTokenStream::getLine()
{
    while (!fLineTokens.empty())
        fLineTokens.pop();
    if (fStream->eof())
        return;

    ST::string line = fStream->readLine() + "\n";
    size_t beg=0, end=0;
    int tokType;
    while (end < line.size()) {
        beg = end;
        if (fInComment == -1) {
            while (beg < line.size() && getCharType(line[beg]) == kCharNone)
                beg++;
        }
        for (auto mark = fStringMarkers.begin(); mark != fStringMarkers.end(); ++mark) {
            if (line.substr(beg).starts_with(mark->fStart)) {
                long strEnd = line.substr(beg + mark->fStart.size()).find(mark->fEnd);
                if (strEnd == -1)
                    throw hsBadParamException(__FILE__, __LINE__);
                unsigned long markerLen = mark->fStart.size() + mark->fEnd.size();
                fLineTokens.push(line.substr(beg, strEnd + markerLen));
                beg += strEnd + markerLen;
            }
        }
        for (size_t i=0; i<fCommentMarkers.size(); i++) {
            if (fInComment == -1 && line.substr(beg).starts_with(fCommentMarkers[i].fStart)) {
                fInComment = i;
                beg += fCommentMarkers[i].fStart.size();
            }
        }
        if (fInComment == -1) {
            while (beg < line.size() && getCharType(line[beg]) == kCharNone)
                beg++;
        }
        end = beg;
        if (fInComment != -1) {
            tokType = kCharComment;
            while (end < line.size() && fInComment != -1) {
                if (line.substr(end).starts_with(fCommentMarkers[fInComment].fEnd)) {
                    end += fCommentMarkers[fInComment].fEnd.size();
                    fInComment = -1;
                } else {
                    end++;
                }
            }
        } else {
            tokType = getCharType(line[beg]);
            while (end < line.size() && getCharType(line[end]) == tokType) {
                end++;
                if (tokType == kCharDelim) break; // Only return one Delimiter
            }
            if (end != beg)
                fLineTokens.push(line.substr(beg, end-beg));
        }
    }

    // Check for a blank line and skip it
    if (fLineTokens.empty())
        getLine();
}

int hsTokenStream::getCharType(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
        return kCharNone;
    for (auto dch = fDelims.begin(); dch != fDelims.end(); ++dch) {
        if (ch == *dch)
            return kCharDelim;
    }
    return kCharIdent;
}
