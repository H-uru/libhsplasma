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

#ifndef _PFGUIBUTTONMOD_H
#define _PFGUIBUTTONMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIButtonMod : public virtual pfGUIControlMod {
    CREATABLE(pfGUIButtonMod, kGUIButtonMod, pfGUIControlMod)

public:
    enum NotifyType { kNotifyOnUp, kNotifyOnDown, kNotifyOnUpAndDown };

protected:
    hsTArray<plKey> fAnimationKeys, fMouseOverAnimKeys;
    plString fAnimName, fMouseOverAnimName;
    plKey fDraggable;
    int fNotifyType, fEoaUnknown1, fEoaUnknown2;

public:
    pfGUIButtonMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getAnimationKeys() const { return fAnimationKeys; }
    hsTArray<plKey>& getAnimationKeys() { return fAnimationKeys; }
    void addAnimationKey(plKey key) { fAnimationKeys.append(key); }
    void delAnimationKey(size_t idx) { fAnimationKeys.remove(idx); }
    void clearAnimationKeys() { fAnimationKeys.clear(); }

    const hsTArray<plKey>& getMouseOverKeys() const { return fMouseOverAnimKeys; }
    hsTArray<plKey>& getMouseOverKeys() { return fMouseOverAnimKeys; }
    void addMouseOverKey(plKey key) { fMouseOverAnimKeys.append(key); }
    void delMouseOverKey(size_t idx) { fMouseOverAnimKeys.remove(idx); }
    void clearMouseOverKeys() { fMouseOverAnimKeys.clear(); }

    const plString& getAnimationName() const { return fAnimName; }
    const plString& getMouseOverAnimName() const { return fMouseOverAnimName; }
    plKey getDraggable() const { return fDraggable; }
    int getNotifyType() const { return fNotifyType; }

    void setAnimationName(const plString& name) { fAnimName = name; }
    void setMouseOverAnimName(const plString& name) { fMouseOverAnimName = name; }
    void setDraggable(plKey draggable) { fDraggable = draggable; }
    void setNotifyType(int type) { fNotifyType = type; }
};


DllClass pfGUIMenuItem : public virtual pfGUIButtonMod {
    CREATABLE(pfGUIMenuItem, kGUIMenuItem, pfGUIButtonMod)

public:
    enum ItemFlags { kDrawSubMenuArrow = kDerivedFlagsStart, kReportHovers };

public:
    pfGUIMenuItem();
};

#endif
