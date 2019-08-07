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

#ifndef _PFGUICHECKBOXCTRL_H
#define _PFGUICHECKBOXCTRL_H

#include "pfGUIControlMod.h"

class PLASMA_DLL pfGUICheckBoxCtrl : public pfGUIControlMod
{
    CREATABLE(pfGUICheckBoxCtrl, kGUICheckBoxCtrl, pfGUIControlMod)

protected:
    std::vector<plKey> fAnimKeys;
    ST::string fAnimName;
    bool fChecked;

public:
    pfGUICheckBoxCtrl() : fChecked() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getAnimKeys() const { return fAnimKeys; }
    std::vector<plKey>& getAnimKeys() { return fAnimKeys; }
    void addAnimKey(plKey key) { fAnimKeys.emplace_back(std::move(key)); }
    void delAnimKey(size_t idx) { fAnimKeys.erase(fAnimKeys.begin() + idx); }
    void clearAnimKeys() { fAnimKeys.clear(); }

    const ST::string& getAnimName() const { return fAnimName; }
    bool isChecked() const { return fChecked; }

    void setAnimName(const ST::string& name) { fAnimName = name; }
    void setChecked(bool checked) { fChecked = checked; }
};

#endif
