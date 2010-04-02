#include "plAnimationEventConditionalObject.h"

plAnimationEventConditionalObject::plAnimationEventConditionalObject()
                                 : fAction(kStart) { }

void plAnimationEventConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fTarget = mgr->readKey(S);
    fAction = (CallbackEvent)S->readInt();
}

void plAnimationEventConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    mgr->writeKey(S, fTarget);
    S->writeInt(fAction);
}

void plAnimationEventConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Target");
    fTarget->prcWrite(prc);
    prc->closeTag();
    prc->startTag("Action");
    prc->writeParam("value", fAction);
    prc->endTag(true);
}

void plAnimationEventConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Target") {
        if (tag->hasChildren())
            fTarget = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Action") {
        fAction = (CallbackEvent)tag->getParam("value", "0").toInt();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
