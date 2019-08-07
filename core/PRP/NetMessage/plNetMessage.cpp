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

#include "plNetMessage.h"

/* plNetMessage */
void plNetMessage::read(hsStream* S, plResManager* mgr)
{
    fFlags = S->readInt();

    if ((fFlags & kHasVersion) != 0) {
        // 12.6 is known to be Live.2 -- other versions need to be inspected
        fProtocolVerMaj = S->readByte();
        fProtocolVerMin = S->readByte();
    }

    if ((fFlags & kHasTimeSent) != 0)
        fTimeSent.read(S);
    if ((fFlags & kHasContext) != 0)
        fContext = S->readInt();
    if ((fFlags & kHasTransactionID) != 0)
        fTransID = S->readInt();
    if ((fFlags & kHasPlayerID) != 0)
        fPlayerID = S->readInt();
    if ((fFlags & kHasAcctUuid) != 0)
        fAcctUuid.read(S);
}

void plNetMessage::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fFlags);

    if ((fFlags & kHasVersion) != 0) {
        S->writeByte(fProtocolVerMaj);
        S->writeByte(fProtocolVerMin);
    }

    if ((fFlags & kHasTimeSent) != 0)
        fTimeSent.write(S);
    if ((fFlags & kHasContext) != 0)
        S->writeInt(fContext);
    if ((fFlags & kHasTransactionID) != 0)
        S->writeInt(fTransID);
    if ((fFlags & kHasPlayerID) != 0)
        S->writeInt(fPlayerID);
    if ((fFlags & kHasAcctUuid) != 0)
        fAcctUuid.write(S);
}

void plNetMessage::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("NetMsgParams");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag();

    if ((fFlags & kHasVersion) != 0) {
        prc->startTag("ProtocolVersion");
        prc->writeParam("Major", fProtocolVerMaj);
        prc->writeParam("Minor", fProtocolVerMin);
        prc->endTag(true);
    }
    if ((fFlags & kHasTimeSent) != 0) {
        prc->writeSimpleTag("TimeSent");
        fTimeSent.prcWrite(prc);
        prc->closeTag();
    }
    if ((fFlags & kHasContext) != 0) {
        prc->startTag("Context");
        prc->writeParam("value", fContext);
        prc->endTag(true);
    }
    if ((fFlags & kHasTransactionID) != 0) {
        prc->startTag("Transaction");
        prc->writeParam("ID", fTransID);
        prc->endTag(true);
    }
    if ((fFlags & kHasPlayerID) != 0) {
        prc->startTag("Player");
        prc->writeParam("ID", fPlayerID);
        prc->endTag(true);
    }
    if ((fFlags & kHasAcctUuid) != 0) {
        prc->writeSimpleTag("AccountUuid");
        fAcctUuid.prcWrite(prc);
        prc->closeTag();
    }

    prc->closeTag();
}

void plNetMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "NetMsgParams") {
        fFlags = tag->getParam("Flags", "0").to_uint();
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "ProtocolVersion") {
                fProtocolVerMaj = child->getParam("Major", "12").to_uint();
                fProtocolVerMin = child->getParam("Minor", "6").to_uint();
            } else if (child->getName() == "TimeSent") {
                if (child->hasChildren())
                    fTimeSent.prcParse(child->getFirstChild());
            } else if (child->getName() == "Context") {
                fContext = child->getParam("value", "0").to_uint();
            } else if (child->getName() == "Transaction") {
                fTransID = child->getParam("ID", "0").to_uint();
            } else if (child->getName() == "Player") {
                fPlayerID = child->getParam("ID", "0").to_uint();
            } else if (child->getName() == "AccountUuid") {
                if (child->hasChildren())
                    fAcctUuid.prcParse(child->getFirstChild());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
