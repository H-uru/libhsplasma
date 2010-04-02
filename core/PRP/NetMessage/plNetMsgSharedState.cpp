#include "plNetMsgSharedState.h"

/* plNetMsgSharedState */
plNetMsgSharedState::plNetMsgSharedState() : fLockRequest(0) { }

void plNetMsgSharedState::read(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::read(S, mgr);

    fState.read(getStream());
    fLockRequest = S->readByte();
}

void plNetMsgSharedState::write(hsStream* S, plResManager* mgr) {
    plNetMsgStreamedObject::write(S, mgr);

    S->writeByte(fLockRequest);
}

void plNetMsgSharedState::IPrcWrite(pfPrcHelper* prc) {
    plNetMsgObject::IPrcWrite(prc); // Skip the binary stream

    prc->writeSimpleTag("State");
    fState.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgSharedState::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "State") {
        if (tag->hasChildren())
            fState.prcParse(tag);
    } else {
        // Skip the binary stream
        plNetMsgObject::IPrcParse(tag, mgr);
    }
}
