#include "plModifier.h"

/* plSingleModifier */
void plSingleModifier::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fFlags.read(S);
}

void plSingleModifier::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    fFlags.write(S);
}

void plSingleModifier::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ModFlags");
    fFlags.prcWrite(prc);
    prc->closeTag();
}

void plSingleModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ModFlags") {
        if (tag->hasChildren())
            fFlags.prcParse(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}


/* plMultiModifier */
void plMultiModifier::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    fFlags.read(S);
}

void plMultiModifier::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    fFlags.write(S);
}

void plMultiModifier::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ModFlags");
    fFlags.prcWrite(prc);
    prc->closeTag();
}

void plMultiModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ModFlags") {
        if (tag->hasChildren())
            fFlags.prcParse(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
