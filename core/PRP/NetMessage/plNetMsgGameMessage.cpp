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

#include "plNetMsgGameMessage.h"

/* plNetMsgGameMessage */
plNetMsgGameMessage::~plNetMsgGameMessage()
{
    delete fMessage;
}

void plNetMsgGameMessage::read(hsStream* S, plResManager* mgr)
{
    plNetMsgStream::read(S, mgr);

    delete fMessage;
    hsRAMStream* msgStream = getStream();
    fMessage = mgr->ReadCreatableC<plMessage>(msgStream);

    if (S->readBool())
        fDeliveryTime.read(S);
}

void plNetMsgGameMessage::write(hsStream* S, plResManager* mgr)
{
    hsRAMStream* msgStream = getStream();
    msgStream->setVer(S->getVer());
    msgStream->rewind();
    msgStream->resize(0);
    mgr->WriteCreatable(msgStream, fMessage);

    plNetMsgStream::write(S, mgr);

    if (fDeliveryTime.atEpoch()) {
        S->writeBool(false);
    } else {
        S->writeBool(true);
        fDeliveryTime.write(S);
    }
}

void plNetMsgGameMessage::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);   // Skip raw stream writing

    if (fMessage) {
        prc->writeSimpleTag("GameMessage");
        fMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("GameMessage");
        prc->writeParam("NULL", "true");
        prc->endTag(true);
    }

    prc->writeSimpleTag("DeliveryTime");
    fDeliveryTime.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgGameMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "GameMessage") {
        delete fMessage;
        if (tag->getParam("NULL", "false").to_bool())
            fMessage = nullptr;
        else
            fMessage = mgr->prcParseCreatableC<plMessage>(tag);
    } else if (tag->getName() == "DeliveryTime") {
        if (tag->hasChildren())
            fDeliveryTime.prcParse(tag->getFirstChild());
    } else {
        // Skip the raw stream
        plNetMessage::IPrcParse(tag, mgr);
    }
}

void plNetMsgGameMessage::setMessage(plMessage* Message)
{
    delete fMessage;
    fMessage = Message;
}


/* plNetMsgGameMessageDirected */
void plNetMsgGameMessageDirected::read(hsStream* S, plResManager* mgr)
{
    plNetMsgGameMessage::read(S, mgr);

    unsigned char count = S->readByte();
    fReceivers.resize(count);
    for (size_t i=0; i<count; i++)
        fReceivers[i] = S->readInt();
}

void plNetMsgGameMessageDirected::write(hsStream* S, plResManager* mgr)
{
    plNetMsgGameMessage::write(S, mgr);

    S->writeByte(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        S->writeInt(fReceivers[i]);
}

void plNetMsgGameMessageDirected::IPrcWrite(pfPrcHelper* prc)
{
    plNetMsgGameMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.size(); i++) {
        prc->startTag("Receiver");
        prc->writeParam("ID", fReceivers[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plNetMsgGameMessageDirected::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            if (child->getName() != "Receiver")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fReceivers[i] = child->getParam("ID", "0").to_uint();
            child = child->getNextSibling();
        }
    } else {
        plNetMsgGameMessage::IPrcParse(tag, mgr);
    }
}
