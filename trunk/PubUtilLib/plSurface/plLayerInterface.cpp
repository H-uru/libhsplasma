#include "plLayerInterface.h"

plLayerInterface::plLayerInterface() { }

plLayerInterface::~plLayerInterface() { }

IMPLEMENT_CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

void plLayerInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fUnderLay = mgr->readKey(S);
}

void plLayerInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fUnderLay);
}

void plLayerInterface::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("BaseLayer");
    fUnderLay->prcWrite(prc);
    prc->closeTag();
}
