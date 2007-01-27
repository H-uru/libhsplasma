#include "plAudioInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plAudioInterface::plAudioInterface(PlasmaVer pv) : plObjInterface(pv) {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    Audible->UnRef();
}

unsigned short plAudioInterface::ClassIndex() { return 0x0011; }

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible = plResManager::inst->readKey(S);
    Audible->Ref();
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    plResManager::inst->writeKey(S, Audible);
}

