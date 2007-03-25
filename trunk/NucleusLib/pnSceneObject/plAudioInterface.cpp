#include "plAudioInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plAudioInterface::plAudioInterface(PlasmaVer pv) {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    Audible->UnRef();
}

short plAudioInterface::ClassIndex() { return 0x0011; }
const char* plAudioInterface::ClassName() { return "plAudioInterface"; }

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible = plResManager::inst->readKey(S);
    Audible->Ref();
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    plResManager::inst->writeKey(S, Audible);
}

void plAudioInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plObjInterface::prcWrite(S, prc);

    prc->writeSimpleTag("Audible");
    Audible->prcWrite(S, prc);
    prc->closeTag();
}
