#include "plPhysical.h"
#include "plHKPhysical.h"
#include "plPXPhysical.h"
#include "plODEPhysical.h"

IMPLEMENT_CREATABLE(plPhysical, kPhysical, plSynchedObject)

void plPhysical::read(hsStream* S, plResManager* mgr) {
    readData(S, mgr);
}

void plPhysical::write(hsStream* S, plResManager* mgr) {
    plPhysical* phys = NULL;
    if (S->getVer() == pvEoa)
        phys = ConvertToODE();
    else if (S->getVer() == pvLive)
        phys = ConvertToPhysX();
    else
        phys = ConvertToHavok();

    if (phys != NULL) {
        phys->writeData(S, mgr);
        delete phys;
    }
}
