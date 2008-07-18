#ifndef _PLOMNILIGHTINFO_H
#define _PLOMNILIGHTINFO_H

#include "plLightInfo.h"

DllClass plOmniLightInfo : public plLightInfo {
protected:
    float fAttenConst, fAttenLinear, fAttenQuadratic, fAttenCutoff;

public:
    plOmniLightInfo();
    virtual ~plOmniLightInfo();

    DECLARE_CREATABLE(plOmniLightInfo)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSpotLightInfo : public plOmniLightInfo {
protected:
    float fFalloff, fSpotInner, fSpotOuter, fEffectiveFOV;

public:
    plSpotLightInfo();
    virtual ~plSpotLightInfo();

    DECLARE_CREATABLE(plSpotLightInfo)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
