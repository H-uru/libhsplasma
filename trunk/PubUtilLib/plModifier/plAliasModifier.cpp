#include "plAliasModifier.h"

plAliasModifier::plAliasModifier() { }
plAliasModifier::~plAliasModifier() { }

IMPLEMENT_CREATABLE(plAliasModifier, kAliasModifier, plSingleModifier)

void plAliasModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    size_t len = S->readInt();
    fAlias = S->readStr(len);
}

void plAliasModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fAlias.len());
    S->write(fAlias.len(), fAlias.cstr());
}

void plAliasModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("Alias");
    prc->writeParam("value", fAlias);
    prc->endTag(true);
}
