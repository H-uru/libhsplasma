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

#ifndef _PFGUIPROGRESSCTRL_H
#define _PFGUIPROGRESSCTRL_H

#include "pfGUIValueCtrl.h"

class PLASMA_DLL pfGUIProgressCtrl : public virtual pfGUIValueCtrl {
    CREATABLE(pfGUIProgressCtrl, kGUIProgressCtrl, pfGUIValueCtrl)

public:
    enum ProgressFlags {
        kReverseValues = kDerivedFlagsStart, kLeftRightOrientation,
        kMapToScreenRange, kTriggerOnlyOnMouseUp, kMapToAnimationRange
    };

protected:
    std::vector<plKey> fAnimationKeys;
    plString fAnimName;

public:
    pfGUIProgressCtrl();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const std::vector<plKey>& getAnimKeys() const { return fAnimationKeys; }
    std::vector<plKey>& getAnimKeys() { return fAnimationKeys; }
    void addAnimKey(plKey key) { fAnimationKeys.push_back(key); }
    void delAnimKey(size_t idx) { fAnimationKeys.erase(fAnimationKeys.begin() + idx); }
    void clearAnimKeys() { fAnimationKeys.clear(); }

    const plString& getAnimName() const { return fAnimName; }
    void setAnimName(const plString& name) { fAnimName = name; }
};

#endif
