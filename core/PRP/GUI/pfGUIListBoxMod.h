#ifndef _PFGUILISTBOXMOD_H
#define _PFGUILISTBOXMOD_H

#include "pfGUIControlMod.h"
#include "pfGUISkin.h"

DllClass pfGUIListElement {
public:
    enum Types { kText, kPicture, kTreeRoot };

protected:
    bool fSelected;

public:
    pfGUIListElement();
    ~pfGUIListElement();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
