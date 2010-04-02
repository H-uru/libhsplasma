#include "plTimerCallbackMsg.h"

plTimerCallbackMsg::plTimerCallbackMsg() : fID(0), fTime(0.0f) { }

void plTimerCallbackMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fID = S->readInt();
    fTime = S->readFloat();
}

void plTimerCallbackMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeInt(fID);
    S->writeFloat(fTime);
}

void plTimerCallbackMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("TimerCallback");
    prc->writeParam("ID", fID);
    prc->writeParam("Time", fTime);
    prc->endTag(true);
}

void plTimerCallbackMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "TimerCallback") {
        fID = tag->getParam("ID", "0").toUint();
        fTime = tag->getParam("Time", "0").toFloat();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
