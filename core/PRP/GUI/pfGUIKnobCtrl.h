#ifndef _PFGUIKNOBCTRL_H
#define _PFGUIKNOBCTRL_H

#include "pfGUIValueCtrl.h"
#include "Math/hsGeometry3.h"

DllClass pfGUIKnobCtrl : public pfGUIValueCtrl {
    CREATABLE(pfGUIKnobCtrl, kGUIKnobCtrl, pfGUIValueCtrl)

public:
    enum KnobFlags {
        kReverseValues = kDerivedFlagsStart, kLeftRightOrientation,
        kMapToScreenRange, kTriggerOnlyOnMouseUp, kMapToAnimationRange
    };

protected:
    hsTArray<plKey> fAnimationKeys;
    plString fAnimName;
    hsVector3 fAnimStartPos, fAnimEndPos;

public:
    pfGUIKnobCtrl();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getAnimationKeys() const { return fAnimationKeys; }
    hsTArray<plKey>& getAnimationKeys() { return fAnimationKeys; }
    void addAnimationKey(plKey key) { fAnimationKeys.append(key); }
    void delAnimationKey(size_t idx) { fAnimationKeys.remove(idx); }
    void clearAnimationKeys() { fAnimationKeys.clear(); }

    plString getAnimName() const { return fAnimName; }
    hsVector3 getAnimStartPos() const { return fAnimStartPos; }
    hsVector3 getAnimEndPos() const { return fAnimEndPos; }

    void setAnimName(const plString& name) { fAnimName = name; }
    void setAnimStartPos(const hsVector3& pos) { fAnimStartPos = pos; }
    void setAnimEndPos(const hsVector3& pos) { fAnimEndPos = pos; }
};

#endif
