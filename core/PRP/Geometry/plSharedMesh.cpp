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

#include "plSharedMesh.h"

plSharedMesh::~plSharedMesh()
{
    for (auto span = fSpans.begin(); span != fSpans.end(); ++span)
        delete *span;
}

void plSharedMesh::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    clearSpans();
    fSpans.resize(S->readInt());
    for (size_t i=0; i<fSpans.size(); i++) {
        fSpans[i] = new plGeometrySpan();
        fSpans[i]->read(S);
    }
    fMorphSet = mgr->readKey(S);
    fFlags = S->readByte();
}

void plSharedMesh::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSpans.size());
    for (size_t i=0; i<fSpans.size(); i++)
        fSpans[i]->write(S);
    mgr->writeKey(S, fMorphSet);
    S->writeByte(fFlags);
}

void plSharedMesh::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Spans");
    for (size_t i=0; i<fSpans.size(); i++)
        fSpans[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MorphSet");
    plResManager::PrcWriteKey(prc, fMorphSet);
    prc->closeTag();
    prc->startTag("Flags");
    prc->writeParamHex("value", fFlags);
    prc->endTag(true);
}

void plSharedMesh::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Spans") {
        clearSpans();
        fSpans.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSpans.size(); i++) {
            fSpans[i] = new plGeometrySpan();
            fSpans[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MorphSet") {
        if (tag->hasChildren())
            fMorphSet = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Flags") {
        fFlags = tag->getParam("value", "0").to_uint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plSharedMesh::delSpan(size_t idx)
{
    delete fSpans[idx];
    fSpans.erase(fSpans.begin() + idx);
}

void plSharedMesh::clearSpans()
{
    for (auto span = fSpans.begin(); span != fSpans.end(); ++span)
        delete *span;
    fSpans.clear();
}
