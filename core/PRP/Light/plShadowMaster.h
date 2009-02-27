#ifndef _PLSHADOWMASTER_H
#define _PLSHADOWMASTER_H

#include "PRP/Object/plObjInterface.h"
#include "plLightInfo.h"

DllClass plShadowMaster : public plObjInterface {
public:
    enum DrawProperties {
        kDisable, kSelfShadow, kNumProps
    };

protected:
    float fAttenDist, fMaxDist, fMinDist, fPower;
    unsigned int fMaxSize, fMinSize;

public:
    plShadowMaster();
    virtual ~plShadowMaster();

    DECLARE_CREATABLE(plShadowMaster)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAttenDist() const;
    float getMaxDist() const;
    float getMinDist() const;
    float getPower() const;
    unsigned int getMaxSize() const;
    unsigned int getMinSize() const;

    void setAttenDist(float dist);
    void setDist(float min, float max);
    void setPower(float power);
    void setSize(unsigned int min, unsigned int max);
};

DllClass plPointShadowMaster : public plShadowMaster {
public:
    plPointShadowMaster();
    virtual ~plPointShadowMaster();

    DECLARE_CREATABLE(plPointShadowMaster)
};

DllClass plDirectShadowMaster : public plShadowMaster {
public:
    plDirectShadowMaster();
    virtual ~plDirectShadowMaster();

    DECLARE_CREATABLE(plDirectShadowMaster)
};

#endif
