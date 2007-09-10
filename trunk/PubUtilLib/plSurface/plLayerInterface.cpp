#include "plLayerInterface.h"
#include "../plResMgr/plResManager.h"

plLayerInterface::plLayerInterface() { }
plLayerInterface::~plLayerInterface() { }

IMPLEMENT_CREATABLE(plLayerInterface, kLayerInterface, plSynchedObject)

void plLayerInterface::read(hsStream* S) {
    plSynchedObject::read(S);
    underLay = plResManager::inst->readKey(S);
}

void plLayerInterface::write(hsStream* S) {
    plSynchedObject::write(S);
    plResManager::inst->writeKey(S, underLay);
}

void plLayerInterface::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->writeSimpleTag("UnderLay");
    underLay->prcWrite(prc);
    prc->closeTag();
}
