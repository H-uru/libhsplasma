#include "plServerReplyMsg.h"
#include "Debug/plDebug.h"

plServerReplyMsg::plServerReplyMsg() : fType(kUnInit) { }
plServerReplyMsg::~plServerReplyMsg() { }

IMPLEMENT_CREATABLE(plServerReplyMsg, kServerReplyMsg, plMessage)

void plServerReplyMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fType = S->readIntSwap();
}

void plServerReplyMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeIntSwap(fType);
}

void plServerReplyMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("Type");
    prc->writeParamHex("value", (unsigned int)fType);
    prc->endTag(true);
}

void plServerReplyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Type") {
        fType = tag->getParam("value", "0").toInt();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
