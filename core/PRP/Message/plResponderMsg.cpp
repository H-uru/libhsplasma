#include "plResponderMsg.h"

/* plOneShotMsg */
void plOneShotMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fCallbacks.read(S, mgr);
}

void plOneShotMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    fCallbacks.write(S, mgr);
}

void plOneShotMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);
    fCallbacks.prcWrite(prc);
}

void plOneShotMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if  (tag->getName() == "plOneShotCallbacks") {
        fCallbacks.prcParse(tag, mgr);
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
