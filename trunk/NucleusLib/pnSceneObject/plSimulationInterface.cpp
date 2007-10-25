#include "plSimulationInterface.h"

plSimulationInterface::plSimulationInterface() { }
plSimulationInterface::~plSimulationInterface() { }

IMPLEMENT_CREATABLE(plSimulationInterface, kSimulationInterface, plObjInterface)

void plSimulationInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    Props.read(S);
    S->readInt();
    Physical = mgr->readKey(S);
}

void plSimulationInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    Props.write(S);
    S->writeInt(0);
    mgr->writeKey(S, Physical);
}

void plSimulationInterface::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->writeSimpleTag("Properties");
    Props.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Physical");
    Physical->prcWrite(prc);
    prc->closeTag();
}
