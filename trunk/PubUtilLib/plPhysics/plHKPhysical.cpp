#include "plHKPhysical.h"
#include "plPXPhysical.h"
#include "plODEPhysical.h"

plHKPhysical::plHKPhysical() {
    // New constructor
}

plHKPhysical::plHKPhysical(const plHKPhysical& init) {
    // Copy constructor
}

plHKPhysical::~plHKPhysical() {
    // Destructor
}

IMPLEMENT_CREATABLE(plHKPhysical, kHKPhysical, plPhysical)

plHKPhysical* plHKPhysical::ConvertToHavok() const {
    return new plHKPhysical(*this);
}

plPXPhysical* plHKPhysical::ConvertToPhysX() const {
    return NULL;
}

plODEPhysical* plHKPhysical::ConvertToODE() const {
    return NULL;
}

void plHKPhysical::readData(hsStream* S, plResManager* mgr) {
    plPhysical::readData(S, mgr);

    //
}

void plHKPhysical::writeData(hsStream* S, plResManager* mgr) {
    plPhysical::writeData(S, mgr);

    //
}
