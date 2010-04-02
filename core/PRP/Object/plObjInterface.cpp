#include "plObjInterface.h"

plObjInterface::plObjInterface() {
    fProps.setName(kDisable, "kDisable");
}

void plObjInterface::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fOwner = mgr->readKey(S);
    fProps.read(S);
}

void plObjInterface::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    mgr->writeKey(S, fOwner);
    fProps.write(S);
}

void plObjInterface::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Owner");
    fOwner->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Properties");
    fProps.prcWrite(prc);
    prc->closeTag();
}

void plObjInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Owner") {
        if (tag->hasChildren())
            fOwner = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Properties") {
        if (tag->hasChildren())
            fProps.prcParse(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
