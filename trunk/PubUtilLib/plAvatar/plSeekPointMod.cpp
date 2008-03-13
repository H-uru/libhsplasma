#include "plSeekPointMod.h"

plSeekPointMod::plSeekPointMod() { }
plSeekPointMod::~plSeekPointMod() { }

IMPLEMENT_CREATABLE(plSeekPointMod, kSeekPointMod, plMultiModifier)

void plSeekPointMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    size_t len = S->readInt();
    fName = S->readStr(len);
}

void plSeekPointMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    S->writeInt(fName.len());
    S->writeStr(fName);
}

void plSeekPointMod::prcWrite(pfPrcHelper* prc) {
    plMultiModifier::prcWrite(prc);

    prc->startTag("SeekPointModParams");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}
