#include "plVisRegion.h"

plVisRegion::plVisRegion() {
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kIsNot, "kIsNot");
    fProps.setName(kReplaceNormal, "kReplaceNormal");
    fProps.setName(kDisableNormal, "kDisableNormal");
}

plVisRegion::~plVisRegion() { }

IMPLEMENT_CREATABLE(plVisRegion, kVisRegion, plObjInterface)

void plVisRegion::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fRegion = mgr->readKey(S);
    fVisMgr = mgr->readKey(S);
}

void plVisRegion::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, fRegion);
    mgr->writeKey(S, fVisMgr);
}

void plVisRegion::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Region");
    fRegion->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("VisMgr");
    fVisMgr->prcWrite(prc);
    prc->closeTag();
}

void plVisRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Region") {
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "VisMgr") {
        if (tag->hasChildren())
            fVisMgr = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
