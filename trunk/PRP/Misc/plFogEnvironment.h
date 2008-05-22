#ifndef _PLFOGENVIRONMENT_H
#define _PLFOGENVIRONMENT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Sys/hsColor.h"

DllClass plFogEnvironment : public hsKeyedObject {
public:
    enum FogType { kLinearFog, kExpFog, kExp2Fog, kNoFog };

    static const char* const FogTypeNames[];

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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
