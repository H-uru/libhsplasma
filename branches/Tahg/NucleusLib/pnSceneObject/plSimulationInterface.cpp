#include "plSimulationInterface.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plSimulationInterface::plSimulationInterface(PlasmaVer pv) : Unknown(0) {
    Physical = new plKey();
}

plSimulationInterface::~plSimulationInterface() {
    Physical->UnRef();
}

unsigned short plSimulationInterface::ClassIndex() { return 0x001C; }

void plSimulationInterface::read(hsStream *S) {
    plObjInterface::read(S);

    SimFlags.read(S);
    Unknown = S->readInt();
    Physical = plResManager::inst->readKey(S);
    Physical->Ref();
}

void plSimulationInterface::write(hsStream *S) {
    plObjInterface::write(S);

    SimFlags.write(S);
    S->writeInt(Unknown);
    plResManager::inst->writeKey(S, Physical);
}

