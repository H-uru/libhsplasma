#include "hsKeyedObject.h"

hsKeyedObject::hsKeyedObject() { }
hsKeyedObject::~hsKeyedObject() { }

void hsKeyedObject::read(hsStream * S) {
    key.read(S);
}

void hsKeyedObject::write(hsStream * S) {
    key.write(S);
}

const char* hsKeyedObject::getTypeName() { return "hsKeyedObject"; }
const int hsKeyedObject::getTypeNum() { return 2; }

