#include "plCreatable.h"

plCreatable::plCreatable() { }
plCreatable::~plCreatable() { }

short plCreatable::ClassIndex(PlasmaVer ver) const {
    return pdUnifiedTypeMap::MappedToPlasma(ClassIndex(), ver);
}

bool plCreatable::ClassInstance(short hClass) const { return false; }

const char* plCreatable::ClassName() const {
    return pdUnifiedTypeMap::ClassName(ClassIndex());
}

void plCreatable::read(hsStream* S, plResManager* mgr) { }
void plCreatable::write(hsStream* S, plResManager* mgr) { }

void plCreatable::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag(ClassName());
}
