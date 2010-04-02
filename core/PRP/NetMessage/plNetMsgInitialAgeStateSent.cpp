#include "plNetMsgInitialAgeStateSent.h"

plNetMsgInitialAgeStateSent::plNetMsgInitialAgeStateSent() : fNumInitialStates(0) { }

void plNetMsgInitialAgeStateSent::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);
    fNumInitialStates = S->readInt();
}

void plNetMsgInitialAgeStateSent::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);
    S->writeInt(fNumInitialStates);
}

void plNetMsgInitialAgeStateSent::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->startTag("InitialAgeStateParams");
    prc->writeParam("NumInitialStates", fNumInitialStates);
    prc->endTag(true);
}

void plNetMsgInitialAgeStateSent::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "InitialAgeStateParams") {
        fNumInitialStates = tag->getParam("NumInitialStates", "0").toUint();
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
