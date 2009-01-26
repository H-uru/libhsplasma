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

plAnimStage::PlayType plAnimStage::getForwardType() const { return fForwardType; }
plAnimStage::PlayType plAnimStage::getBackType() const { return fBackType; }
plAnimStage::AdvanceType plAnimStage::getAdvanceType() const { return fAdvanceType; }
plAnimStage::AdvanceType plAnimStage::getRegressType() const { return fRegressType; }
plString plAnimStage::getAnimName() const { return fAnimName; }
unsigned char plAnimStage::getNotify() const { return fNotify; }
int plAnimStage::getLoops() const { return fLoops; }
bool plAnimStage::doAdvanceTo() const { return fDoAdvanceTo; }
bool plAnimStage::doRegressTo() const { return fDoRegressTo; }
unsigned int plAnimStage::getAdvanceTo() const { return fAdvanceTo; }
unsigned int plAnimStage::getRegressTo() const { return fRegressTo; }

void plAnimStage::setForwardType(PlayType fwd) { fForwardType = fwd; }
void plAnimStage::setBackType(PlayType back) { fBackType = back; }
void plAnimStage::setAdvanceType(AdvanceType adv) { fAdvanceType = adv; }
void plAnimStage::setRegressType(AdvanceType reg) { fRegressType = reg; }
void plAnimStage::setAnimName(const plString& name) { fAnimName = name; }
void plAnimStage::setNotify(unsigned char notify) { fNotify = notify; }
void plAnimStage::setLoops(int loops) { fLoops = loops; }

void plAnimStage::setAdvanceTo(bool doAdvance, unsigned int advance) {
    fDoAdvanceTo = doAdvance;
    fAdvanceTo = advance;
}

void plAnimStage::setRegressTo(bool doRegress, unsigned int regress) {
    fDoRegressTo = doRegress;
    fRegressTo = regress;
}
