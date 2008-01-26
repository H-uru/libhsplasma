#include "plAnimStage.h"

plAnimStage::plAnimStage() { }
plAnimStage::~plAnimStage() { }

IMPLEMENT_CREATABLE(plAnimStage, kAnimStage, plCreatable)

void plAnimStage::read(hsStream* S, plResManager* mgr) {
    fAnimName = S->readSafeStr();
    fNotify = S->readByte();
    fForwardType = (PlayType)S->readInt();
    fBackType = (PlayType)S->readInt();
    fAdvanceType = (AdvanceType)S->readInt();
    fRegressType = (AdvanceType)S->readInt();
    fLoops = S->readInt();
    fDoAdvanceTo = S->readBool();
    fAdvanceTo = S->readInt();
    fDoRegressTo = S->readBool();
    fRegressTo = S->readInt();
}

void plAnimStage::write(hsStream* S, plResManager* mgr) {
    S->writeSafeStr(fAnimName);
    S->writeByte(fNotify);
    S->writeInt((hsUint32)fForwardType);
    S->writeInt((hsUint32)fBackType);
    S->writeInt((hsUint32)fAdvanceType);
    S->writeInt((hsUint32)fRegressType);
    S->writeInt(fLoops);
    S->writeBool(fDoAdvanceTo);
    S->writeInt(fAdvanceTo);
    S->writeBool(fDoRegressTo);
    S->writeInt(fRegressTo);
}

void plAnimStage::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("Loops", fLoops);
    prc->endTag(true);

    prc->startTag("StageTypes");
    prc->writeParam("Notify", fNotify);
    prc->writeParam("ForwardType", fForwardType);
    prc->writeParam("BackwardType", fBackType);
    prc->writeParam("AdvanceType", fAdvanceType);
    prc->writeParam("RegressType", fRegressType);
    prc->endTag(true);

    prc->startTag("AdvanceTo");
    prc->writeParam("enabled", fDoAdvanceTo);
    prc->writeParam("value", fAdvanceTo);
    prc->endTag(true);

    prc->startTag("RegressTo");
    prc->writeParam("enabled", fDoRegressTo);
    prc->writeParam("value", fRegressTo);
    prc->endTag(true);
}
