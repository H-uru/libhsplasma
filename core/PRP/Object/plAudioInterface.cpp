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

#include "plAudioInterface.h"

void plAudioInterface::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);
    fAudible = mgr->readKey(S);
}

void plAudioInterface::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fAudible);
}

void plAudioInterface::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Audible");
    plResManager::PrcWriteKey(prc, fAudible);
    prc->closeTag();
}

void plAudioInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Audible") {
        if (tag->hasChildren())
            fAudible = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
