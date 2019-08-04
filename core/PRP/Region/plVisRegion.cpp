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

#include "plVisRegion.h"

plVisRegion::plVisRegion()
{
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kIsNot, "kIsNot");
    fProps.setName(kReplaceNormal, "kReplaceNormal");
    fProps.setName(kDisableNormal, "kDisableNormal");
}

void plVisRegion::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);
    fRegion = mgr->readKey(S);
    fVisMgr = mgr->readKey(S);
}

void plVisRegion::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fRegion);
    mgr->writeKey(S, fVisMgr);
}

void plVisRegion::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Region");
    plResManager::PrcWriteKey(prc, fRegion);
    prc->closeTag();
    prc->writeSimpleTag("VisMgr");
    plResManager::PrcWriteKey(prc, fVisMgr);
    prc->closeTag();
}

void plVisRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Region") {
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "VisMgr") {
        if (tag->hasChildren())
            fVisMgr = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
