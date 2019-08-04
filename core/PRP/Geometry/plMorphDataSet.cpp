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

#include "plMorphDataSet.h"

void plMorphDataSet::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fMorphs.resize(S->readInt());
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].read(S, mgr);
}

void plMorphDataSet::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fMorphs.size());
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].write(S, mgr);
}

void plMorphDataSet::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Morphs");
    for (size_t i=0; i<fMorphs.size(); i++)
        fMorphs[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphDataSet::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Morphs") {
        fMorphs.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMorphs.size(); i++) {
            fMorphs[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
