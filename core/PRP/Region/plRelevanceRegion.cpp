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

void plRelevanceRegion::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Region");
    fRegion->prcWrite(prc);
    prc->closeTag();
}

void plRelevanceRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Region") {
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
