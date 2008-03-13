#include "plSittingModifier.h"

plSittingModifier::plSittingModifier() : fMiscFlags(0) { }
plSittingModifier::~plSittingModifier() { }

IMPLEMENT_CREATABLE(plSittingModifier, kSittingModifier, plSingleModifier)

void plSittingModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fMiscFlags = S->readByte();
    fNotifyKeys.setSize(S->readInt());
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        fNotifyKeys[i] = mgr->readKey(S);
}

void plSittingModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(fMiscFlags);
    S->writeInt(fNotifyKeys.getSize());
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        mgr->writeKey(S, fNotifyKeys[i]);
}

void plSittingModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("SittingModifierParams");
    prc->writeParam("MiscFlags", fMiscFlags);
    prc->endTag(true);

    prc->writeSimpleTag("NotifyKeys");
    for (size_t i=0; i<fNotifyKeys.getSize(); i++)
        fNotifyKeys[i]->prcWrite(prc);
    prc->closeTag();
}
