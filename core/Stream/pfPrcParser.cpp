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

#include "pfPrcParser.h"
#include "Debug/plDebug.h"
#include <cstdarg>

static ST::string xmlUnescape(const ST::string& text)
{
    return text.replace("&lt;", "<").replace("&gt;", ">")
               .replace("&quot;", "\"").replace("&apos;", "'")
               .replace("&amp;", "&");
}

/* pfPrcTag */
pfPrcTag::~pfPrcTag()
{
    /* This can cause a stack overflow if there are lots of tags
     * (e.g., hsGBufferGroup's verts.  For now, use Destroy() */

    //delete fNextSibling;
    //delete fFirstChild;
}

pfPrcTag* pfPrcTag::Destroy()
{
    while (fFirstChild)
        fFirstChild = fFirstChild->Destroy();
    pfPrcTag* next = fNextSibling;
    delete this;
    return next;
}

ST::string pfPrcTag::getParam(const ST::string& key, const ST::string& def) const
{
    std::map<ST::string, ST::string>::const_iterator f = fParams.find(key);
    if (f == fParams.end())
        return def;
    else
        return xmlUnescape(f->second);
}

bool pfPrcTag::hasParam(const ST::string& key) const
{
    std::map<ST::string, ST::string>::const_iterator f = fParams.find(key);
    return (f != fParams.end());
}

size_t pfPrcTag::countChildren() const
{
    const pfPrcTag* childPtr = fFirstChild;
    size_t nChildren = 0;
    while (childPtr) {
        nChildren++;
        childPtr = childPtr->fNextSibling;
    }
    return nChildren;
}

void pfPrcTag::readHexStream(size_t maxLen, unsigned char* buf) const
{
    std::list<ST::string> bytes = getContents();
    size_t i=0;
    auto iter = bytes.begin();
    while (iter != bytes.end() && i<maxLen)
        buf[i++] = (*iter++).to_uint(16);
}


/* pfPrcParser */
pfPrcParser::~pfPrcParser()
{
    if (fRootTag)
        fRootTag->Destroy();
}

void pfPrcParser::read(hsStream* S)
{
    hsTokenStream* tok = new hsTokenStream(S);
    std::vector<hsTokenStream::Region> commentMarkers;
    std::vector<hsTokenStream::Region> stringMarkers;
    commentMarkers.push_back(hsTokenStream::Region("<!--", "-->"));
    commentMarkers.push_back(hsTokenStream::Region("<?", "?>"));  // we don't really care about the XML info :P
    stringMarkers.push_back(hsTokenStream::Region("\"", "\""));
    stringMarkers.push_back(hsTokenStream::Region("'", "'"));
    tok->setDelimiters("<>/=[](),;");
    tok->setCommentMarkers(commentMarkers);
    tok->setStringMarkers(stringMarkers);

    fRootTag = readTag(tok);
    delete tok;
}

pfPrcTag* pfPrcParser::readTag(hsTokenStream* tok)
{
    if (!tok->hasNext())
        return nullptr;

    ST::string str = tok->next();
    while ((str != "<") && tok->hasNext()) {
        plDebug::Warning("WARN: Ignoring extraneous token {}", str);
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
            plDebug::Warning("WARN: Ignoring extraneous token {}", str);
            str = tok->next();
        }
        return tag;
    }

    str = tok->next();
    while (str != "/" && str != ">") {
        ST::string tmp = tok->next();
        if (tmp != "=") {
            throw pfPrcParseException(__FILE__, __LINE__,
                    ST::format("Unexpected '{}', expected '='", tmp).c_str());
        }
        tmp = tok->next();
        if (tmp.starts_with("\""))
            tmp = tmp.substr(1, tmp.size() - 2);
        else if (tmp.starts_with("'"))
            tmp = tmp.substr(1, tmp.size() - 2);
        tag->fParams[str] = tmp;
        str = tok->next();
    }

    if (str == "/") {
        // Closed tag; no children
        str = tok->next();
        while ((str != ">") && tok->hasNext()) {
            plDebug::Warning("WARN: Ignoring extraneous token {}", str);
            str = tok->next();
        }
        return tag;
    }

    while (tok->peekNext() != "<")
        tag->fContents.push_back(xmlUnescape(tok->next()));

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
        ST::string name = childPtr->fName;
        delete childPtr;
        throw pfPrcParseException(__FILE__, __LINE__,
                ST::format("Closing <{}> tag, which isn't open", name).c_str());
    }
    delete childPtr;
    return tag;
}
