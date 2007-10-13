#include "plMessage.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plMessage::plMessage() { }
plMessage::~plMessage() { }

IMPLEMENT_CREATABLE(plMessage, kMessage, plCreatable)

void plMessage::IMsgRead(hsStream* S, plResManager* mgr) {
    fSender = mgr->readKey(S);
    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    fTimeStamp = S->readDouble();
    fBCastFlags = S->readInt();
}

void plMessage::IMsgWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fSender);
    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    S->writeDouble(fTimeStamp);
    S->writeInt(fBCastFlags);
}

void plMessage::read(hsStream* S, plResManager* mgr) {
    IMsgRead(S, mgr);
}

void plMessage::write(hsStream* S, plResManager* mgr) {
    IMsgWrite(S, mgr);
}

void plMessage::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->writeSimpleTag("Sender");
    fSender->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("MessageParams");
    prc->writeParam("TimeStamp", fTimeStamp);
    prc->writeParam("BCastFlags", fBCastFlags);
    prc->endTag(true);
}
