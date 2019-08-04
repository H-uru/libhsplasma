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

#include "plOneShotCallbacks.h"

void plOneShotCallbacks::read(hsStream* S, plResManager* mgr)
{
    fCallbacks.resize(S->readInt());
    for (size_t i=0; i<fCallbacks.size(); i++) {
        fCallbacks[i].fMarker = S->readSafeStr();
        fCallbacks[i].fReceiver = mgr->readKey(S);
        fCallbacks[i].fUser = S->readShort();
    }
}

void plOneShotCallbacks::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fCallbacks.size());
    for (size_t i=0; i<fCallbacks.size(); i++) {
        S->writeSafeStr(fCallbacks[i].fMarker);
        mgr->writeKey(S, fCallbacks[i].fReceiver);
        S->writeShort(fCallbacks[i].fUser);
    }
}

void plOneShotCallbacks::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("plOneShotCallbacks");
    for (size_t i=0; i<fCallbacks.size(); i++) {
        prc->startTag("Callback");
        prc->writeParam("Marker", fCallbacks[i].fMarker);
        prc->writeParam("User", fCallbacks[i].fUser);
        prc->endTag();
        plResManager::PrcWriteKey(prc, fCallbacks[i].fReceiver);
        prc->closeTag();
    }
    prc->closeTag();
}

void plOneShotCallbacks::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() != "plOneShotCallbacks")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fCallbacks.resize(tag->countChildren());
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fCallbacks.size(); i++) {
        if (child->getName() != "Callback")
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        fCallbacks[i].fMarker = child->getParam("Marker", "");
        fCallbacks[i].fUser = child->getParam("User", "0").to_int();
        if (child->hasChildren())
            fCallbacks[i].fReceiver = mgr->prcParseKey(child->getFirstChild());
        child = child->getNextSibling();
    }
}
