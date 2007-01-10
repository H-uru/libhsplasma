#ifndef _PLSIMULATIONINTERFACE_H
#define _PLSIMULATIONINTERFACE_H

#include "plObjInterface.h"

class plSimulationInterface : public plObjInterface {
protected:
    hsBitVector SimFlags;
    int Unknown;
    plKey * Physical;

public:
    plSimulationInterface(PlasmaVer pv = pvUnknown);
    ~plSimulationInterface();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

