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

void plPhysical::readData(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
}

void plPhysical::writeData(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
}

void plPhysical::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);
    prc->writeComment("Incomplete");
}
