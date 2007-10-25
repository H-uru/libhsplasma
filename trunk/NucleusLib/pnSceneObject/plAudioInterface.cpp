#include "plAudioInterface.h"

plAudioInterface::plAudioInterface() { }
plAudioInterface::~plAudioInterface() { }

IMPLEMENT_CREATABLE(plAudioInterface, kAudioInterface, plObjInterface)

void plAudioInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    Audible = mgr->readKey(S);
}

void plAudioInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->writeKey(S, Audible);
}

void plAudioInterface::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->writeSimpleTag("Audible");
    Audible->prcWrite(prc);
    prc->closeTag();
}
