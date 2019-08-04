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

#include "plDetectorModifier.h"

/* plDetectorModifier */
void plDetectorModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fReceivers.resize(S->readInt());
    for (size_t i=0; i<fReceivers.size(); i++)
        fReceivers[i] = mgr->readKey(S);
    fRemoteMod = mgr->readKey(S);
    fProxyKey = mgr->readKey(S);
}

void plDetectorModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        mgr->writeKey(S, fReceivers[i]);
    mgr->writeKey(S, fRemoteMod);
    mgr->writeKey(S, fProxyKey);
}

void plDetectorModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.size(); i++)
        plResManager::PrcWriteKey(prc, fReceivers[i]);
    prc->closeTag();

    prc->writeSimpleTag("RemoteMod");
    plResManager::PrcWriteKey(prc, fRemoteMod);
    prc->closeTag();
    prc->writeSimpleTag("Proxy");
    plResManager::PrcWriteKey(prc, fProxyKey);
    prc->closeTag();
}

void plDetectorModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "RemoteMod") {
        if (tag->hasChildren())
            fRemoteMod = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Proxy") {
        if (tag->hasChildren())
            fProxyKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
