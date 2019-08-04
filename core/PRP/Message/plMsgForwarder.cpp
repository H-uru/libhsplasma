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

#include "plMsgForwarder.h"

void plMsgForwarder::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fForwardKeys.resize(S->readInt());
    for (size_t i=0; i<fForwardKeys.size(); i++)
        fForwardKeys[i] = mgr->readKey(S);
}

void plMsgForwarder::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeInt(fForwardKeys.size());
    for (size_t i=0; i<fForwardKeys.size(); i++)
        mgr->writeKey(S, fForwardKeys[i]);
}

void plMsgForwarder::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ForwardKeys");
    for (size_t i=0; i<fForwardKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fForwardKeys[i]);
    prc->closeTag();
}

void plMsgForwarder::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ForwardKeys") {
        fForwardKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fForwardKeys.size(); i++) {
            fForwardKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
