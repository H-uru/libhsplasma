#include "plDetectorModifier.h"

/* plDetectorModifier */
plDetectorModifier::plDetectorModifier() { }
plDetectorModifier::~plDetectorModifier() { }

IMPLEMENT_CREATABLE(plDetectorModifier, kDetectorModifier, plSingleModifier)

void plDetectorModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    fRemoteMod = mgr->readKey(S);
    fProxyKey = mgr->readKey(S);
}

void plDetectorModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    mgr->writeKey(S, fRemoteMod);
    mgr->writeKey(S, fProxyKey);
}

void plDetectorModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RemoteMod");
    fRemoteMod->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Proxy");
    fProxyKey->prcWrite(prc);
    prc->closeTag();
}


/* plPickingDetector */
plPickingDetector::plPickingDetector() { }
plPickingDetector::~plPickingDetector() { }

IMPLEMENT_CREATABLE(plPickingDetector, kPickingDetector, plDetectorModifier)
