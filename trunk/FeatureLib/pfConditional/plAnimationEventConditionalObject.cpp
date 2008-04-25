#include "plAnimationEventConditionalObject.h"

plAnimationEventConditionalObject::plAnimationEventConditionalObject()
    : fAction(kStart) { }
plAnimationEventConditionalObject::~plAnimationEventConditionalObject() { }

IMPLEMENT_CREATABLE(plAnimationEventConditionalObject,
                    kAnimationEventConditionalObject,
                    plConditionalObject)

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
