#include "plObjInterface.h"

plObjInterface::plObjInterface() {
    Owner = new plKey();
}

plObjInterface::~plObjInterface() {
    delete Owner;
}

bool plObjInterface::msgReceive(plMessage msg) {
    // Later
    return false;
}

void plObjInterface::read(hsStream *S) {
    plSynchedObject::read(S);
    Owner->readRef(S);
    Properties.read(S);
}

void plObjInterface::write(hsStream *S) {
    plSynchedObject::write(S);
    Owner->writeRef(S);
    Properties.write(S);
}

