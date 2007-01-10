#include "hsKeyedObject.h"

hsKeyedObject::hsKeyedObject(PlasmaVer pv) { }
hsKeyedObject::~hsKeyedObject() { }

void hsKeyedObject::read(hsStream * S) {
    key.read(S);
}

void hsKeyedObject::write(hsStream * S) {
    key.write(S);
}

