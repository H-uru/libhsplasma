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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumAnimKeys() const;
    plKey getAnimKey(size_t idx) const;
    void addAnimKey(plKey key);
    void delAnimKey(size_t idx);
    void clearAnimKeys();

    const plString& getAnimName() const;
    void setAnimName(const plString& name);
};

#endif
