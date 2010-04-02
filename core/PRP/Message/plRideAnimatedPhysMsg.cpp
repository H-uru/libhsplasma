#include "plRideAnimatedPhysMsg.h"

plRideAnimatedPhysMsg::plRideAnimatedPhysMsg() : fEntering(false) { }

void plRideAnimatedPhysMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fEntering = S->readBool();
    fRegion = mgr->readKey(S);
}

void plRideAnimatedPhysMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeBool(fEntering);
    mgr->writeKey(S, fRegion);
}

void plRideAnimatedPhysMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("Region");
    prc->writeParam("Entering", fEntering);
    prc->endTag();
    fRegion->prcWrite(prc);
    prc->closeTag();
}

void plRideAnimatedPhysMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Region") {
        fEntering = tag->getParam("Entering", "False").toBool();
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
