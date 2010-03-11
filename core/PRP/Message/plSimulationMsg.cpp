#include "plSimulationMsg.h"

/* plSimulationMsg */
plSimulationMsg::plSimulationMsg() { }
plSimulationMsg::~plSimulationMsg() { }

IMPLEMENT_CREATABLE(plSimulationMsg, kSimulationMsg, plMessage)


/* plSimStateMsg */
plSimStateMsg::plSimStateMsg() { }
plSimStateMsg::~plSimStateMsg() { }

IMPLEMENT_CREATABLE(plSimStateMsg, kSimStateMsg, plSimulationMsg)


/* plSimSuppressMsg */
plSimSuppressMsg::plSimSuppressMsg() : fSuppress(false) { }
plSimSuppressMsg::~plSimSuppressMsg() { }

IMPLEMENT_CREATABLE(plSimSuppressMsg, kSimSuppressMsg, plSimStateMsg)

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
plSubWorldMsg::plSubWorldMsg() { }
plSubWorldMsg::~plSubWorldMsg() { }

IMPLEMENT_CREATABLE(plSubWorldMsg, kSubWorldMsg, plSimulationMsg)

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
