#include "plPXPhysical.h"
#include "plHKPhysical.h"
#include "plODEPhysical.h"

plPXPhysical::plPXPhysical() {
    // New constructor
}

plPXPhysical::plPXPhysical(const plPXPhysical& init) {
    // Copy constructor
}

plPXPhysical::~plPXPhysical() {
    // Destructor
}

IMPLEMENT_CREATABLE(plPXPhysical, kPXPhysical, plPhysical)

plHKPhysical* plPXPhysical::ConvertToHavok() const {
    return NULL;
}

plPXPhysical* plPXPhysical::ConvertToPhysX() const {
    return new plPXPhysical(*this);
}

plODEPhysical* plPXPhysical::ConvertToODE() const {
    return NULL;
}

void plPXPhysical::readData(hsStream* S, plResManager* mgr) {
    //
}

void plPXPhysical::writeData(hsStream* S, plResManager* mgr) {
    //
}
