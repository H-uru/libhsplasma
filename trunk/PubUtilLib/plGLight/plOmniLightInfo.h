#ifndef _PLOMNILIGHTINFO_H
#define _PLOMNILIGHTINFO_H

#include "plLightInfo.h"

class plOmniLightInfo : public plLightInfo {
protected:
    float fAttenConst, fAttenLinear, fAttenQuadratic, fAttenCutoff;
    //plSphereIsect* fSphere;

public:
    plOmniLightInfo();
    virtual ~plOmniLightInfo();

    DECLARE_CREATABLE(plOmniLightInfo)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

class plSpotLightInfo : public plOmniLightInfo {
protected:
    float fFalloff, fSpotInner, fSpotOuter, fEffectiveFOV;
    //plConeIsect* fCone;

public:
    plSpotLightInfo();
    virtual ~plSpotLightInfo();

    DECLARE_CREATABLE(plSpotLightInfo)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

