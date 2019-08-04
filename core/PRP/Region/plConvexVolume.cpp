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

#include "plConvexVolume.h"

void plConvexVolume::read(hsStream* S, plResManager* mgr)
{
    fLocalPlanes.resize(S->readInt());
    for (size_t i=0; i<fLocalPlanes.size(); i++)
        fLocalPlanes[i].read(S);
}

void plConvexVolume::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fLocalPlanes.size());
    for (size_t i=0; i<fLocalPlanes.size(); i++)
        fLocalPlanes[i].write(S);
}

void plConvexVolume::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fLocalPlanes.size(); i++)
        fLocalPlanes[i].prcWrite(prc);
    prc->closeTag();
}

void plConvexVolume::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Planes") {
        fLocalPlanes.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLocalPlanes.size(); i++) {
            fLocalPlanes[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
