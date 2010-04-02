#ifndef _PFGUIRADIOGROUPCTRL_H
#define _PFGUIRADIOGROUPCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIRadioGroupCtrl : public pfGUIControlMod {
    CREATABLE(pfGUIRadioGroupCtrl, kGUIRadioGroupCtrl, pfGUIControlMod)

public:
    enum RadioGroupFlags { kAllowNoSelection = kDerivedFlagsStart };

protected:
    hsTArray<plKey> fControls;
    int fDefaultValue;

public:
    pfGUIRadioGroupCtrl();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getControls() const { return fControls; }
    hsTArray<plKey>& getControls() { return fControls; }
    void addControl(plKey ctrl) { fControls.append(ctrl); }
    void delControl(size_t idx) { fControls.remove(idx); }
    void clearControls() { fControls.clear(); }

    int getDefaultValue() const { return fDefaultValue; }
    void setDefaultValue(int value) { fDefaultValue = value; }
};

#endif
