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

void plLayerInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BaseLayer") {
        if (tag->hasChildren())
            fUnderLay = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
