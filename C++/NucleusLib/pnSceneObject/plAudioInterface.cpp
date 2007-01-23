#include "plAudioInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plAudioInterface::plAudioInterface(PlasmaVer pv) {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    Audible->UnRef();
}

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible = plResManager::inst->readKey(S);
    Audible->Ref();
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    plResManager::inst->writeKey(S, Audible);
}

