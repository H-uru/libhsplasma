#ifndef _HSTOKENSTREAM_H
#define _HSTOKENSTREAM_H

#include "hsStream.h"
#include "hsTList.hpp"
#include "hsTArray.hpp"

DllClass hsTokenStream {
public:
    DllStruct Region {
        plString fStart;
        plString fEnd;

        Region(const plString& start, const plString& end);
        Region();
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
