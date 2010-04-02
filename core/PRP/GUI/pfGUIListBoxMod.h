#ifndef _PFGUILISTBOXMOD_H
#define _PFGUILISTBOXMOD_H

#include "pfGUIControlMod.h"
#include "pfGUISkin.h"

DllClass pfGUIListElement {
public:
    enum Types { kText, kPicture, kTreeRoot };

private:
    bool fSelected;

public:
    pfGUIListElement();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    bool isSelected() const { return fSelected; }
    void setSelected(bool sel) { fSelected = sel; }
};


DllClass pfGUIListBoxMod : public pfGUIControlMod {
    CREATABLE(pfGUIListBoxMod, kGUIListBoxMod, pfGUIControlMod)

public:
    enum ListBoxFlags {
        kSingleSelect = kDerivedFlagsStart, kDragAndDropCapable,
        kDisableSelection, kDisableKeyActions, kAllowMultipleElementsPerRow,
        kScrollLeftToRight, kAllowMousePassThrough, kGrowLeavesAndProcessOxygen,
        kHandsOffMultiSelect, kForbidNoSelection
    };

protected:
    plKey fScrollCtrl;

public:
    pfGUIListBoxMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getScrollCtrl() const { return fScrollCtrl; }
    void setScrollCtrl(plKey ctrl) { fScrollCtrl = ctrl; }
};

#endif
