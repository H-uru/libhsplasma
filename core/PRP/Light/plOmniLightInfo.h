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

    float getAttenConst() const;
    float getAttenLinear() const;
    float getAttenQuadratic() const;
    float getAttenCutoff() const;

    void setAttenConst(float atten);
    void setAttenLinear(float atten);
    void setAttenQuadratic(float atten);
    void setAttenCutoff(float cutoff);
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

    float getFalloff() const;
    float getSpotInner() const;
    float getSpotOuter() const;
    float getEffectiveFOV() const;

    void setFalloff(float falloff);
    void setSpotInner(float spot);
    void setSpotOuter(float spot);
    void setEffectiveFOV(float fov);
};

#endif
