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

#include "plBooleanConditionalObject.h"

/* plANDConditionalObject */
void plANDConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fChildren.resize(S->readInt());
    for (size_t i=0; i<fChildren.size(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plANDConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeInt(fChildren.size());
    for (size_t i=0; i<fChildren.size(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plANDConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.size(); i++)
        plResManager::PrcWriteKey(prc, fChildren[i]);
    prc->closeTag();
}

void plANDConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Children") {
        fChildren.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.size(); i++) {
            fChildren[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}


/* plORConditionalObject */
void plORConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fChildren.resize(S->readInt());
    for (size_t i=0; i<fChildren.size(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plORConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeInt(fChildren.size());
    for (size_t i=0; i<fChildren.size(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plORConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.size(); i++)
        plResManager::PrcWriteKey(prc, fChildren[i]);
    prc->closeTag();
}

void plORConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Children") {
        fChildren.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.size(); i++) {
            fChildren[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
