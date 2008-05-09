#include "plSimStateMsg.h"

// plSimStateMsg //
plSimStateMsg::plSimStateMsg() { }
plSimStateMsg::~plSimStateMsg() { }

IMPLEMENT_CREATABLE(plSimStateMsg, kSimStateMsg, plSimulationMsg)


// plSimSuppressMsg //
plSimSuppressMsg::plSimSuppressMsg() { }
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
