#include "pfPrcParser.h"
#include "Debug/plDebug.h"
#include <cstdarg>

/* pfPrcTag */
pfPrcTag::pfPrcTag()
        : fNextSibling(NULL), fFirstChild(NULL), fIsEndTag(false) { }

pfPrcTag::~pfPrcTag() {
    /* This can cause a stack overflow if there are lots of tags
     * (e.g., hsGBufferGroup's verts.  For now, use Destroy() */

    //if (fNextSibling != NULL)
    //    delete fNextSibling;
    //if (fFirstChild != NULL)
    //    delete fFirstChild;
}

pfPrcTag* pfPrcTag::Destroy() {
    while (fFirstChild != NULL)
        fFirstChild = fFirstChild->Destroy();
    pfPrcTag* next = fNextSibling;
    delete this;
    return next;
}

const plString& pfPrcTag::getName() const { return fName; }
const hsTList<plString>& pfPrcTag::getContents() const { return fContents; }
const pfPrcTag* pfPrcTag::getFirstChild() const { return fFirstChild; }
const pfPrcTag* pfPrcTag::getNextSibling() const { return fNextSibling; }
bool pfPrcTag::hasChildren() const { return (fFirstChild != NULL); }
bool pfPrcTag::hasNextSibling() const { return (fNextSibling != NULL); }
bool pfPrcTag::isEndTag() const { return fIsEndTag; }

const plString& pfPrcTag::getParam(const plString& key, const plString& def) const {
    std::map<plString, plString>::const_iterator f = fParams.find(key);
    if (f == fParams.end())
        return def;
    else
        return f->second;
}

bool pfPrcTag::hasParam(const plString& key) const {
    std::map<plString, plString>::const_iterator f = fParams.find(key);
    return (f != fParams.end());
}

size_t pfPrcTag::countChildren() const {
    const pfPrcTag* childPtr = fFirstChild;
    size_t nChildren = 0;
    while (childPtr != NULL) {
        nChildren++;
        childPtr = childPtr->fNextSibling;
    }
    return nChildren;
}

void pfPrcTag::readHexStream(size_t maxLen, unsigned char* buf) const {
    hsTList<plString> bytes = getContents();
    size_t i=0;
    while (!bytes.empty() && i<maxLen)
        buf[i++] = bytes.pop().toUint(16);
}


/* pfPrcParser */
pfPrcParser::pfPrcParser() : fRootTag(NULL) { }

pfPrcParser::~pfPrcParser() {
    if (fRootTag != NULL)
        fRootTag->Destroy();
}

void pfPrcParser::read(hsStream* S) {
    hsTokenStream* tok = new hsTokenStream(S);
    hsTArray<hsTokenStream::Region> commentMarkers;
    hsTArray<hsTokenStream::Region> stringMarkers;
    commentMarkers.append(hsTokenStream::Region("<!--", "-->"));
    commentMarkers.append(hsTokenStream::Region("<?", "?>"));  // we don't really care about the XML info :P
    stringMarkers.append(hsTokenStream::Region("\"", "\""));
    stringMarkers.append(hsTokenStream::Region("'", "'"));
    tok->setDelimiters("<>/=[](),;");
    tok->setCommentMarkers(commentMarkers);
    tok->setStringMarkers(stringMarkers);

    fRootTag = readTag(tok);
    delete tok;
}

const pfPrcTag* pfPrcParser::getRoot() const { return fRootTag; }

pfPrcTag* pfPrcParser::readTag(hsTokenStream* tok) {
    if (!tok->hasNext())
        return NULL;
    
    plString str = tok->next();
    while ((str != "<") && tok->hasNext()) {
        plDebug::Warning("WARN: Ignoring extraneous token %s", str.cstr());
        str = tok->next();
    }
    if (!tok->hasNext())
        throw hsBadParamException(__FILE__, __LINE__);
    
    pfPrcTag* tag = new pfPrcTag();
    if (tok->peekNext() == "/") {
        tag->fIsEndTag = true;
        tok->next();
    }
    tag->fName = tok->next();

    if (tag->fIsEndTag) {
        str = tok->next();
        while ((str != ">") && tok->hasNext()) {
            plDebug::Warning("WARN: Ignoring extraneous token %s", str.cstr());
            str = tok->next();
        }
        return tag;
    }

    str = tok->next();
    while (str != "/" && str != ">") {
        plString tmp = tok->next();
        if (tmp != "=") {
            throw pfPrcParseException(__FILE__, __LINE__,
                    "Unexpected '%s', expected '='", tmp.cstr());
        }
        tmp = tok->next();
        if (tmp.startsWith("\""))
            tmp = tmp.mid(1, tmp.len() - 2);
        else if (tmp.startsWith("'"))
            tmp = tmp.mid(1, tmp.len() - 2);
        tag->fParams[str] = tmp;
        str = tok->next();
    }

    if (str == "/") {
        // Closed tag; no children
        str = tok->next();
        while ((str != ">") && tok->hasNext()) {
            plDebug::Warning("WARN: Ignoring extraneous token %s", str.cstr());
            str = tok->next();
        }
        return tag;
    }

    while (tok->peekNext() != "<")
        tag->fContents.rpush(tok->next());

    pfPrcTag* childPtr = readTag(tok);
    if (!childPtr->fIsEndTag)
        tag->fFirstChild = childPtr;
    while (!childPtr->isEndTag()) {
        pfPrcTag* next = readTag(tok);
        if (!next->isEndTag())
            childPtr->fNextSibling = next;
        childPtr = next;
    }

    if (childPtr->fName != tag->fName) {
        delete childPtr;
        throw pfPrcParseException(__FILE__, __LINE__,
                "Closing <%s> tag, which isn't open", childPtr->fName.cstr());
    }
    delete childPtr;
    return tag;
}


/* pfPrcParseException */
pfPrcParseException::pfPrcParseException(const char* file, unsigned long line,
                                         const char* msg, ...) throw()
                   : hsException(file, line) {
    if (msg == NULL) {
        fWhat = "Unknown Parse Error";
    } else {
        va_list argptr;
        va_start(argptr, msg);
        plString str = plString::FormatV(msg, argptr);
        va_end(argptr);
        fWhat = plString("Parse Error: ") + str;
    }
}

/* pfPrcTagException */
pfPrcTagException::pfPrcTagException(const char* file, unsigned long line,
                                     const char* tag) throw()
                 : pfPrcParseException(file, line, NULL) {
    if (tag == NULL)
        fWhat = "Unexpected tag";
    else
        fWhat = plString("Unexpected tag: ") + tag;
}
