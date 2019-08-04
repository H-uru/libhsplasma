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

#include "plMessage.h"

void plMessage::IMsgRead(hsStream* S, plResManager* mgr)
{
    fSender = mgr->readKey(S);
    fReceivers.resize(S->readInt());
    for (size_t i=0; i<fReceivers.size(); i++)
        fReceivers[i] = mgr->readKey(S);
    if (S->getVer().isUru() || S->getVer().isUniversal())
        fTimeStamp = S->readDouble();
    else
        fTimeStamp = 0.0;
    fBCastFlags = S->readInt();
}

void plMessage::IMsgWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fSender);
    S->writeInt(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        mgr->writeKey(S, fReceivers[i]);
    if (S->getVer().isUru() || S->getVer().isUniversal())
        S->writeDouble(fTimeStamp);
    S->writeInt(fBCastFlags);
}

void plMessage::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Sender");
    plResManager::PrcWriteKey(prc, fSender);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.size(); i++)
        plResManager::PrcWriteKey(prc, fReceivers[i]);
    prc->closeTag();

    prc->startTag("MessageParams");
    prc->writeParam("TimeStamp", fTimeStamp);
    prc->writeParamHex("BCastFlags", fBCastFlags);
    prc->endTag(true);
}

void plMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Sender") {
        if (tag->hasChildren())
            fSender = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MessageParams") {
        fTimeStamp = tag->getParam("TimeStamp", "0").to_float();
        fBCastFlags = tag->getParam("BCastFlags", "0").to_uint();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
