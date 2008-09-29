#ifndef _PLDYNADECALMGR_H
#define _PLDYNADECALMGR_H

#include "PRP/Object/plSynchedObject.h"
#include "Math/hsGeometry3.h"

DllClass plDynaDecalMgr : public plSynchedObject {
protected:
    plKey fMatPreShade, fMatRTShade;
    hsTArray<plKey> fTargets, fPartyObjects;
    float fPartyTime;
    unsigned short fMaxNumVerts, fMaxNumIdx;
    unsigned int fWaitOnEnable;
    float fWetLength, fRampEnd, fDecayStart, fLifeSpan, fIntensity;
    float fGridSizeU, fGridSizeV;
    hsVector3 fScale;
    float fInitAtten;
    float fMinDepth, fMaxDepth, fMinDepthRange, fMaxDepthRange;
    hsTArray<unsigned int> fPartIDs;
    hsTArray<plKey> fNotifies;

public:
    plDynaDecalMgr();
    virtual ~plDynaDecalMgr();

    DECLARE_CREATABLE(plDynaDecalMgr)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plDynaBulletMgr : public plDynaDecalMgr {
public:
    plDynaBulletMgr();
    virtual ~plDynaBulletMgr();

    DECLARE_CREATABLE(plDynaBulletMgr)
};

DllClass plDynaFootMgr : public plDynaDecalMgr {
public:
    plDynaFootMgr();
    virtual ~plDynaFootMgr();

    DECLARE_CREATABLE(plDynaFootMgr)
};

#endif
