#include "plLayerInterface.h"

plLayerInterface::plLayerInterface() : fState(NULL) { }

plLayerInterface::~plLayerInterface() {
    if (fState) delete fState;
}

IMPLEMENT_CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

void plLayerInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fUnderLay = mgr->readKey(S);
}

void plLayerInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fUnderLay);
}

void plLayerInterface::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->writeSimpleTag("UnderLay");
    fUnderLay->prcWrite(prc);
    prc->closeTag();
}
