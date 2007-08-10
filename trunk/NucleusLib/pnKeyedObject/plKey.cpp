#include <stdlib.h>
#include <string.h>
#include "plKey.h"

plKey::plKey() : uoid(), objPtr(NULL), exists(true), fileOff(0), objSize(0) { }
plKey::~plKey() { }

bool plKey::operator==(plKey &other) {
    return (uoid == other.uoid);
}

const char* plKey::toString() {
    return uoid.toString();
}

void plKey::read(hsStream *S) {
    uoid.read(S);
    fileOff = S->readInt();
    objSize = S->readInt();
}

void plKey::write(hsStream *S) {
    uoid.write(S);
    S->writeInt(fileOff);
    S->writeInt(objSize);
}

void plKey::readUoid(hsStream* S) {
    uoid.read(S);
}

void plKey::writeUoid(hsStream* S) {
    uoid.write(S);
}

void plKey::prcWrite(pfPrcHelper* prc) {
    if (exists) {
        uoid.prcWrite(prc);
    } else {
        prc->startTag("plKey");
        prc->writeParam("null", true);
        prc->endTag(true);
    }
}

short plKey::getType() { return uoid.getType(); }
PageID& plKey::getPageID() { return uoid.getPageID(); }
const char* plKey::getName() { return uoid.getName(); }
void plKey::setID(unsigned int id) { uoid.setID(id); }
unsigned int plKey::getID() { return uoid.getID(); }

/*
void plKey::readRef(hsStream *S) {
    exists = true;
    if (S->getVer() != pvEoa)
        exists = S->readBool();
    if (exists) read(S);
}

void plKey::writeRef(hsStream *S) {
    if (S->getVer() != pvEoa)
        S->writeBool(exists);
    if (exists) write(S);
}
*/

