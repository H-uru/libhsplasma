#include "plSimulationInterface.h"

plSimulationInterface::plSimulationInterface() : Unknown(0) {
    Physical = new plKey();
}

plSimulationInterface::~plSimulationInterface() {
    delete Physical;
}

void plSimulationInterface::read(hsStream *S) {
    plObjInterface::read(S);

    SimFlags.read(S);
    Unknown = S->readInt();
    Physical->readRef(S);
}

void plSimulationInterface::write(hsStream *S) {
    plObjInterface::write(S);

    SimFlags.write(S);
    S->writeInt(Unknown);
    Physical->writeRef(S);
}

