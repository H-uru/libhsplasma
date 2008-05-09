#ifndef _PLANIMTIMECONVERT_H
#define _PLANIMTIMECONVERT_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "NucleusLib/pnMessage/plEventCallbackMsg.h"
#include "plATCEaseCurves.h"

DllClass plAnimTimeConvert : public plCreatable {
public:
    enum plAnimTimeFlags {
        kNone = 0,
        kStopped = 0x1,
        kLoop = 0x2,
        kBackwards = 0x4,
        kWrap = 0x8,
        kNeedsReset = 0x10,
        kEasingIn = 0x20,
        kForcedMove = 0x40,
        kNoCallbacks = 0x80,
        kFlagsMask = 0xFF
    };

    enum plEaseCurveType { kEaseNone, kEaseIn, kEaseOut, kEaseSpeed };

protected:
    unsigned int fFlags;
    float fBegin, fEnd, fLoopBegin, fLoopEnd;
    float fSpeed, fCurrentAnimTime, fWrapTime;
    double fLastEvalWorldTime, fLastStateChange;
    hsTArray<float> fStopPoints;
    hsTArray<plEventCallbackMsg*> fCallbackMsgs;
    plATCEaseCurve* fEaseInCurve;
    plATCEaseCurve* fEaseOutCurve;
    plATCEaseCurve* fSpeedEaseCurve;
    plATCEaseCurve* fCurrentEaseCurve;
    float fInitialBegin, fInitialEnd;

public:
    plAnimTimeConvert();
    virtual ~plAnimTimeConvert();

    DECLARE_CREATABLE(plAnimTimeConvert)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
