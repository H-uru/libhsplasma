#include "plCreatable.h"

/* plCreatable */
plCreatable::plCreatable() { }
plCreatable::~plCreatable() { }

short plCreatable::ClassIndex(PlasmaVer ver) const {
    return pdUnifiedTypeMap::MappedToPlasma(ClassIndex(), ver);
}

bool plCreatable::ClassInstance(short hClass) const { return false; }

const char* plCreatable::ClassName() const {
    return pdUnifiedTypeMap::ClassName(ClassIndex());
}

bool plCreatable::isStub() const { return false; }

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


/* plCreatableStub */
plCreatableStub::plCreatableStub()
              : fClassIdx((short)0x8000), fData(NULL), fDataLen(0) { }

plCreatableStub::plCreatableStub(short hClass, size_t length)
              : fClassIdx(hClass), fDataLen(length) {
    fData = new unsigned char[fDataLen];
}

plCreatableStub::~plCreatableStub() {
    if (fData != NULL)
        delete[] fData;
}

short plCreatableStub::ClassIndex() const { return fClassIdx; }

bool plCreatableStub::isStub() const { return true; }

void plCreatableStub::read(hsStream* S, plResManager* mgr) {
    S->read(fDataLen, fData);
}

void plCreatableStub::write(hsStream* S, plResManager* mgr) {
    S->write(fDataLen, fData);
}

void plCreatableStub::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plCreatableStub");
    prc->writeParam("Type", pdUnifiedTypeMap::ClassName(fClassIdx));
    prc->endTag();
    prc->writeHexStream(fDataLen, fData);
    prc->closeTag();
}

void plCreatableStub::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "plCreatableStub")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fClassIdx = pdUnifiedTypeMap::ClassIndex(tag->getParam("Type", ""));

    if (fData != NULL)
        delete[] fData;
    fDataLen = tag->getContents().getSize();
    fData = new unsigned char[fDataLen];
    tag->readHexStream(fDataLen, fData);
}

void plCreatableStub::IPrcWrite(pfPrcHelper* prc) { }
void plCreatableStub::IPrcParse(const pfPrcTag* tag, plResManager* mgr) { }

const unsigned char* plCreatableStub::getData() const { return fData; }
size_t plCreatableStub::getLength() const { return fDataLen; }
