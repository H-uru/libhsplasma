#ifndef _PLANIMTIMECONVERT_H
#define _PLANIMTIMECONVERT_H

#include "PRP/plCreatable.h"
#include "PRP/Message/plEventCallbackMsg.h"
#include "plATCEaseCurves.h"

DllClass plAnimTimeConvert : public plCreatable {
    CREATABLE(plAnimTimeConvert, kAnimTimeConvert, plCreatable)

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

protected:
    unsigned int fFlags;
    float fBegin, fEnd, fLoopBegin, fLoopEnd;
    float fSpeed, fCurrentAnimTime;
    double fLastEvalWorldTime;
    hsTArray<float> fStopPoints;
    hsTArray<plEventCallbackMsg*> fCallbackMsgs;
    plATCEaseCurve* fEaseInCurve;
    plATCEaseCurve* fEaseOutCurve;
    plATCEaseCurve* fSpeedEaseCurve;

public:
    plAnimTimeConvert();
    virtual ~plAnimTimeConvert();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getFlags() const { return fFlags; }
    float getBegin() const { return fBegin; }
    float getEnd() const { return fEnd; }
    float getLoopBegin() const { return fLoopBegin; }
    float getLoopEnd() const { return fLoopEnd; }
    float getSpeed() const { return fSpeed; }
    float getCurrentAnimTime() const { return fCurrentAnimTime; }
    double getLastEvalWorldTime() const { return fLastEvalWorldTime; }
    plATCEaseCurve* getEaseInCurve() const { return fEaseInCurve; }
    plATCEaseCurve* getEaseOutCurve() const { return fEaseOutCurve; }
    plATCEaseCurve* getSpeedEaseCurve() const { return fSpeedEaseCurve; }
    const hsTArray<float>& getStopPoints() const { return fStopPoints; }

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setRange(float begin, float end) { fBegin = begin; fEnd = end; }
    void setLoop(float begin, float end) { fLoopBegin = begin; fLoopEnd = end; }
    void setSpeed(float speed) { fSpeed = speed; }
    void setCurrentAnimTime(float time) { fCurrentAnimTime = time; }
    void setLastEvalWorldTime(double time) { fLastEvalWorldTime = time; }
    void setEaseInCurve(plATCEaseCurve* curve);
    void setEaseOutCurve(plATCEaseCurve* curve);
    void setSpeedEaseCurve(plATCEaseCurve* curve);
    void setStopPoints(const hsTArray<float>& stops) { fStopPoints = stops; }

    const hsTArray<plEventCallbackMsg*>& getCallbacks() const { return fCallbackMsgs; }
    hsTArray<plEventCallbackMsg*>& getCallbacks() { return fCallbackMsgs; }
    void addCallback(plEventCallbackMsg* callback) { fCallbackMsgs.append(callback); }
    void delCallback(size_t idx);
    void clearCallbacks();
};

#endif
