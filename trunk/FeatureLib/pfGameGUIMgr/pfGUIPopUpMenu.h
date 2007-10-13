#ifndef _PFGUIPOPUPMENU_H
#define _PFGUIPOPUPMENU_H

#include "pfGUIDialogMod.h"

DllClass pfGUIPopUpMenu : public pfGUIDialogMod {
public:
    enum Alignment {
        kAlignUpLeft, kAlignUpRight, kAlignDownLoeft, kAlignDownRight
    };

    enum MenuFlags {
        kStayOpenAfterClick = kDerivedFlagsStart, kModalOutsideMenus,
        kOpenSubMenusOnHover, kScaleWithResolution
    };

    struct pfMenuItem {
        plString fName;
        pfGUICtrlProcWriteableObject* fHandler;
        plKey fSubMenu;
        float fYOffsetToNext;
    };

protected:
    pfGUIDialogMod* fParent;
    //pfPopUpKeyGenerator* fKeyGen;
    bool fNeedsRebuilding, fWaitingForSkin;
    float fOriginX, fOriginY;
    unsigned short fMargin;
    hsTArray<pfMenuItem> fMenuItems;
    int fSubMenuOpen;
    plKey fSkin, fOriginAnchor, fOriginContext;
    Alignment fAlignment;

public:
    pfGUIPopUpMenu();
    virtual ~pfGUIPopUpMenu();

    DECLARE_CREATABLE(pfGUIPopUpMenu)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
