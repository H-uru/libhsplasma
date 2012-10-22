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

#ifndef _PFPRCPARSER_H
#define _PFPRCPARSER_H

#include "hsStream.h"
#include "hsTokenStream.h"
#include <map>
#include <list>

class PLASMA_DLL pfPrcTag {
protected:
    plString fName;
    std::map<plString, plString> fParams;
    pfPrcTag* fNextSibling;
    pfPrcTag* fFirstChild;
    std::list<plString> fContents;
    bool fIsEndTag;

    pfPrcTag() : fNextSibling(NULL), fFirstChild(NULL), fIsEndTag(false) { }
    ~pfPrcTag();

    pfPrcTag* Destroy();

    friend class pfPrcParser;

public:
    plString getName() const { return fName; }
    plString getParam(const plString& key, const plString& def) const;
    const std::list<plString>& getContents() const { return fContents; }
    const pfPrcTag* getFirstChild() const { return fFirstChild; }
    const pfPrcTag* getNextSibling() const { return fNextSibling; }
    bool hasChildren() const { return (fFirstChild != NULL); }
    bool hasNextSibling() const { return (fNextSibling != NULL); }
    bool isEndTag() const { return fIsEndTag; }
    bool hasParam(const plString& key) const;
    size_t countChildren() const;

    void readHexStream(size_t maxLen, unsigned char* buf) const;
};


class PLASMA_DLL pfPrcParser {
private:
    pfPrcTag* fRootTag;

public:
    pfPrcParser() : fRootTag(NULL) { }
    ~pfPrcParser();

    void read(hsStream* S);
    const pfPrcTag* getRoot() const { return fRootTag; }

private:
    pfPrcTag* readTag(hsTokenStream* tok);
};


class PLASMA_DLL pfPrcParseException : public hsException {
public:
    pfPrcParseException(const char* file, unsigned long line,
                        const char* msg, ...) throw();
};


class PLASMA_DLL pfPrcTagException : public pfPrcParseException {
public:
    pfPrcTagException(const char* file, unsigned long line,
                      const char* tag) throw();
};

#endif
