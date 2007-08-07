#include "plCreatable.h"

plCreatable::plCreatable() { }
plCreatable::~plCreatable() { }

short plCreatable::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(ClassIndex(), ver);
}

bool plCreatable::ClassInstance(short hClass) { return false; }

const char* plCreatable::ClassName() {
    return pdUnifiedTypeMap::ClassName(ClassIndex());
}

void plCreatable::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag(ClassName());
}
