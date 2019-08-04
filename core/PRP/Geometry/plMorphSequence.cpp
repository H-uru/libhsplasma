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

#include "plMorphSequence.h"

void plMorphSequence::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fMorphs.resize(S->readInt());
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].read(S, mgr);

    fSharedMeshes.resize(S->readInt());
    for (size_t i=0; i<fSharedMeshes.size(); i++)
        fSharedMeshes[i] = mgr->readKey(S);
}

void plMorphSequence::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fMorphs.size());
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].write(S, mgr);

    S->writeInt(fSharedMeshes.size());
    for (size_t i=0; i<fSharedMeshes.size(); i++)
        mgr->writeKey(S, fSharedMeshes[i]);
}

void plMorphSequence::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SharedMeshes");
    for (size_t i=0; i<fSharedMeshes.size(); i++)
        plResManager::PrcWriteKey(prc, fSharedMeshes[i]);
    prc->closeTag();
}

void plMorphSequence::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Morphs") {
        size_t count = tag->countChildren();
        fMorphs.resize(count);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<count; i++) {
            fMorphs[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SharedMeshes") {
        size_t count = tag->countChildren();
        fSharedMeshes.resize(count);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<count; i++) {
            fSharedMeshes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
