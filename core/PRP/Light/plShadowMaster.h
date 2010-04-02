#ifndef _PLSHADOWMASTER_H
#define _PLSHADOWMASTER_H

#include "PRP/Object/plObjInterface.h"
#include "plLightInfo.h"

DllClass plShadowMaster : public plObjInterface {
    CREATABLE(plShadowMaster, kShadowMaster, plObjInterface)

public:
    enum DrawProperties {
        kDisable, kSelfShadow, kNumProps
    };

protected:
    float fAttenDist, fMaxDist, fMinDist, fPower;
    unsigned int fMaxSize, fMinSize;

public:
    plShadowMaster();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAttenDist() const { return fAttenDist; }
    float getMaxDist() const { return fMaxDist; }
    float getMinDist() const { return fMinDist; }
    float getPower() const { return fPower; }
    unsigned int getMaxSize() const { return fMaxSize; }
    unsigned int getMinSize() const { return fMinSize; }

    void setAttenDist(float dist) { fAttenDist = dist; }
    void setDist(float min, float max) { fMinDist = min; fMaxDist = max; }
    void setPower(float power) { fPower = power; }
    void setSize(unsigned int min, unsigned int max) { fMinSize = min; fMaxSize = max; }
};


DllClass plPointShadowMaster : public plShadowMaster {
    CREATABLE(plPointShadowMaster, kPointShadowMaster, plShadowMaster)
};


DllClass plDirectShadowMaster : public plShadowMaster {
    CREATABLE(plDirectShadowMaster, kDirectShadowMaster, plShadowMaster)
};

#endif
