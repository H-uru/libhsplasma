#include "plCoordinateInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plCoordinateInterface::plCoordinateInterface(PlasmaVer pv) {
    LocalToParent.Identity();
    ParentToLocal.Identity();
    LocalToWorld.Identity();
    WorldToLocal.Identity();
}

plCoordinateInterface::~plCoordinateInterface() {
    for (int i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i]->UnRef();
}

short plCoordinateInterface::ClassIndex() { return 0x0015; }
const char* plCoordinateInterface::ClassName() { return "plCoordinateInterface"; }

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

    LocalToParent.write(S);
    ParentToLocal.write(S);
    LocalToWorld.write(S);
    WorldToLocal.write(S);

    S->writeInt(SceneObjects.getSize());
    for (int i=0; i<SceneObjects.getSize(); i++)
        plResManager::inst->writeKey(S, SceneObjects[i]);
}

void plCoordinateInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plObjInterface::prcWrite(S, prc);

    prc->writeSimpleTag("LocalToParent");
    LocalToParent.prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    ParentToLocal.prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToWorld");
    LocalToWorld.prcWrite(S, prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    WorldToLocal.prcWrite(S, prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneObjects");
    for (int i=0; i<SceneObjects.getSize(); i++)
        SceneObjects[i]->prcWrite(S, prc);
    prc->closeTag();
}
