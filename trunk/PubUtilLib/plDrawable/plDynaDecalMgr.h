#ifndef _PLDYNADECALMGR_H
#define _PLDYNADECALMGR_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "CoreLib/hsGeometry3.h"

DllClass plDynaDecalMgr : public plSynchedObject {
protected:
    //std::map<unsigned int, plDynaDecalInfo> fDecalMap;
    //hsTArray<plDynaDecal*> fDecals;
    //hsTArray<plGBufferGroup*> fGroups;
    //plCutter* fCutter;
    //hsTArray<plAuxSpan*> fAuxSpans;
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
    virtual void prcWrite(pfPrcHelper* prc);
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
