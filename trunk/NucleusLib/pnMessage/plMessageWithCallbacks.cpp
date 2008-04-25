#include "plMessageWithCallbacks.h"

plMessageWithCallbacks::plMessageWithCallbacks() { }

plMessageWithCallbacks::~plMessageWithCallbacks() {
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        if (fCallbacks[i] != NULL)
            delete fCallbacks[i];
    }
}

IMPLEMENT_CREATABLE(plMessageWithCallbacks, kMessageWithCallbacks, plMessage)

void plMessageWithCallbacks::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCallbacks.setSizeNull(S->readInt());
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        fCallbacks[i] = plMessage::Convert(mgr->ReadCreatable(S));
        if (fCallbacks[i] == NULL)
            throw hsNotImplementedException(__FILE__, __LINE__, "Callback Message");
    }
}

void plMessageWithCallbacks::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fCallbacks.getSize());
    for (size_t i=0; i<fCallbacks.getSize(); i++)
        mgr->WriteCreatable(S, fCallbacks[i]);
}

void plMessageWithCallbacks::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Callbacks");
    for (size_t i=0; i<fCallbacks.getSize(); i++)
        fCallbacks[i]->prcWrite(prc);
    prc->closeTag();
}
