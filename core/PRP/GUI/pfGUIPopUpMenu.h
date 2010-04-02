#ifndef _PFGUIPOPUPMENU_H
#define _PFGUIPOPUPMENU_H

#include "pfGUIDialogMod.h"

DllClass pfGUIPopUpMenu : public pfGUIDialogMod {
    CREATABLE(pfGUIPopUpMenu, kGUIPopUpMenu, pfGUIDialogMod)

public:
    enum Alignment {
        kAlignUpLeft, kAlignUpRight, kAlignDownLeft, kAlignDownRight
    };

    enum MenuFlags {
        kStayOpenAfterClick = kDerivedFlagsStart, kModalOutsideMenus,
        kOpenSubMenusOnHover, kScaleWithResolution
    };

    DllStruct pfMenuItem {
        plString fName;
        pfGUICtrlProcWriteableObject* fHandler;
        plKey fSubMenu;
        float fYOffsetToNext;
    };

protected:
    unsigned short fMargin;
    hsTArray<pfMenuItem> fMenuItems;
    plKey fSkin;
    plKey fOriginContext, fOriginAnchor;
    Alignment fAlignment;

public:
    pfGUIPopUpMenu();
    virtual ~pfGUIPopUpMenu();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumItems() const { return fMenuItems.getSize(); }
    pfMenuItem& getItem(size_t idx) { return fMenuItems[idx]; }
    void addItem(const plString& name, pfGUICtrlProcWriteableObject* handler,
                 plKey subMenu = plKey(), float yoffs = 0.0f);
    void delItem(size_t idx);
    void moveItem(size_t from, size_t to);
    void clearItems();

    unsigned short getMargin() const { return fMargin; }
    plKey getSkin() const { return fSkin; }
    plKey getOriginContext() const { return fOriginContext; }
    plKey getOriginAnchor() const { return fOriginAnchor; }
    Alignment getAlignment() const { return fAlignment; }

    void setMargin(unsigned short margin) { fMargin = margin; }
    void setSkin(plKey skin) { fSkin = skin; }
    void setOriginContext(plKey context) { fOriginContext = context; }
    void setOriginAnchor(plKey anchor) { fOriginAnchor = anchor; }
    void setAlignment(Alignment align) { fAlignment = align; }
};

#endif
