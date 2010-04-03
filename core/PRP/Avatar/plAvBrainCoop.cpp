#include "plAvBrainCoop.h"

plAvBrainCoop::plAvBrainCoop()
             : fInitiatorID(0), fInitiatorSerial(0), fWaitingForClick(false) { }

void plAvBrainCoop::read(hsStream* S, plResManager* mgr) {
    plAvBrainGeneric::read(S, mgr);

    fInitiatorID = S->readInt();
    fInitiatorSerial = S->readShort();

    if (S->readBool())
        fHostKey = mgr->readKey(S);
    else
        fHostKey = plKey();

    if (S->readBool())
        fGuestKey = mgr->readKey(S);
    else
        fGuestKey = plKey();

    fWaitingForClick = S->readBool();

    fRecipients.setSize(S->readShort());
    for (size_t i=0; i<fRecipients.getSize(); i++)
        fRecipients[i] = mgr->readKey(S);
}

void plAvBrainCoop::write(hsStream* S, plResManager* mgr) {
    plAvBrainGeneric::write(S, mgr);

    S->writeInt(fInitiatorID);
    S->writeShort(fInitiatorSerial);

    S->writeBool(fHostKey.Exists());
    if (fHostKey.Exists())
        mgr->writeKey(S, fHostKey);

    S->writeBool(fGuestKey.Exists());
    if (fGuestKey.Exists())
        mgr->writeKey(S, fGuestKey);

    S->writeBool(fWaitingForClick);

    S->writeShort(fRecipients.getSize());
    for (size_t i=0; i<fRecipients.getSize(); i++)
        mgr->writeKey(S, fRecipients[i]);
}

void plAvBrainCoop::IPrcWrite(pfPrcHelper* prc) {
    plAvBrainGeneric::IPrcWrite(prc);

    prc->startTag("Initiator");
    prc->writeParam("ID", fInitiatorID);
    prc->writeParam("Serial", fInitiatorSerial);
    prc->endTag(true);

    prc->startTag("AvBrainCoopParams");
    prc->writeParam("WaitingForClick", fWaitingForClick);
    prc->endTag(true);

    prc->writeSimpleTag("Host");
    fHostKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Guest");
    fGuestKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Recipients");
    for (size_t i=0; i<fRecipients.getSize(); i++)
        fRecipients[i]->prcWrite(prc);
    prc->closeTag();
}

void plAvBrainCoop::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Initiator") {
        fInitiatorID = tag->getParam("ID", "0").toUint();
        fInitiatorSerial = tag->getParam("Serial", "0").toUint();
    } else if (tag->getName() == "AvBrainCoopParams") {
        fWaitingForClick = tag->getParam("WaitingForClick", "False").toBool();
    } else if (tag->getName() == "Host") {
        if (tag->hasChildren())
            fHostKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Guest") {
        if (tag->hasChildren())
            fGuestKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Recipients") {
        fRecipients.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRecipients.getSize(); i++) {
            fRecipients[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plAvBrainGeneric::IPrcParse(tag, mgr);
    }
}
