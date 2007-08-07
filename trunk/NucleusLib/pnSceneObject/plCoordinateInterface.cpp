#include "plCoordinateInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plCoordinateInterface::plCoordinateInterface() {
    LocalToParent.Reset();
    ParentToLocal.Reset();
    LocalToWorld.Reset();
    WorldToLocal.Reset();
}

plCoordinateInterface::~plCoordinateInterface() {
    for (int i=0; i<Children.getSize(); i++)
        Children[i]->UnRef();
}

IMPLEMENT_CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)

plCoordinateInterface* plCoordinateInterface::getRoot() {
    plCoordinateInterface* cur = this;
    while (cur->Parent) cur = cur->Parent;
    return cur;
}

void plCoordinateInterface::read(hsStream* S) {
    plObjInterface::read(S);
    
    LocalToParent.read(S);
    ParentToLocal.read(S);
    LocalToWorld.read(S);
    WorldToLocal.read(S);

    int soCount = S->readInt();
    Children.clear();
    Children.setSize(soCount);
    for (int i=0; i<soCount; i++) {
        Children[i] = plResManager::inst->readKey(S);
        Children[i]->Ref();
    }
}

void plCoordinateInterface::write(hsStream* S) {
    plObjInterface::write(S);

    LocalToParent.write(S);
    ParentToLocal.write(S);
    LocalToWorld.write(S);
    WorldToLocal.write(S);

    S->writeInt(Children.getSize());
    for (int i=0; i<Children.getSize(); i++)
        plResManager::inst->writeKey(S, Children[i]);
}

void plCoordinateInterface::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->writeSimpleTag("LocalToParent");
    LocalToParent.prcWrite(prc);
    ParentToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToWorld");
    LocalToWorld.prcWrite(prc);
    WorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Children");
    for (int i=0; i<Children.getSize(); i++)
        Children[i]->prcWrite(prc);
    prc->closeTag();
}
