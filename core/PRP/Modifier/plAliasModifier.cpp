#include "plAliasModifier.h"

void plAliasModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    size_t len = S->readInt();
    fAlias = S->readStr(len);
}

void plAliasModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fAlias.len());
    S->writeStr(fAlias);
}

void plAliasModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("Alias");
    prc->writeParam("value", fAlias);
    prc->endTag(true);
}

void plAliasModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Alias") {
        fAlias = tag->getParam("value", "");
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
