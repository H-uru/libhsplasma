#ifndef _PLANIMSTAGE_H
#define _PLANIMSTAGE_H

#include "PRP/plCreatable.h"

DllClass plAnimStage : public plCreatable {
public:
    enum NotifyType {
        kNotifyEnter = 0x1,
        kNotifyLoop = 0x2,
        kNotifyAdvance = 0x4,
        kNotifyRegress = 0x8
    };

    enum PlayType { kPlayNone, kPlayKey, kPlayAuto, kPlayMax };
    
    enum AdvanceType {
        kAdvanceNone, kAdvanceOnMove, kAdvanceAuto, kAdvanceOnAnyKey,
        kAdvanceMax
    };

protected:
    PlayType fForwardType, fBackType;
    AdvanceType fAdvanceType, fRegressType;
    plString fAnimName;
    unsigned char fNotify;
    int fLoops, fCurLoop;
    bool fDoAdvanceTo, fDoRegressTo;
    unsigned int fAdvanceTo, fRegressTo;
    float fLocalTime, fLength;
    bool fAttached, fAnimatedHandle;
    unsigned char fSentNotifiers;
    bool fReverseOnIdle, fDone;

public:
    plAnimStage();
    virtual ~plAnimStage();

    DECLARE_CREATABLE(plAnimStage)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
