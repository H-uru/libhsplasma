#include "plOneShotMod.h"

plOneShotMod::plOneShotMod()
            : fDrivable(false), fReversable(false), fSmartSeek(false),
              fNoSeek(true), fSeekDuration(0.0f) { }

plOneShotMod::~plOneShotMod() { }

IMPLEMENT_CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

void plOneShotMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fAnimName = S->readSafeStr();
    fSeekDuration = S->readFloat();
    fDrivable = S->readBool();
    fReversable = S->readBool();
    fSmartSeek = S->readBool();
    fNoSeek = S->readBool();
}

void plOneShotMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    S->writeSafeStr(fAnimName);
    S->writeFloat(fSeekDuration);
    S->writeBool(fDrivable);
    S->writeBool(fReversable);
    S->writeBool(fSmartSeek);
    S->writeBool(fNoSeek);
}

void plOneShotMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("SeekDuration", fSeekDuration);
    prc->writeParam("Drivable", fDrivable);
    prc->writeParam("Reversable", fReversable);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("NoSeek", fNoSeek);
    prc->endTag(true);
}

void plOneShotMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fSeekDuration = tag->getParam("SeekDuration", "0").toFloat();
        fDrivable = tag->getParam("Drivable", "false").toBool();
        fReversable = tag->getParam("Reversable", "false").toBool();
        fSmartSeek = tag->getParam("SmartSeek", "false").toBool();
        fNoSeek = tag->getParam("NoSeek", "true").toBool();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}

plString plOneShotMod::getAnimName() const { return fAnimName; }
bool plOneShotMod::isDrivable() const { return fDrivable; }
bool plOneShotMod::isReversable() const { return fReversable; }
bool plOneShotMod::getSmartSeek() const { return fSmartSeek; }
bool plOneShotMod::getNoSeek() const { return fNoSeek; }
float plOneShotMod::getSeekDuration() { return fSeekDuration; }

void plOneShotMod::setAnimName(const plString& name) { fAnimName = name; }
void plOneShotMod::setDrivable(bool drivable) { fDrivable = drivable; }
void plOneShotMod::setReversable(bool reversable) { fReversable = reversable; }
void plOneShotMod::setSmartSeek(bool smartSeek) { fSmartSeek = smartSeek; }
void plOneShotMod::setNoSeek(bool noSeek) { fNoSeek = noSeek; }
void plOneShotMod::setSeekDuration(float duration) { fSeekDuration = duration; }
