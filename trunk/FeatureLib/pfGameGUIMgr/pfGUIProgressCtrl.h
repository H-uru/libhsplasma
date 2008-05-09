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

public:
    pfGUIProgressCtrl();
    virtual ~pfGUIProgressCtrl();

    DECLARE_CREATABLE(pfGUIProgressCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
