#include "plSimulationMsg.h"

/* plSimSuppressMsg */
plSimSuppressMsg::plSimSuppressMsg() : fSuppress(false) { }

void plSimSuppressMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fSuppress = S->readBool();
}

void plSimSuppressMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeBool(fSuppress);
}

void plSimSuppressMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("SimSuppressParams");
    prc->writeParam("Suppress", fSuppress);
    prc->endTag(true);
}

void plSimSuppressMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SimSuppressParams") {
        fSuppress = tag->getParam("Suppress", "false").toBool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}


/* plSubWorldMsg */
void plSubWorldMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fWorldKey = mgr->readKey(S);
}

void plSubWorldMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    mgr->writeKey(S, fWorldKey);
}

void plSubWorldMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("WorldKey");
    fWorldKey->prcWrite(prc);
    prc->closeTag();
}

void plSubWorldMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WorldKey") {
        fWorldKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
