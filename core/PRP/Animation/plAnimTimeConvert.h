#ifndef _PLANIMTIMECONVERT_H
#define _PLANIMTIMECONVERT_H

#include "PRP/plCreatable.h"
#include "PRP/Message/plEventCallbackMsg.h"
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

    //enum plEaseCurveType { kEaseNone, kEaseIn, kEaseOut, kEaseSpeed };

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

    DECLARE_CREATABLE(plAnimTimeConvert)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getFlags() const;
    float getBegin() const;
    float getEnd() const;
    float getLoopBegin() const;
    float getLoopEnd() const;
    float getSpeed() const;
    float getCurrentAnimTime() const;
    double getLastEvalWorldTime() const;
    plATCEaseCurve* getEaseInCurve() const;
    plATCEaseCurve* getEaseOutCurve() const;
    plATCEaseCurve* getSpeedEaseCurve() const;
    const hsTArray<float>& getStopPoints() const;

    void setFlags(unsigned int flags);
    void setRange(float begin, float end);
    void setLoop(float begin, float end);
    void setSpeed(float speed);
    void setCurrentAnimTime(float time);
    void setLastEvalWorldTime(double time);
    void setEaseInCurve(plATCEaseCurve* curve);
    void setEaseOutCurve(plATCEaseCurve* curve);
    void setSpeedEaseCurve(plATCEaseCurve* curve);
    void setStopPoints(const hsTArray<float>& stops);

    size_t getNumCallbacks() const;
    plEventCallbackMsg* getCallback(size_t idx) const;
    void addCallback(plEventCallbackMsg* callback);
    void delCallback(size_t idx);
    void clearCallbacks();
};

#endif
