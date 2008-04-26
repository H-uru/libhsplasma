#ifndef _PFPRCPARSER_H
#define _PFPRCPARSER_H

#include "CoreLib/hsStream.h"
#include "CoreLib/hsTokenStream.h"
#include <map>

DllClass pfPrcTag {
protected:
    plString fName;
    std::map<plString, plString> fParams;
    pfPrcTag* fNextSibling;
    pfPrcTag* fFirstChild;
    plString fContents;
    bool fIsEndTag;

    pfPrcTag();
    ~pfPrcTag();
    
    friend class pfPrcParser;

public:
    const plString& getName() const;
    const plString& getParam(const plString& key, const plString& def) const;
    const plString& getContents() const;
    const pfPrcTag* getFirstChild() const;
    const pfPrcTag* getNextSibling() const;
    bool hasChildren() const;
    bool hasNextSibling() const;
    bool isEndTag() const;
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

#endif
