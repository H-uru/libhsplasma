#ifndef _PFGUIKNOBCTRL_H
#define _PFGUIKNOBCTRL_H

#include "pfGUIValueCtrl.h"
#include "Math/hsGeometry3.h"

DllClass pfGUIKnobCtrl : public pfGUIValueCtrl {
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
    virtual ~pfGUIKnobCtrl();

    DECLARE_CREATABLE(pfGUIKnobCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumAnimationKeys() const;
    plKey getAnimationKey(size_t idx) const;
    void addAnimationKey(plKey key);
    void delAnimationKey(size_t idx);
    void clearAnimationKeys();

    const plString& getAnimName() const;
    const hsVector3& getAnimStartPos() const;
    const hsVector3& getAnimEndPos() const;

    void setAnimName(const plString& name);
    void setAnimStartPos(const hsVector3& pos);
    void setAnimEndPos(const hsVector3& pos);
};

#endif
