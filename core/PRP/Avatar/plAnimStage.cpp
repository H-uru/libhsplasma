#include "plAnimStage.h"

plAnimStage::plAnimStage()
           : fForwardType(kPlayNone), fBackType(kPlayNone),
             fAdvanceType(kAdvanceNone), fRegressType(kAdvanceNone),
             fNotify(0), fLoops(0), fDoAdvanceTo(false), fDoRegressTo(false),
             fAdvanceTo(0), fRegressTo(0) { }

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

void plAnimStage::IPrcWrite(pfPrcHelper* prc) {
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

void plAnimStage::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fLoops = tag->getParam("Loops", "0").toInt();
    } else if (tag->getName() == "StageTypes") {
        fNotify = tag->getParam("Notify", "0").toUint();
        fForwardType = (PlayType)tag->getParam("ForwardType", "0").toInt();
        fBackType = (PlayType)tag->getParam("BackwardType", "0").toInt();
        fAdvanceType = (AdvanceType)tag->getParam("AdvanceType", "0").toInt();
        fRegressType = (AdvanceType)tag->getParam("RegressType", "0").toInt();
    } else if (tag->getName() == "AdvanceTo") {
        fDoAdvanceTo = tag->getParam("enabled", "true").toBool();
        fAdvanceTo = tag->getParam("value", "0").toUint();
    } else if (tag->getName() == "RegressTo") {
        fDoRegressTo = tag->getParam("enabled", "true").toBool();
        fRegressTo = tag->getParam("value", "0").toUint();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
