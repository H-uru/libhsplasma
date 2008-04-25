#ifndef _PFGUILISTBOXMOD_H
#define _PFGUILISTBOXMOD_H

#include "pfGUIControlMod.h"
#include "pfGUISkin.h"

DllClass pfGUIListElement {
public:
    enum Types { kText, kPicture, kTreeRoot };

protected:
    bool fSelected, fCollapsed;
    unsigned char fType, fIndentLevel;
    pfGUIColorScheme* fColors;
    pfGUISkin* fSkin;

public:
    pfGUIListElement();
    ~pfGUIListElement();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllClass pfGUIListBoxMod : public pfGUIControlMod {
public:
    enum ListBoxFlags {
        kSingleSelect = kDerivedFlagsStart, kDragAndDropCapable,
        kDisableSelection, kDisableKeyActions, kAllowMultipleElementsPerRow,
        kScrollLeftToRight, kAllowMousePassThrough, kGrowLeavesAndProcessOxygen,
        kHandsOffMultiSelect, kForbidNoSelection
    };

    enum ExtendedEvents {
        kScrollPosChanged, kItemAdded, kItemRemoved, kListCleared
    };

protected:
    plKey fScrollCtrl;

public:
    pfGUIListBoxMod();
    virtual ~pfGUIListBoxMod();

    DECLARE_CREATABLE(pfGUIListBoxMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
