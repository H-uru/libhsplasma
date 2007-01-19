#ifndef _PLFOGENVIRONMENT_H
#define _PLFOGENVIRONMENT_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"

class plFogEnvironment : public hsKeyedObject {
protected:
    char c10;
    float f14, f18, f1C, f20, f24, f28, f2C;

public:
    plFogEnvironment(PlasmaVer pv = pvUnknown);
    virtual ~plFogEnvironment();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

