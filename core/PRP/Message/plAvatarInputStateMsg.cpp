#include "plAvatarInputStateMsg.h"
#include "Debug/plDebug.h"

plAvatarInputStateMsg::plAvatarInputStateMsg() : fState(0) { }
plAvatarInputStateMsg::~plAvatarInputStateMsg() { }

IMPLEMENT_CREATABLE(plAvatarInputStateMsg, kAvatarInputStateMsg, plMessage)

void plAvatarInputStateMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fState = S->readShort();
}

void plAvatarInputStateMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeShort(fState);
}

void plAvatarInputStateMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("State");
    prc->writeParamHex("value", fState);
    prc->endTag(true);
}

void plAvatarInputStateMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "State") {
        fState = tag->getParam("value", "0").toUint();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
