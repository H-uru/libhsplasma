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

#ifndef _PFGUIKNOBCTRL_H
#define _PFGUIKNOBCTRL_H

#include "pfGUIValueCtrl.h"
#include "Math/hsGeometry3.h"

DllClass pfGUIKnobCtrl : public virtual pfGUIValueCtrl {
    CREATABLE(pfGUIKnobCtrl, kGUIKnobCtrl, pfGUIValueCtrl)

public:
    enum KnobFlags {
        kReverseValues = kDerivedFlagsStart, kLeftRightOrientation,
        kMapToScreenRange, kTriggerOnlyOnMouseUp, kMapToAnimationRange
    };

protected:
    hsTArray<plKey> fAnimationKeys;
    plString fAnimName;
    hsVector3 fAnimStartPos, fAnimEndPos;
    unsigned int fEoaInt1, fEoaInt2, fEoaInt3, fEoaInt4;
    float fEoaFl1, fEoaFl2, fEoaFl3, fEoaFl4;

public:
    pfGUIKnobCtrl();

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

    plString getAnimName() const { return fAnimName; }
    hsVector3 getAnimStartPos() const { return fAnimStartPos; }
    hsVector3 getAnimEndPos() const { return fAnimEndPos; }

    void setAnimName(const plString& name) { fAnimName = name; }
    void setAnimStartPos(const hsVector3& pos) { fAnimStartPos = pos; }
    void setAnimEndPos(const hsVector3& pos) { fAnimEndPos = pos; }
};

#endif
