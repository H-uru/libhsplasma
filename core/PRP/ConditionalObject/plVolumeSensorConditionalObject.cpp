#include "plVolumeSensorConditionalObject.h"

/* plVolumeSensorConditionalObject */
plVolumeSensorConditionalObject::plVolumeSensorConditionalObject()
    : fTrigNum(-1), fType(kTypeEnter), fFirst(false), fTriggered(false),
      fIgnoreExtraEnters(true) { }

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
    prc->startTag("VolumeSensorParams");
    prc->writeParam("TrigNum", fTrigNum);
    prc->writeParam("Type", fType);
    prc->writeParam("First", fFirst);
    prc->endTag(true);
}

void plVolumeSensorConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "VolumeSensorParams") {
        fTrigNum = tag->getParam("TrigNum", "0").toInt();
        fType = tag->getParam("Type", "0").toInt();
        fFirst = tag->getParam("First", "false").toBool();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
