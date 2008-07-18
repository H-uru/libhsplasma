#ifndef _PFPRCPARSER_H
#define _PFPRCPARSER_H

#include "hsStream.h"
#include "hsTokenStream.h"
#include "Util/hsTList.hpp"
#include <map>

DllClass pfPrcTag {
protected:
    plString fName;
    std::map<plString, plString> fParams;
    pfPrcTag* fNextSibling;
    pfPrcTag* fFirstChild;
    hsTList<plString> fContents;
    bool fIsEndTag;

    pfPrcTag();
    ~pfPrcTag();

    pfPrcTag* Destroy();
    
    friend class pfPrcParser;

public:
    const plString& getName() const;
    const plString& getParam(const plString& key, const plString& def) const;
    const hsTList<plString>& getContents() const;
    const pfPrcTag* getFirstChild() const;
    const pfPrcTag* getNextSibling() const;
    bool hasChildren() const;
    bool hasNextSibling() const;
    bool isEndTag() const;
    bool hasParam(const plString& key) const;
    size_t countChildren() const;

    void readHexStream(size_t maxLen, unsigned char* buf) const;
};

DllClass pfPrcParser {
private:
    pfPrcTag* fRootTag;

public:
    pfPrcParser();
    ~pfPrcParser();

    void read(hsStream* S);
    const pfPrcTag* getRoot() const;

private:
    pfPrcTag* readTag(hsTokenStream* tok);
};

DllClass pfPrcParseException : public hsException {
public:
    pfPrcParseException(const char* file, unsigned long line,
                        const char* msg, ...) throw();
};

DllClass pfPrcTagException : public pfPrcParseException {
public:
    pfPrcTagException(const char* file, unsigned long line,
                      const char* tag) throw();
};

#endif
