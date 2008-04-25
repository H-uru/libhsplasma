#include "plCoordinateInterface.h"

plCoordinateInterface::plCoordinateInterface() {
    fLocalToParent.Reset();
    fParentToLocal.Reset();
    fLocalToWorld.Reset();
    fWorldToLocal.Reset();

    fProps.setName(kDisable, "kDisable");
    fProps.setName(kCanEverDelayTransform, "kCanEverDelayTransform");
    fProps.setName(kDelayedTransformEval, "kDelayedTransformEval");
}

plCoordinateInterface::~plCoordinateInterface() { }

IMPLEMENT_CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)

void plCoordinateInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    
    fLocalToParent.read(S);
    fParentToLocal.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);

    fChildren.setSize(S->readInt());
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plCoordinateInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    fLocalToParent.write(S);
    fParentToLocal.write(S);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);

    S->writeInt(fChildren.getSize());
    for (size_t i=0; i<fChildren.getSize(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plCoordinateInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("LocalToParent");
    fLocalToParent.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    fParentToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToWorld");
    fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}
