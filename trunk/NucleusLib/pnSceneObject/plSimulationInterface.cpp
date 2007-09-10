#include "plSimulationInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSimulationInterface::plSimulationInterface() { }
plSimulationInterface::~plSimulationInterface() { }

IMPLEMENT_CREATABLE(plSimulationInterface, kSimulationInterface, plObjInterface)

void plSimulationInterface::read(hsStream* S) {
    plObjInterface::read(S);

    Props.read(S);
    S->readInt();
    Physical = plResManager::inst->readKey(S);
}

void plSimulationInterface::write(hsStream* S) {
    plObjInterface::write(S);

    Props.write(S);
    S->writeInt(0);
    plResManager::inst->writeKey(S, Physical);
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
