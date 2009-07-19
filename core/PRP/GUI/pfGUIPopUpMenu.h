#ifndef _PFGUIPOPUPMENU_H
#define _PFGUIPOPUPMENU_H

#include "pfGUIDialogMod.h"

DllClass pfGUIPopUpMenu : public pfGUIDialogMod {
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

    DECLARE_CREATABLE(pfGUIPopUpMenu)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumItems() const;
    pfMenuItem& getItem(size_t idx);
    void addItem(const plString& name, pfGUICtrlProcWriteableObject* handler,
                 plKey subMenu = plKey(), float yoffs = 0.0f);
    void delItem(size_t idx);
    void moveItem(size_t from, size_t to);
    void clearItems();

    unsigned short getMargin() const;
    plKey getSkin() const;
    plKey getOriginContext() const;
    plKey getOriginAnchor() const;
    Alignment getAlignment() const;

    void setMargin(unsigned short margin);
    void setSkin(plKey skin);
    void setOriginContext(plKey context);
    void setOriginAnchor(plKey anchor);
    void setAlignment(Alignment align);
};

#endif
