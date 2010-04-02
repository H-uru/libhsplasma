#include "plMessage.h"

plMessage::plMessage() : fTimeStamp(0.0), fBCastFlags(kLocalPropagate) { }

void plMessage::IMsgRead(hsStream* S, plResManager* mgr) {
    fSender = mgr->readKey(S);
    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    if (S->getVer() < pvEoa || S->getVer() == pvUniversal)
        fTimeStamp = S->readDouble();
    else
        fTimeStamp = 0.0;
    fBCastFlags = S->readInt();
}

void plMessage::IMsgWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fSender);
    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    if (S->getVer() < pvEoa || S->getVer() == pvUniversal)
        S->writeDouble(fTimeStamp);
    S->writeInt(fBCastFlags);
}

void plMessage::read(hsStream* S, plResManager* mgr) {
    IMsgRead(S, mgr);
}

void plMessage::write(hsStream* S, plResManager* mgr) {
    IMsgWrite(S, mgr);
}

void plMessage::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Sender");
    fSender->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("MessageParams");
    prc->writeParam("TimeStamp", fTimeStamp);
    prc->writeParamHex("BCastFlags", fBCastFlags);
    prc->endTag(true);
}

void plMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Sender") {
        if (tag->hasChildren())
            fSender = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MessageParams") {
        fTimeStamp = tag->getParam("TimeStamp", "0").toFloat();
        fBCastFlags = tag->getParam("BCastFlags", "0").toUint();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
