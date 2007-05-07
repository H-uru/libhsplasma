#include "plSimulationInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSimulationInterface::plSimulationInterface() {
    Physical = new plKey();
}

plSimulationInterface::~plSimulationInterface() {
    Physical->UnRef();
}

short plSimulationInterface::ClassIndex() { return kSimulationInterface; }
short plSimulationInterface::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kSimulationInterface, ver);
}

void plSimulationInterface::read(hsStream* S) {
    plObjInterface::read(S);

    Props.read(S);
    S->readInt();
    Physical = plResManager::inst->readKey(S);
    Physical->Ref();
}

void plSimulationInterface::write(hsStream* S) {
    plObjInterface::write(S);

    Props.write(S);
    S->writeInt(0);
    plResManager::inst->writeKey(S, Physical);
}

void plSimulationInterface::prcWrite(hsStream* S, pfPrcHelper* prc) {
    plObjInterface::prcWrite(S, prc);

    prc->writeSimpleTag("Properties");
    Props.prcWrite(S, prc);
    prc->closeTag();

    prc->writeSimpleTag("Physical");
    Physical->prcWrite(S, prc);
    prc->closeTag();
}
