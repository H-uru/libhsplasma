#ifndef _PFGUILISTBOXMOD_H
#define _PFGUILISTBOXMOD_H

#include "pfGUIControlMod.h"
#include "pfGUISkin.h"

DllClass pfScrollProc : public pfGUICtrlProcObject {
protected:
    class pfGUIListBoxMod* fParent;

public:
    pfScrollProc(class pfGUIListBoxMod* parent);
    virtual void DoSomething(pfGUIControlMod* ctrl);
};

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
    DllStruct SmallRect {
        short fLeft, fTop, fRight,fBottom;
    };

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
    pfScrollProc* fScrollProc;
    hsTArray<pfGUIListElement*> fElements;
    int fCurrClick, fScrollPos, fCurrHover;
    unsigned char fModsAtDragTime;
    int fMinSel, fMaxSel;
    bool fCheckSel, fClicking;
    int fSingleSelElement;
    bool fScrollRangeUpdateDeferred, fLocked, fReadyToRoll;
    hsTArray<SmallRect> fElementBounds;
    hsTArray<short> fWrapStartIdxs;

public:
    pfGUIListBoxMod();
    virtual ~pfGUIListBoxMod();

    DECLARE_CREATABLE(pfGUIListBoxMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
