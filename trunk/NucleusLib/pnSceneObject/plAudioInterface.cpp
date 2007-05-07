#include "plAudioInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plAudioInterface::plAudioInterface() {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    Audible->UnRef();
}

short plAudioInterface::ClassIndex() { return kAudioInterface; }
short plAudioInterface::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kAudioInterface, ver);
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

void plAudioInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plObjInterface::prcWrite(S, prc);

    prc->writeSimpleTag("Audible");
    Audible->prcWrite(S, prc);
    prc->closeTag();
}
