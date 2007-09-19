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

    DECLARE_CREATABLE(plFogEnvironment)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};

#endif

