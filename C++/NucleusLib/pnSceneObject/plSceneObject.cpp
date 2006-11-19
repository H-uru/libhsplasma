#include "plSceneObject.h"

plSceneObject::plSceneObject() {
    DrawIntf = new plKey();
    SimIntf = new plKey();
    CoordIntf = new plKey();
    AudioIntf = new plKey();
    SceneNode = new plKey();
}

plSceneObject::~plSceneObject() {
    delete DrawIntf;
    delete SimIntf;
    delete CoordIntf;
    delete AudioIntf;
    delete SceneNode;
}

void plSceneObject::read(hsStream *S) {
    plSynchedObject::read(S);

    DrawIntf->readRef(S);
    SimIntf->readRef(S);
    CoordIntf->readRef(S);
    AudioIntf->readRef(S);
    Interfaces.read(S);
    Modifiers.read(S);
    SceneNode->readRef(S);
}

void plSceneObject::write(hsStream *S) {
    plSynchedObject::write(S);

    DrawIntf->writeRef(S);
    SimIntf->writeRef(S);
    CoordIntf->writeRef(S);
    AudioIntf->writeRef(S);
    Interfaces.write(S);
    Modifiers.write(S);
    SceneNode->writeRef(S);
}

