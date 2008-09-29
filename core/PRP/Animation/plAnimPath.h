#ifndef _PLANIMPATH_H
#define _PLANIMPATH_H

#include "PRP/plCreatable.h"
#include "Math/hsAffineParts.h"
#include "Math/hsMatrix44.h"
#include "Util/hsTArray.hpp"
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
   unsigned int fAnimPathFlags;
   float fMinDistSq, fLength;
   hsMatrix44 fLocalToWorld, fWorldToLocal;
   plCompoundController* fController;
   plTMController* fTMController;
   hsAffineParts fParts;

public:
    plAnimPath();
    virtual ~plAnimPath();

    DECLARE_CREATABLE(plAnimPath)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
