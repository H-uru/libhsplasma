/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PFGUIPOPUPMENU_H
#define _PFGUIPOPUPMENU_H

#include "pfGUIDialogMod.h"

class PLASMA_DLL pfGUIPopUpMenu : public virtual pfGUIDialogMod {
    CREATABLE(pfGUIPopUpMenu, kGUIPopUpMenu, pfGUIDialogMod)

public:
    enum Alignment {
        kAlignUpLeft, kAlignUpRight, kAlignDownLeft, kAlignDownRight
    };

    enum MenuFlags {
        kStayOpenAfterClick = kDerivedFlagsStart, kModalOutsideMenus,
        kOpenSubMenusOnHover, kScaleWithResolution
    };

    struct PLASMA_DLL pfMenuItem {
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
