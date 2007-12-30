#include "plOneShotMod.h"

plOneShotMod::plOneShotMod()
            : fDrivable(false), fReversible(false), fSeekDuration(0.0f),
              fSmartSeek(0.0f), fNoSeek(true) { }

plOneShotMod::~plOneShotMod() { }

IMPLEMENT_CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

void plOneShotMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fAnimName = S->readSafeStr();
    fSeekDuration = S->readFloat();
    fDrivable = S->readBool();
    fReversible = S->readBool();
    fSmartSeek = (S->readBool() ? 1.0f : 0.0f);
    fNoSeek = S->readBool();
}

void plOneShotMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    S->writeSafeStr(fAnimName);
    S->writeFloat(fSeekDuration);
    S->writeBool(fDrivable);
    S->writeBool(fReversible);
    S->writeBool(fSmartSeek == 0.0f ? false : true);
    S->writeBool(fNoSeek);
}

void plOneShotMod::prcWrite(pfPrcHelper* prc) {
    plMultiModifier::prcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("SeekDuration", fSeekDuration);
    prc->writeParam("Drivable", fDrivable);
    prc->writeParam("Reversible", fReversible);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("NoSeek", fNoSeek);
    prc->endTag(true);
}
