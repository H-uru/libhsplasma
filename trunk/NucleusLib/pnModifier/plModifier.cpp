#include "plModifier.h"

/* plModifier */
plModifier::plModifier() { }

short plModifier::ClassIndex() { return kModifier; }
short plModifier::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kModifier, ver);
}


/* plSingleModifier */
plSingleModifier::plSingleModifier() { }

short plSingleModifier::ClassIndex() { return kSingleModifier; }
short plSingleModifier::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kSingleModifier, ver);
}

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
plMultiModifier::plMultiModifier() { }

short plMultiModifier::ClassIndex() { return kMultiModifier; }
short plMultiModifier::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kMultiModifier, ver);
}

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
