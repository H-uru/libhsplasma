#ifndef _PFGUIPROGRESSCTRL_H
#define _PFGUIPROGRESSCTRL_H

#include "pfGUIValueCtrl.h"

DllClass pfGUIProgressCtrl : public pfGUIValueCtrl {
    CREATABLE(pfGUIProgressCtrl, kGUIProgressCtrl, pfGUIValueCtrl)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getAnimKeys() const { return fAnimationKeys; }
    hsTArray<plKey>& getAnimKeys() { return fAnimationKeys; }
    void addAnimKey(plKey key) { fAnimationKeys.append(key); }
    void delAnimKey(size_t idx) { fAnimationKeys.remove(idx); }
    void clearAnimKeys() { fAnimationKeys.clear(); }

    const plString& getAnimName() const { return fAnimName; }
    void setAnimName(const plString& name) { fAnimName = name; }
};

#endif
