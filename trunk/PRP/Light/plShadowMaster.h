#ifndef _PLSHADOWMASTER_H
#define _PLSHADOWMASTER_H

#include "PRP/Object/plObjInterface.h"
#include "plLightInfo.h"
#include "plShadowSlave.h"

DllClass plShadowMaster : public plObjInterface {
public:
    enum DrawProperties {
        kDisable, kSelfShadow, kNumProps
    };

protected:
    float fAttenDist, fMaxDist, fMinDist, fPower;
    unsigned int fMaxSize, fMinSize;
    hsTArray<plShadowSlave*> fSlavePool;
    plLightInfo* fLightInfo;

public:
    plShadowMaster();
    virtual ~plShadowMaster();

    DECLARE_CREATABLE(plShadowMaster)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plPointShadowMaster : public plShadowMaster {
protected:
    hsVector3 fLastUp;

public:
    plPointShadowMaster();
    virtual ~plPointShadowMaster();

    DECLARE_CREATABLE(plPointShadowMaster)
};

DllClass plDirectShadowMaster : public plShadowMaster {
protected:
    hsTArray<plShadowSlave*> fPerspSlavePool;

public:
    plDirectShadowMaster();
    virtual ~plDirectShadowMaster();

    DECLARE_CREATABLE(plDirectShadowMaster)
};

#endif
