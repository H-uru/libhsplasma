#include "plMultiModifier.h"

plMultiModifier::plMultiModifier(PlasmaVer pv) { }

short plMultiModifier::ClassIndex() { return 0x0027; }

void plMultiModifier::read(hsStream* S) {
    plSynchedObject::read(S);
    flags.read(S);
}

void plMultiModifier::write(hsStream* S) {
    plSynchedObject::write(S);
    flags.write(S);
}
