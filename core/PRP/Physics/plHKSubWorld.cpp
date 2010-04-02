#include "plHKSubWorld.h"

void plHKSubWorld::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fPosition.read(S);
}

void plHKSubWorld::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    fPosition.write(S);
}

void plHKSubWorld::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Position");
    fPosition.prcWrite(prc);
    prc->closeTag();
}

void plHKSubWorld::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Position") {
        if (tag->hasChildren())
            fPosition.prcParse(tag);
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
