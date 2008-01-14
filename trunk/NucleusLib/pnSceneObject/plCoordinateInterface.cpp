#include "plCoordinateInterface.h"

plCoordinateInterface::plCoordinateInterface() {
    LocalToParent.Reset();
    ParentToLocal.Reset();
    LocalToWorld.Reset();
    WorldToLocal.Reset();

    Props.setName(kDisable, "kDisable");
    Props.setName(kCanEverDelayTransform, "kCanEverDelayTransform");
    Props.setName(kDelayedTransformEval, "kDelayedTransformEval");
}

plCoordinateInterface::~plCoordinateInterface() { }

IMPLEMENT_CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)

plCoordinateInterface* plCoordinateInterface::getRoot() {
    plCoordinateInterface* cur = this;
    while (cur->Parent) cur = cur->Parent;
    return cur;
}

void plCoordinateInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    
    LocalToParent.read(S);
    ParentToLocal.read(S);
    LocalToWorld.read(S);
    WorldToLocal.read(S);

    Children.clear();
    Children.setSize(S->readInt());
    for (size_t i=0; i<Children.getSize(); i++)
        Children[i] = mgr->readKey(S);
}

void plCoordinateInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    LocalToParent.write(S);
    ParentToLocal.write(S);
    LocalToWorld.write(S);
    WorldToLocal.write(S);

    S->writeInt(Children.getSize());
    for (size_t i=0; i<Children.getSize(); i++)
        mgr->writeKey(S, Children[i]);
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
    for (size_t i=0; i<Children.getSize(); i++)
        Children[i]->prcWrite(prc);
    prc->closeTag();
}
