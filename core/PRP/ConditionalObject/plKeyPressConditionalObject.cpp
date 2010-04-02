#include "plKeyPressConditionalObject.h"

plKeyPressConditionalObject::plKeyPressConditionalObject()
                           : fKeyEvent((plKeyDef)0) { }

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

void plKeyPressConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "KeyEvent") {
        fKeyEvent = (plKeyDef)tag->getParam("value", "0").toInt();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
