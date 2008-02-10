#include "plRelevanceRegion.h"

plRelevanceRegion::plRelevanceRegion() : fMgrIdx(-1) { }
plRelevanceRegion::~plRelevanceRegion() { }

IMPLEMENT_CREATABLE(plRelevanceRegion, kRelevanceRegion, plObjInterface)

void plRelevanceRegion::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fRegion = mgr->readKey(S);
}

void plRelevanceRegion::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fRegion);
}

void plRelevanceRegion::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->writeSimpleTag("Region");
    fRegion->prcWrite(prc);
    prc->closeTag();
}
