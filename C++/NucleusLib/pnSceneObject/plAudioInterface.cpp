#include "plAudioInterface.h"

plAudioInterface::plAudioInterface(PlasmaVer pv) {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    Audible->UnRef();
}

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible->readRef(S);
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    Audible->writeRef(S);
}

