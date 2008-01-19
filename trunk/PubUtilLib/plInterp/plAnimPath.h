#ifndef _PLANIMPATH_H
#define _PLANIMPATH_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "PubUtilLib/plTransform/hsAffineParts.h"
#include "CoreLib/hsMatrix44.h"
#include "CoreLib/hsTArray.hpp"
#include "plTMController.h"

DllClass plAnimPath : public plCreatable {
public:
    struct ArcLenDeltaInfo {
        float fT, fArcLenDelta;

        ArcLenDeltaInfo();
        ArcLenDeltaInfo(float T, float arcLenDelta);
    };
    
    enum Flags {
        kNone = 0,
        kFavorFwdSearch = 0x1,
        kFavorBwdSearch = 0x2,
        kCalcPosOnly = 0x4,
        kFarthest = 0x8,
        kWrap = 0x10,
        kIncrement = 0x20
    };

protected:
    hsMatrix44 fXform;
    hsPoint3 fPos;
    hsVector3 fVel, fAccel;
    float fTime;
    unsigned int fAnimPathFlags;
    float fMinDistSq, fLength;
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    hsPoint3 fCenter;
    float fRadius;
    plCompoundController* fController;
    plTMController* fTMController;
    hsAffineParts fParts;
    float fLastTime, fLastDistSq;
    float fThisTime, fThisDistSq;
    float fNextTime, fNextDistSq;
    float fDelTime;
    hsPoint3 fPrevPos, fCurPos;
    hsTArray<ArcLenDeltaInfo> fArcLenDeltas;

public:
    plAnimPath();
    virtual ~plAnimPath();

    DECLARE_CREATABLE(plAnimPath)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
