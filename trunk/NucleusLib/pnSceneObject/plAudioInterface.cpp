#include "plAudioInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plAudioInterface::plAudioInterface() { }
plAudioInterface::~plAudioInterface() { }

IMPLEMENT_CREATABLE(plAudioInterface, kAudioInterface, plObjInterface)

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible = plResManager::inst->readKey(S);
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    plResManager::inst->writeKey(S, Audible);
}

void plAudioInterface::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->writeSimpleTag("Audible");
    Audible->prcWrite(prc);
    prc->closeTag();
}
