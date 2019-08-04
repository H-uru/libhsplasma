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

#include "pfGUISkin.h"

/* pfGUISkin::pfSRect */
void pfGUISkin::pfSRect::read(hsStream* S)
{
    fX = S->readShort();
    fY = S->readShort();
    fWidth = S->readShort();
    fHeight = S->readShort();
}

void pfGUISkin::pfSRect::write(hsStream* S)
{
    S->writeShort(fX);
    S->writeShort(fY);
    S->writeShort(fWidth);
    S->writeShort(fHeight);
}

void pfGUISkin::pfSRect::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfSRect");
    prc->writeParam("X", fX);
    prc->writeParam("Y", fY);
    prc->writeParam("width", fWidth);
    prc->writeParam("height", fHeight);
    prc->endTag(true);
}

void pfGUISkin::pfSRect::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "pfSRect")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fX = tag->getParam("X", "0").to_uint();
    fY = tag->getParam("Y", "0").to_uint();
    fWidth = tag->getParam("width", "0").to_uint();
    fHeight = tag->getParam("height", "0").to_uint();
}


/* pfGUISkin */
void pfGUISkin::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fItemMargin = S->readShort();
    fBorderMargin = S->readShort();
    size_t i, count = S->readInt();
    for (i=0; i<count; i++)
        fElements[i].read(S);
    for (; i<kNumElements; i++)
        fElements[i].clear();

    fTexture = mgr->readKey(S);
}

void pfGUISkin::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeShort(fItemMargin);
    S->writeShort(fBorderMargin);
    S->writeInt(kNumElements);
    for (size_t i=0; i<kNumElements; i++)
        fElements[i].write(S);

    mgr->writeKey(S, fTexture);
}

void pfGUISkin::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SkinParams");
    prc->writeParam("ItemMargin", fItemMargin);
    prc->writeParam("BorderMargin", fBorderMargin);
    prc->endTag(true);

    prc->writeSimpleTag("Elements");
    for (size_t i=0; i<kNumElements; i++)
        fElements[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Texture");
    plResManager::PrcWriteKey(prc, fTexture);
    prc->closeTag();
}

void pfGUISkin::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SkinParams") {
        fItemMargin = tag->getParam("ItemMargin", "0").to_uint();
        fBorderMargin = tag->getParam("BorderMargin", "0").to_uint();
    } else if (tag->getName() == "Elements") {
        size_t nElements = tag->countChildren();
        if (nElements > kNumElements)
            throw pfPrcParseException(__FILE__, __LINE__, "Too many elements");
        const pfPrcTag* child = tag->getFirstChild();
        size_t i;
        for (i=0; i<nElements; i++) {
            fElements[i].prcParse(child);
            child = child->getNextSibling();
        }
        for (; i<kNumElements; i++)
            fElements[i].clear();
    } else if (tag->getName() == "Texture") {
        if (tag->hasChildren())
            fTexture = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
