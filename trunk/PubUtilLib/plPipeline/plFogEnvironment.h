#ifndef _PLFOGENVIRONMENT_H
#define _PLFOGENVIRONMENT_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsColor.h"

class plFogEnvironment : public hsKeyedObject {
public:
    enum FogType { kLinearFog, kExpFog, kExp2Fog, kNoFog };

protected:
    unsigned char fType;
    float fStart, fEnd, fDensity;
    hsColorRGBA fColor;

public:
    plFogEnvironment();
    virtual ~plFogEnvironment();

    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

