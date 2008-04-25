#include "plVolumeSensorConditionalObject.h"

plVolumeSensorConditionalObject::plVolumeSensorConditionalObject()
    : fTrigNum(-1), fType(kTypeEnter), fFirst(false), fTriggered(false),
      fIgnoreExtraEnters(true) { }

plVolumeSensorConditionalObject::~plVolumeSensorConditionalObject() { }

IMPLEMENT_CREATABLE(plVolumeSensorConditionalObject,
                    kVolumeSensorConditionalObject,
                    plConditionalObject)

void plVolumeSensorConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fTrigNum = S->readInt();
    fType = S->readInt();
    fFirst = S->readBool();
}

void plVolumeSensorConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fTrigNum);
    S->writeInt(fType);
    S->writeBool(fFirst);
}

void plVolumeSensorConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("Params");
    prc->writeParam("TrigNum", fTrigNum);
    prc->writeParam("Type", fType);
    prc->writeParam("First", fFirst);
    prc->endTag(true);
}
