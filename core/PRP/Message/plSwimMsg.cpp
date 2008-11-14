#include "plSwimMsg.h"

plSwimMsg::plSwimMsg() : fIsEntering(false) { }

IMPLEMENT_CREATABLE(plSwimMsg, kSwimMsg, plMessage)

void plSwimMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fIsEntering = S->readBool();
    fSwimRegion = mgr->readKey(S);
}

void plSwimMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeBool(fIsEntering);
    mgr->writeKey(S, fSwimRegion);
}

void plSwimMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("SwimMsgParams");
    prc->writeParam("IsEntering", fIsEntering);
    prc->endTag(true);

    prc->writeSimpleTag("SwimRegion");
    fSwimRegion->prcWrite(prc);
    prc->closeTag();
}

void plSwimMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SwimMsgParams") {
        fIsEntering = tag->getParam("IsEntering", "false").toBool();
    } else if (tag->getName() == "SwimRegion") {
        if (tag->hasChildren())
            fSwimRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
