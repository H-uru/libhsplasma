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

#ifndef _PFGUIRADIOGROUPCTRL_H
#define _PFGUIRADIOGROUPCTRL_H

#include "pfGUIControlMod.h"

class PLASMA_DLL pfGUIRadioGroupCtrl : public pfGUIControlMod
{
    CREATABLE(pfGUIRadioGroupCtrl, kGUIRadioGroupCtrl, pfGUIControlMod)

public:
    enum RadioGroupFlags { kAllowNoSelection = kDerivedFlagsStart };

protected:
    std::vector<plKey> fControls;
    int fDefaultValue;

public:
    pfGUIRadioGroupCtrl() : fDefaultValue()
    {
        fFlags.setName(kAllowNoSelection, "kAllowNoSelection");
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getControls() const { return fControls; }
    std::vector<plKey>& getControls() { return fControls; }
    void addControl(plKey ctrl) { fControls.emplace_back(std::move(ctrl)); }
    void delControl(size_t idx) { fControls.erase(fControls.begin() + idx); }
    void clearControls() { fControls.clear(); }

    int getDefaultValue() const { return fDefaultValue; }
    void setDefaultValue(int value) { fDefaultValue = value; }
};

#endif
