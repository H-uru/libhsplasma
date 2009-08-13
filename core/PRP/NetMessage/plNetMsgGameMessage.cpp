#include "plNetMsgGameMessage.h"

plNetMsgGameMessage::plNetMsgGameMessage() : fMessage(NULL) { }

plNetMsgGameMessage::~plNetMsgGameMessage() {
    if (fMessage != NULL)
        delete fMessage;
}

IMPLEMENT_CREATABLE(plNetMsgGameMessage, kNetMsgGameMessage, plNetMsgStream)

void plNetMsgGameMessage::read(hsStream* S, plResManager* mgr) {
    plNetMsgStream::read(S, mgr);

    if (fMessage != NULL)
        delete fMessage;
    fMessage = plMessage::Convert(mgr->ReadCreatable(getStream()));

    if (S->readBool())
        fDeliveryTime.read(S);
}

void plNetMsgGameMessage::write(hsStream* S, plResManager* mgr) {
    plNetMsgStream::write(S, mgr);

    if (fDeliveryTime.atEpoch()) {
        S->writeBool(false);
    } else {
        S->writeBool(true);
        fDeliveryTime.write(S);
    }
}

void plNetMsgGameMessage::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);   // Skip raw stream writing

    if (fMessage != NULL) {
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

void plNetMsgGameMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "GameMessage") {
        if (fMessage != NULL)
            delete fMessage;
        if (tag->getParam("NULL", "false").toBool())
            fMessage = NULL;
        else
            fMessage = plMessage::Convert(mgr->prcParseCreatable(tag));
    } else if (tag->getName() == "DeliveryTime") {
        if (tag->hasChildren())
            fDeliveryTime.prcParse(tag->getFirstChild());
    } else {
        // Skip the raw stream
        plNetMessage::IPrcParse(tag, mgr);
    }
}
