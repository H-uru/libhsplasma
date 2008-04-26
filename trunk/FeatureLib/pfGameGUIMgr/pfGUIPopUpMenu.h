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
    unsigned short fMargin;
    hsTArray<pfMenuItem> fMenuItems;
    plKey fSkin, fOriginContext;
    plWeakKey fOriginAnchor;
    Alignment fAlignment;

public:
    pfGUIPopUpMenu();
    virtual ~pfGUIPopUpMenu();

    DECLARE_CREATABLE(pfGUIPopUpMenu)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
