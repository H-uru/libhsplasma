#include "plOneShotMod.h"

plOneShotMod::plOneShotMod()
            : fDrivable(false), fReversible(false), fSmartSeek(false),
              fNoSeek(true), fSeekDuration(0.0f) { }

plOneShotMod::~plOneShotMod() { }

IMPLEMENT_CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

void plOneShotMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fAnimName = S->readSafeStr();
    fSeekDuration = S->readFloat();
    fDrivable = S->readBool();
    fReversible = S->readBool();
    fSmartSeek = S->readBool();
    fNoSeek = S->readBool();
}

void plOneShotMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    S->writeSafeStr(fAnimName);
    S->writeFloat(fSeekDuration);
    S->writeBool(fDrivable);
    S->writeBool(fReversible);
    S->writeBool(fSmartSeek);
    S->writeBool(fNoSeek);
}

void plOneShotMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("SeekDuration", fSeekDuration);
    prc->writeParam("Drivable", fDrivable);
    prc->writeParam("Reversible", fReversible);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("NoSeek", fNoSeek);
    prc->endTag(true);
}

void plOneShotMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fSeekDuration = tag->getParam("SeekDuration", "0").toFloat();
        fDrivable = tag->getParam("Drivable", "false").toBool();
        fDrivable = tag->getParam("Reversible", "false").toBool();
        fDrivable = tag->getParam("SmartSeek", "false").toBool();
        fDrivable = tag->getParam("NoSeek", "true").toBool();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
