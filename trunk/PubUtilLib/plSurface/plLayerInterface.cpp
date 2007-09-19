#include "plLayerInterface.h"
#include "../plResMgr/plResManager.h"

plLayerInterface::plLayerInterface() { }
plLayerInterface::~plLayerInterface() { }

IMPLEMENT_CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

void plLayerInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    underLay = mgr->readKey(S);
}

void plLayerInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, underLay);
}

void plLayerInterface::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->writeSimpleTag("UnderLay");
    underLay->prcWrite(prc);
    prc->closeTag();
}
