#include "plControlEventConditionalObject.h"

plControlEventConditionalObject::plControlEventConditionalObject() { }
plControlEventConditionalObject::~plControlEventConditionalObject() { }

IMPLEMENT_CREATABLE(plControlEventConditionalObject,
                    kControlEventConditionalObject,
                    plConditionalObject)

void plControlEventConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fControlEvent = (ControlEventCode)S->readInt();
}

void plControlEventConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fControlEvent);
}

void plControlEventConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("ControlEvent");
    prc->writeParam("value", fControlEvent);
    prc->endTag(true);
}
