#include "plCoordinateInterface.h"

plCoordinateInterface::plCoordinateInterface() /* : Member60(0) */ {
    LocalToParent.Identity();
    ParentToLocal.Identity();
    LocalToWorld.Identity();
    WorldToLocal.Identity();
}

plCoordinateInterface::~plCoordinateInterface() { }

plCoordinateInterface* plCoordinateInterface::getRoot() {
    plCoordinateInterface * cur = this;
    while (cur->Parent) cur = cur->Parent;
    return cur;
}

void plCoordinateInterface::read(hsStream *S) {
    plObjInterface::read(S);
    
    LocalToParent.read(S);
    ParentToLocal.read(S);
    LocalToWorld.read(S);
    WorldToLocal.read(S);
    SceneObjects.read(S);
}

void plCoordinateInterface::write(hsStream *S) {
    plObjInterface::write(S);

    LocalToParent.write(S);
    ParentToLocal.write(S);
    LocalToWorld.write(S);
    WorldToLocal.write(S);
    SceneObjects.write(S);
}

