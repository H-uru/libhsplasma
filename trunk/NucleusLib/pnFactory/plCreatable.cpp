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
    IPrcWrite(prc);
    prc->closeTag();
}

void plCreatable::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        IPrcParse(child, mgr);
        child = child->getNextSibling();
    }
}

void plCreatable::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}
