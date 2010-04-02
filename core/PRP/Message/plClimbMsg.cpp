#include "plClimbMsg.h"

plClimbMsg::plClimbMsg() : fCommand(0), fDirection(0), fStatus(false) { }

void plClimbMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCommand = S->readInt();
    fDirection = S->readInt();
    fStatus = S->readBool();
    fTarget = mgr->readKey(S);
}

void plClimbMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fCommand);
    S->writeInt(fDirection);
    S->writeBool(fStatus);
    mgr->writeKey(S, fTarget);
}

void plClimbMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("ClimbMsgParams");
    prc->writeParamHex("Command", fCommand);
    prc->writeParamHex("Direction", fDirection);
    prc->writeParam("Status", fStatus);
    prc->endTag(true);

    prc->writeSimpleTag("Target");
    fTarget->prcWrite(prc);
    prc->closeTag();
}

void plClimbMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ClimbMsgParams") {
        fCommand = tag->getParam("Command", "0").toUint();
        fDirection = tag->getParam("Direction", "0").toUint();
        fStatus = tag->getParam("Status", "false").toBool();
    } else if (tag->getName() == "Target") {
        if (tag->hasChildren())
            fTarget = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
