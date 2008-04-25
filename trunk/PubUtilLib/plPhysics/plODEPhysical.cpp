#include "plODEPhysical.h"
#include "plPXPhysical.h"
#include "plHKPhysical.h"

plODEPhysical::plODEPhysical() {
    // New constructor
}

plODEPhysical::plODEPhysical(const plODEPhysical& init) {
    // Copy constructor
}

plODEPhysical::~plODEPhysical() {
    // Destructor
}

IMPLEMENT_CREATABLE(plODEPhysical, kODEPhysical, plPhysical)

plHKPhysical* plODEPhysical::ConvertToHavok() const {
    return NULL;
}

plPXPhysical* plODEPhysical::ConvertToPhysX() const {
    return NULL;
}

plODEPhysical* plODEPhysical::ConvertToODE() const {
    return new plODEPhysical(*this);
}

void plODEPhysical::readData(hsStream* S, plResManager* mgr) {
    //
}

void plODEPhysical::writeData(hsStream* S, plResManager* mgr) {
    //
}
