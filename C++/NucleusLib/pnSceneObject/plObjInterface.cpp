#include "plObjInterface.h"

plObjInterface::plObjInterface() {
    SceneObj = new plKey();
}

plObjInterface::~plObjInterface() {
    delete SceneObj;
}

void plObjInterface::read(hsStream *S) {
    plSynchedObject::read(S);
    SceneObj->read(S);
    ifFlags.read(S);
}

void plObjInterface::write(hsStream *S) {
    plSynchedObject::write(S);
    SceneObj->write(S);
    ifFlags.write(S);
}

