#include "plSDL.h"

/* plSDL */
unsigned int plSDL::VariableLengthRead(hsStream* S, size_t size) {
    if (size < 0x100)
        return S->readByte();
    else if (size < 0x10000)
        return S->readShort();
    else
        return S->readInt();
}

void plSDL::VariableLengthWrite(hsStream* S, size_t size, unsigned int value) {
    if (size < 0x100)
        S->writeByte(value);
    else if (size < 0x10000)
        S->writeShort(value);
    else
        S->writeInt(value);
}


/* plSDLCreatableStub */
plSDLCreatableStub::plSDLCreatableStub()
                  : fClassIdx(0x8000), fData(NULL), fDataLen(0) { }

plSDLCreatableStub::plSDLCreatableStub(short hClass, size_t length)
                  : fClassIdx(hClass), fDataLen(length) {
    fData = new unsigned char[fDataLen];
}

plSDLCreatableStub::~plSDLCreatableStub() {
    if (fData != NULL)
        delete[] fData;
}

short plSDLCreatableStub::ClassIndex() const { return fClassIdx; }

void plSDLCreatableStub::read(hsStream* S, plResManager* mgr) {
    S->read(fDataLen, fData);
}

void plSDLCreatableStub::write(hsStream* S, plResManager* mgr) {
    S->write(fDataLen, fData);
}

void plSDLCreatableStub::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSDLCreatableStub");
    prc->writeParam("ClassIdx", fClassIdx);
    prc->endTag();
    prc->writeHexStream(fDataLen, fData);
    prc->closeTag();
}

void plSDLCreatableStub::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "plSDLCreatableStub")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fClassIdx = tag->getParam("ClassIdx", "0").toInt();

    if (fData != NULL)
        delete[] fData;
    fDataLen = tag->getContents().getSize();
    fData = new unsigned char[fDataLen];
    tag->readHexStream(fDataLen, fData);
}

void plSDLCreatableStub::IPrcWrite(pfPrcHelper* prc) { }
void plSDLCreatableStub::IPrcParse(const pfPrcTag* tag, plResManager* mgr) { }

short plSDLCreatableStub::getClassIdx() const { return fClassIdx; }
unsigned char* plSDLCreatableStub::getData() const { return fData; }
size_t plSDLCreatableStub::getLength() const { return fDataLen; }
