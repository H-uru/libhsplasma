#include "plModifier.h"

/* plModifier */
plModifier::plModifier(PlasmaVer pv) { }

short plModifier::ClassIndex() { return 0x001E; }
const char* plModifier::ClassName() { return "plModifier"; }


/* plSingleModifier */
plSingleModifier::plSingleModifier(PlasmaVer pv) { }

short plSingleModifier::ClassIndex() { return 0x001F; }
const char* plSingleModifier::ClassName() { return "plSingleModifier"; }

void plSingleModifier::read(hsStream* S) {
    plSynchedObject::read(S);
    flags.read(S);
}

void plSingleModifier::write(hsStream* S) {
    plSynchedObject::write(S);
    flags.write(S);
}

void plSingleModifier::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->writeSimpleTag("ModFlags");
    flags.prcWrite(S, prc);
    prc->closeTag();
}


/* plMultiModifier */
plMultiModifier::plMultiModifier(PlasmaVer pv) { }

short plMultiModifier::ClassIndex() { return 0x0027; }
const char* plMultiModifier::ClassName() { return "plMultiModifier"; }

void plMultiModifier::read(hsStream* S) {
    plSynchedObject::read(S);
    flags.read(S);
}

void plMultiModifier::write(hsStream* S) {
    plSynchedObject::write(S);
    flags.write(S);
}

void plMultiModifier::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->writeSimpleTag("ModFlags");
    flags.prcWrite(S, prc);
    prc->closeTag();
}
