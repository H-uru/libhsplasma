#ifndef _PFGUIBUTTONMOD_H
#define _PFGUIBUTTONMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIButtonMod : public pfGUIControlMod {
public:
    enum NotifyType { kNotifyOnUp, kNotifyOnDown, kNotifyOnUpAndDown };

protected:
    hsTArray<plKey> fAnimationKeys, fMouseOverAnimKeys;
    plString fAnimName, fMouseOverAnimName;
    plKey fDraggable;
    int fNotifyType, fEoaUnknown1, fEoaUnknown2;

public:
    pfGUIButtonMod();
    virtual ~pfGUIButtonMod();

    DECLARE_CREATABLE(pfGUIButtonMod)

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

    size_t getNumMouseOverKeys() const;
    plKey getMouseOverKey(size_t idx) const;
    void addMouseOverKey(plKey key);
    void delMouseOverKey(size_t idx);
    void clearMouseOverKeys();

    const plString& getAnimationName() const;
    const plString& getMouseOverAnimName() const;
    plKey getDraggable() const;
    int getNotifyType() const;

    void setAnimationName(const plString& name);
    void setMouseOverAnimName(const plString& name);
    void setDraggable(plKey draggable);
    void setNotifyType(int type);
};

DllClass pfGUIMenuItem : public pfGUIButtonMod {
public:
    enum ItemFlags { kDrawSubMenuArrow = kDerivedFlagsStart, kReportHovers };

public:
    pfGUIMenuItem();
    DECLARE_CREATABLE(pfGUIMenuItem)
};

#endif
