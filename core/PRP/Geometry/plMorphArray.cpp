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

#include "plMorphArray.h"

void plMorphArray::read(hsStream* S, plResManager* mgr)
{
    fDeltas.resize(S->readInt());
    for (size_t i=0; i<fDeltas.size(); i++)
        fDeltas[i].read(S, mgr);
}

void plMorphArray::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fDeltas.size());
    for (size_t i=0; i<fDeltas.size(); i++)
        fDeltas[i].write(S, mgr);
}

void plMorphArray::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("plMorphArray");
    for (size_t i=0; i<fDeltas.size(); i++)
        fDeltas[i].prcWrite(prc);
    prc->closeTag();
}

void plMorphArray::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() != "plMorphArray")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDeltas.resize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fDeltas.size(); i++) {
        fDeltas[i].prcParse(child, mgr);
        child = child->getNextSibling();
    }
}
