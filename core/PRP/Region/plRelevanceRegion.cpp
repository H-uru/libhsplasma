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

#include "plRelevanceRegion.h"

void plRelevanceRegion::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);
    fRegion = mgr->readKey(S);
}

void plRelevanceRegion::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fRegion);
}

void plRelevanceRegion::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Region");
    plResManager::PrcWriteKey(prc, fRegion);
    prc->closeTag();
}

void plRelevanceRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Region") {
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
