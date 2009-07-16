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
    ~pfGUIListElement();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    bool getSelected() const;
    void setSelected(bool sel);
};

DllClass pfGUIListBoxMod : public pfGUIControlMod {
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
    virtual ~pfGUIListBoxMod();

    DECLARE_CREATABLE(pfGUIListBoxMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getScrollCtrl() const;
    void setScrollCtrl(plKey ctrl);
};

#endif
