#include "plAnimEventModifier.h"

plAnimEventModifier::plAnimEventModifier() : fCallback(NULL), fDisabled(false) { }

plAnimEventModifier::~plAnimEventModifier() {
    if (fCallback != NULL)
        delete fCallback;
}

IMPLEMENT_CREATABLE(plAnimEventModifier, kAnimEventModifier, plSingleModifier)

void plAnimEventModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    fCallback = plMessage::Convert(mgr->ReadCreatable(S));
}

void plAnimEventModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    mgr->WriteCreatable(S, fCallback);
}

void plAnimEventModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Callback");
    fCallback->prcWrite(prc); prc->closeTag();
    prc->closeTag();
}
