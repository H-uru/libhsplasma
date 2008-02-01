#include "plAGModifier.h"

plAGModifier::plAGModifier() : fAutoApply(true), fEnabled(true) { }
plAGModifier::~plAGModifier() { }

IMPLEMENT_CREATABLE(plAGModifier, kAGModifier, plSingleModifier)

void plAGModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);
    fChannelName = S->readSafeStr();
}

void plAGModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);
    S->writeSafeStr(fChannelName);
}

void plAGModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("AGModifierParams");
    prc->writeParam("ChannelName", fChannelName);
    prc->endTag(true);
}
