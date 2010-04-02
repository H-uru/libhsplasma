#ifndef _PLOMNILIGHTINFO_H
#define _PLOMNILIGHTINFO_H

#include "plLightInfo.h"

DllClass plOmniLightInfo : public plLightInfo {
    CREATABLE(plOmniLightInfo, kOmniLightInfo, plLightInfo)

protected:
    float fAttenConst, fAttenLinear, fAttenQuadratic, fAttenCutoff;

public:
    plOmniLightInfo();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAttenConst() const { return fAttenConst; }
    float getAttenLinear() const { return fAttenLinear; }
    float getAttenQuadratic() const { return fAttenQuadratic; }
    float getAttenCutoff() const { return fAttenCutoff; }

    void setAttenConst(float atten) { fAttenConst = atten; }
    void setAttenLinear(float atten) { fAttenLinear = atten; }
    void setAttenQuadratic(float atten) { fAttenQuadratic = atten; }
    void setAttenCutoff(float cutoff) { fAttenCutoff = cutoff; }
};


DllClass plSpotLightInfo : public plOmniLightInfo {
    CREATABLE(plSpotLightInfo, kSpotLightInfo, plOmniLightInfo)

protected:
    float fFalloff, fSpotInner, fSpotOuter;

public:
    plSpotLightInfo();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getFalloff() const { return fFalloff; }
    float getSpotInner() const { return fSpotInner; }
    float getSpotOuter() const { return fSpotOuter; }

    void setFalloff(float falloff) { fFalloff = falloff; }
    void setSpotInner(float spot) { fSpotInner = spot; }
    void setSpotOuter(float spot) { fSpotOuter = spot; }
};

#endif
