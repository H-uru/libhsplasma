#include "plCreatable.h"

plCreatable::plCreatable(PlasmaVer pv) {
    setVer(pv);
}

plCreatable::~plCreatable() { }

PlasmaVer plCreatable::getVer() { return ver; }
void plCreatable::setVer(PlasmaVer pv, bool mutate) { ver = pv; }

void plCreatable::read(hsStream* S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer());
}

void plCreatable::write(hsStream* S) {
    if (S->getVer() != pvUnknown)
        setVer(S->getVer(), true);
}
