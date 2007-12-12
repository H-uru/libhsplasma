#include "plLogicModifier.h"

plLogicModifier::plLogicModifier() : fMyCursor(0) { }
plLogicModifier::~plLogicModifier() { }

IMPLEMENT_CREATABLE(plLogicModifier, kLogicModifier, plLogicModBase)

void plLogicModifier::read(hsStream* S, plResManager* mgr) {
    plLogicModBase::read(S, mgr);

    size_t count = S->readInt();
    fConditionList.setSizeNull(count);
    for (size_t i=0; i<count; i++)
        fConditionList[i] = mgr->readKey(S);
    fMyCursor = S->readInt();
}

void plLogicModifier::write(hsStream* S, plResManager* mgr) {
    plLogicModBase::write(S, mgr);

    S->writeInt(fConditionList.getSize());
    for (size_t i=0; i<fConditionList.getSize(); i++)
        mgr->writeKey(S, fConditionList[i]);
    S->writeInt(fMyCursor);
}

void plLogicModifier::prcWrite(pfPrcHelper* prc) {
    plLogicModBase::prcWrite(prc);

    prc->writeSimpleTag("Conditions");
    for (size_t i=0; i<fConditionList.getSize(); i++)
        fConditionList[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("LogicModifierParams");
    prc->writeParam("MyCursor", fMyCursor);
    prc->endTag(true);
}
