#include "plLayerInterface.h"
#include "../plResMgr/plResManager.h"

plLayerInterface::plLayerInterface() : underLay(NULL) { }

plLayerInterface::~plLayerInterface() {
    if (underLay) underLay->UnRef();
}

short plLayerInterface::ClassIndex() { return kLayerInterface; }
short plLayerInterface::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kLayerInterface, ver);
}

void plLayerInterface::read(hsStream* S) {
    plSynchedObject::read(S);
    underLay = plResManager::inst->readKey(S);
    underLay->Ref();
}

void plLayerInterface::write(hsStream* S) {
    plSynchedObject::write(S);
    plResManager::inst->writeKey(S, underLay);
}

void plLayerInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plSynchedObject::prcWrite(S, prc);

    prc->writeSimpleTag("UnderLay");
    underLay->prcWrite(S, prc);
    prc->closeTag();
}
