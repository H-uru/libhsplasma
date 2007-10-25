#ifndef _PFGUIRADIOGROUPCTRL_H
#define _PFGUIRADIOGROUPCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGroupProc : public pfGUICtrlProcObject {
protected:
    class pfGUIRadioGroupCtrl* fParent;

public:
    pfGroupProc(class pfGUIRadioGroupCtrl* parent);
    virtual void DoSomething(pfGUIControlMod* ctrl);
};

DllClass pfGUIRadioGroupCtrl : public pfGUIControlMod {
public:
    enum RadioGroupFlags { kAllowNoSelection = kDerivedFlagsStart };

protected:
    hsTArray<plKey> fControls;
    pfGroupProc* fButtonProc;
    int fValue, fDefaultValue;

public:
    pfGUIRadioGroupCtrl();
    virtual ~pfGUIRadioGroupCtrl();

    DECLARE_CREATABLE(pfGUIRadioGroupCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
