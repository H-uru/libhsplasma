#include "hsKeyedObject.h"

hsKeyedObject::hsKeyedObject(PlasmaVer pv) : koFlags(0) { }
hsKeyedObject::~hsKeyedObject() { }

void hsKeyedObject::read(hsStream * S) {
    myKey.read(S);
}

void hsKeyedObject::write(hsStream * S) {
    myKey.write(S);
}

