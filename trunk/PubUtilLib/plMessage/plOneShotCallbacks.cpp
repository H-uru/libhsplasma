#include "plOneShotCallbacks.h"

plOneShotCallbacks::plOneShotCallbacks() { }
plOneShotCallbacks::~plOneShotCallbacks() { }

void plOneShotCallbacks::read(hsStream* S, plResManager* mgr) {
    fCallbacks.setSize(S->readInt());
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        fCallbacks[i].fMarker = S->readSafeStr();
        fCallbacks[i].fReceiver = mgr->readKey(S);
        fCallbacks[i].fUser = S->readShort();
    }
}

void plOneShotCallbacks::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fCallbacks.getSize());
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        S->writeSafeStr(fCallbacks[i].fMarker);
        mgr->writeKey(S, fCallbacks[i].fReceiver);
        S->writeShort(fCallbacks[i].fUser);
    }
}

void plOneShotCallbacks::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plOneShotCallbacks");
    for (size_t i=0; i<fCallbacks.getSize(); i++) {
        prc->startTag("plOneShotCallback");
        prc->writeParam("Marker", fCallbacks[i].fMarker);
        prc->writeParam("User", fCallbacks[i].fUser);
        prc->endTag();
        fCallbacks[i].fReceiver->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}
