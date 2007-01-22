#include "plCreatable.h"

plCreatable::plCreatable(PlasmaVer pv) {
    setVersion(pv);
}

plCreatable::~plCreatable() { }

short plCreatable::ClassIndex() { return -1; }

PlasmaVer plCreatable::getVersion() { return ver; }
void plCreatable::setVersion(PlasmaVer pv, bool mutate) { ver = pv; }

void plCreatable::read(hsStream *S) { }
void plCreatable::write(hsStream *S) { }

