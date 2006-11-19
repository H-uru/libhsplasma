#include "plAudioInterface.h"

plAudioInterface::plAudioInterface() {
    Audible = new plKey();
}

plAudioInterface::~plAudioInterface() {
    delete Audible;
}

void plAudioInterface::read(hsStream *S) {
    plObjInterface::read(S);
    Audible->readRef(S);
}

void plAudioInterface::write(hsStream *S) {
    plObjInterface::write(S);
    Audible->writeRef(S);
}

