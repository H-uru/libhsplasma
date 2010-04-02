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
    plString getName() const { return fName; }
    plString getParam(const plString& key, const plString& def) const;
    const hsTList<plString>& getContents() const { return fContents; }
    const pfPrcTag* getFirstChild() const { return fFirstChild; }
    const pfPrcTag* getNextSibling() const { return fNextSibling; }
    bool hasChildren() const { return (fFirstChild != NULL); }
    bool hasNextSibling() const { return (fNextSibling != NULL); }
    bool isEndTag() const { return fIsEndTag; }
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
    const pfPrcTag* getRoot() const { return fRootTag; }

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
