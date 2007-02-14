#include "plLayerInterface.h"
#include "../plResMgr/plResManager.h"

plLayerInterface::plLayerInterface(PlasmaVer pv) : underLay(NULL) { }

plLayerInterface::~plLayerInterface() {
    if (underLay) underLay->UnRef();
}

short plLayerInterface::ClassIndex() {
    return (ver == pvEoa ? 0x003F : 0x0041);
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
