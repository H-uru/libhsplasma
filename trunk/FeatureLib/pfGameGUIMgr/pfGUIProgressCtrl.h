#ifndef _PFGUIPROGRESSCTRL_H
#define _PFGUIPROGRESSCTRL_H

#include "pfGUIValueCtrl.h"

DllClass pfGUIProgressCtrl : public pfGUIValueCtrl {
public:
    enum ProgressFlags {
        kReverseValues = kDerivedFlagsStart, kLeftRightOrientation,
        kMapToScreenRange, kTriggerOnlyOnMouseUp, kMapToAnimationRange
    };

protected:
    hsTArray<plKey> fAnimationKeys;
    plString fAnimName;
    float fAnimBegin, fAnimEnd;
    bool fAnimTimesCalced, fPlaySound;
    unsigned int fStopSoundTimer;

public:
    pfGUIProgressCtrl();
    virtual ~pfGUIProgressCtrl();

    DECLARE_CREATABLE(pfGUIProgressCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
