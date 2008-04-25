#include "plKeyPressConditionalObject.h"

plKeyPressConditionalObject::plKeyPressConditionalObject() { }
plKeyPressConditionalObject::~plKeyPressConditionalObject() { }

IMPLEMENT_CREATABLE(plKeyPressConditionalObject, kKeyPressConditionalObject,
                    plConditionalObject)

void plKeyPressConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fKeyEvent = (plKeyDef)S->readInt();
}

void plKeyPressConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fKeyEvent);
}

void plKeyPressConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("KeyEvent");
    prc->writeParam("value", fKeyEvent);
    prc->endTag(true);
}
