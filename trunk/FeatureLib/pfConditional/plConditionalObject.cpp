#include "plConditionalObject.h"

plConditionalObject::plConditionalObject() /*: fLogicMod(NULL)*/ { }
plConditionalObject::~plConditionalObject() { }

IMPLEMENT_CREATABLE(plConditionalObject, kConditionalObject, hsKeyedObject)

void plConditionalObject::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fSatisfied = S->readBool();
    fToggle = S->readBool();
}

void plConditionalObject::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeBool(fSatisfied);
    S->writeBool(fToggle);
}

void plConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("ConditionFlags");
    prc->writeParam("satisfied", fSatisfied);
    prc->writeParam("toggle", fToggle);
    prc->endTag(true);
}

void plConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ConditionFlags") {
        fSatisfied = tag->getParam("satisfied", "false").toBool();
        fToggle = tag->getParam("toggle", "false").toBool();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
