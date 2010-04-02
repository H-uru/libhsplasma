#ifndef _PLDYNADECALMGR_H
#define _PLDYNADECALMGR_H

#include "PRP/Object/plSynchedObject.h"
#include "Math/hsGeometry3.h"

DllClass plDynaDecalMgr : public plSynchedObject {
    CREATABLE(plDynaDecalMgr, kDynaDecalMgr, plSynchedObject)

protected:
    plKey fMatPreShade, fMatRTShade;
    hsTArray<plKey> fTargets, fPartyObjects;
    float fPartyTime;
    unsigned short fMaxNumVerts, fMaxNumIdx;
    unsigned int fWaitOnEnable;
    float fWetLength, fRampEnd, fDecayStart, fLifeSpan, fIntensity;
    float fGridSizeU, fGridSizeV;
    hsVector3 fScale;
    hsTArray<plKey> fNotifies;

public:
    plDynaDecalMgr();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plDynaBulletMgr : public plDynaDecalMgr {
    CREATABLE(plDynaBulletMgr, kDynaBulletMgr, plDynaDecalMgr)
};


DllClass plDynaFootMgr : public plDynaDecalMgr {
    CREATABLE(plDynaFootMgr, kDynaFootMgr, plDynaDecalMgr)
};

#endif
