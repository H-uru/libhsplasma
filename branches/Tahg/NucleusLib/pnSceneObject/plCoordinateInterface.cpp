#include "plCoordinateInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plCoordinateInterface::plCoordinateInterface(PlasmaVer pv) {
    LocalToParent = hsMatrix44::IdentityMatrix();
    ParentToLocal = hsMatrix44::IdentityMatrix();
    LocalToWorld = hsMatrix44::IdentityMatrix();
    WorldToLocal = hsMatrix44::IdentityMatrix();
}

plCoordinateInterface::~plCoordinateInterface() {
    for (int i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i]->UnRef();
}

unsigned short plCoordinateInterface::ClassIndex() { return 0x0015; }

plCoordinateInterface* plCoordinateInterface::getRoot() {
    plCoordinateInterface * cur = this;
    while (cur->Parent) cur = cur->Parent;
    return cur;
}

void plCoordinateInterface::read(hsStream *S) {
    plObjInterface::read(S);
    
    LocalToParent.Read(S);
    ParentToLocal.Read(S);
    LocalToWorld.Read(S);
    WorldToLocal.Read(S);

    int soCount = S->readInt();
    SceneObjects.clear();
    SceneObjects.setSize(soCount);
    for (int i=0; i<soCount; i++) {
        SceneObjects[i] = plResManager::inst->readKey(S);
        SceneObjects[i]->Ref();
    }
}

void plCoordinateInterface::write(hsStream *S) {
    plObjInterface::write(S);

    LocalToParent.Write(S);
    ParentToLocal.Write(S);
    LocalToWorld.Write(S);
    WorldToLocal.Write(S);

    S->writeInt(SceneObjects.getSize());
    for (int i=0; i<SceneObjects.getSize(); i++)
        plResManager::inst->writeKey(S, SceneObjects[i]);
}

