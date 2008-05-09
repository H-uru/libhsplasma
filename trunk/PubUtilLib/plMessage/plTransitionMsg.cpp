#include "plTransitionMsg.h"

plTransitionMsg::plTransitionMsg()
               : fEffect(0), fLengthInSecs(0.0f), fHoldUntilNext(0) { }

plTransitionMsg::~plTransitionMsg() { }

IMPLEMENT_CREATABLE(plTransitionMsg, kTransitionMsg, plMessageWithCallbacks)

void plTransitionMsg::read(hsStream* S, plResManager* mgr) {
    plMessageWithCallbacks::read(S, mgr);

    fEffect = S->readInt();
    fLengthInSecs = S->readFloat();
    fHoldUntilNext = S->readInt();
}

void plTransitionMsg::write(hsStream* S, plResManager* mgr) {
    plMessageWithCallbacks::write(S, mgr);

    S->writeInt(fEffect);
    S->writeFloat(fLengthInSecs);
    S->writeInt(fHoldUntilNext);
}

void plTransitionMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessageWithCallbacks::IPrcWrite(prc);

    prc->startTag("TransitionParams");
    prc->writeParam("Effect", fEffect);
    prc->writeParam("Length", fLengthInSecs);
    prc->writeParam("HoldUntilNext", fHoldUntilNext);
    prc->endTag(true);
}

void plTransitionMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "TimerCallback") {
        fEffect = tag->getParam("Effect", "0").toUint();
        fLengthInSecs = tag->getParam("Length", "0").toFloat();
        fHoldUntilNext = tag->getParam("HoldUntilNext", "0").toInt();
    } else {
        plMessageWithCallbacks::IPrcParse(tag, mgr);
    }
}
