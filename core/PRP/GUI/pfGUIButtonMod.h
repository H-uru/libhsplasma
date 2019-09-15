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

class PLASMA_DLL pfGUIButtonMod : public pfGUIControlMod
{
    CREATABLE(pfGUIButtonMod, kGUIButtonMod, pfGUIControlMod)

public:
    enum NotifyType { kNotifyOnUp, kNotifyOnDown, kNotifyOnUpAndDown };

protected:
    std::vector<plKey> fAnimationKeys, fMouseOverAnimKeys;
    ST::string fAnimName, fMouseOverAnimName;
    plKey fDraggable;
    int fNotifyType, fEoaUnknown1, fEoaUnknown2;

public:
    pfGUIButtonMod() : fNotifyType(), fEoaUnknown1(), fEoaUnknown2() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getAnimationKeys() const { return fAnimationKeys; }
    std::vector<plKey>& getAnimationKeys() { return fAnimationKeys; }
    void addAnimationKey(plKey key) { fAnimationKeys.emplace_back(std::move(key)); }
    void delAnimationKey(size_t idx) { fAnimationKeys.erase(fAnimationKeys.begin() + idx); }
    void clearAnimationKeys() { fAnimationKeys.clear(); }

    const std::vector<plKey>& getMouseOverKeys() const { return fMouseOverAnimKeys; }
    std::vector<plKey>& getMouseOverKeys() { return fMouseOverAnimKeys; }
    void addMouseOverKey(plKey key) { fMouseOverAnimKeys.emplace_back(std::move(key)); }
    void delMouseOverKey(size_t idx) { fMouseOverAnimKeys.erase(fMouseOverAnimKeys.begin() + idx); }
    void clearMouseOverKeys() { fMouseOverAnimKeys.clear(); }

    const ST::string& getAnimationName() const { return fAnimName; }
    const ST::string& getMouseOverAnimName() const { return fMouseOverAnimName; }
    plKey getDraggable() const { return fDraggable; }
    int getNotifyType() const { return fNotifyType; }

    void setAnimationName(const ST::string& name) { fAnimName = name; }
    void setMouseOverAnimName(const ST::string& name) { fMouseOverAnimName = name; }
    void setDraggable(plKey draggable) { fDraggable = std::move(draggable); }
    void setNotifyType(int type) { fNotifyType = type; }
};


class PLASMA_DLL pfGUIMenuItem : public pfGUIButtonMod
{
    CREATABLE(pfGUIMenuItem, kGUIMenuItem, pfGUIButtonMod)

public:
    enum ItemFlags { kDrawSubMenuArrow = kDerivedFlagsStart, kReportHovers };

public:
    pfGUIMenuItem()
    {
        fFlags.setName(kDrawSubMenuArrow, "kDrawSubMenuArrow");
        fFlags.setName(kReportHovers, "kReportHovers");
    }
};

#endif
