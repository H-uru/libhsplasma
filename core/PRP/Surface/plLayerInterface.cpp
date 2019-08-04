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

#include "plLayerInterface.h"

void plLayerInterface::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);
    fUnderLay = mgr->readKey(S);
}

void plLayerInterface::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fUnderLay);
}

void plLayerInterface::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("BaseLayer");
    plResManager::PrcWriteKey(prc, fUnderLay);
    prc->closeTag();
}

void plLayerInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "BaseLayer") {
        if (tag->hasChildren())
            fUnderLay = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
