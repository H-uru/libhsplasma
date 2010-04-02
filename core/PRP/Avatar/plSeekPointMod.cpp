#include "plSeekPointMod.h"

void plSeekPointMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    size_t len = S->readInt();
    fName = S->readStr(len);
}

void plSeekPointMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    S->writeInt(fName.len());
    S->writeStr(fName);
}

void plSeekPointMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("SeekPoint");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}

void plSeekPointMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SeekPoint") {
        fName = tag->getParam("Name", "");
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
