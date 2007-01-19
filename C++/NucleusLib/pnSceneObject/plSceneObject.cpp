#include "plSceneObject.h"

plSceneObject::plSceneObject(PlasmaVer pv) {
    DrawIntf = new plKey();
    SimIntf = new plKey();
    CoordIntf = new plKey();
    AudioIntf = new plKey();
    SceneNode = new plKey();
}

plSceneObject::~plSceneObject() {
    DrawIntf->UnRef();
    SimIntf->UnRef();
    CoordIntf->UnRef();
    AudioIntf->UnRef();
    SceneNode->UnRef();
}

void plSceneObject::read(hsStream *S) {
    plSynchedObject::read(S);

    DrawIntf->readRef(S);
    SimIntf->readRef(S);
    CoordIntf->readRef(S);
    AudioIntf->readRef(S);

    Interfaces.setSize(S->readInt());
    for (int i=0; i<Interfaces.getSize(); i++)
        Interfaces[i].readRef(S);
    Modifiers.setSize(S->readInt());
    for (int i=0; i<Modifiers.getSize(); i++)
        Modifiers[i].readRef(S);

    SceneNode->readRef(S);
}

void plSceneObject::write(hsStream *S) {
    plSynchedObject::write(S);

    DrawIntf->writeRef(S);
    SimIntf->writeRef(S);
    CoordIntf->writeRef(S);
    AudioIntf->writeRef(S);

    S->writeInt(Interfaces.getSize());
    for (int i=0; i<Interfaces.getSize(); i++)
        Interfaces[i].writeRef(S);
    S->writeInt(Modifiers.getSize());
    for (int i=0; i<Modifiers.getSize(); i++)
        Modifiers[i].writeRef(S);
    SceneNode->writeRef(S);
}

