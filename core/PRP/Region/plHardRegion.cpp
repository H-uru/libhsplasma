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

#include "plHardRegion.h"

/* plHardRegionComplex */
void plHardRegionComplex::read(hsStream* S, plResManager* mgr)
{
    plHardRegion::read(S, mgr);

    fSubRegions.resize(S->readInt());
    for (size_t i=0; i<fSubRegions.size(); i++)
        fSubRegions[i] = mgr->readKey(S);
}

void plHardRegionComplex::write(hsStream* S, plResManager* mgr)
{
    plHardRegion::write(S, mgr);

    S->writeInt(fSubRegions.size());
    for (size_t i=0; i<fSubRegions.size(); i++)
        mgr->writeKey(S, fSubRegions[i]);
}

void plHardRegionComplex::IPrcWrite(pfPrcHelper* prc)
{
    plHardRegion::IPrcWrite(prc);

    prc->writeSimpleTag("SubRegions");
    for (size_t i=0; i<fSubRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fSubRegions[i]);
    prc->closeTag();
}

void plHardRegionComplex::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SubRegions") {
        fSubRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSubRegions.size(); i++) {
            fSubRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plHardRegion::IPrcParse(tag, mgr);
    }
}
