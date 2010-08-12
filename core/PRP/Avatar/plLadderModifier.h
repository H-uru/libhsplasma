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

#ifndef _PLLADDERMODIFIER_H
#define _PLLADDERMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

DllClass plAvLadderMod : public virtual plSingleModifier {
    CREATABLE(plAvLadderMod, kAvLadderMod, plSingleModifier)

public:
    enum TypeField { kBig, kFourFeet, kTwoFeet, kNumTypeFields };

protected:
    bool fGoingUp, fEnabled, fAvatarInBox, fAvatarMounting;
    int fType, fLoops;
    hsVector3 fLadderView;

public:
    plAvLadderMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plLadderModifier : public virtual plSingleModifier {
    CREATABLE(plLadderModifier, kLadderModifier, plSingleModifier)

protected:
    plKey fTopLogic, fBottomLogic, fMainLogic;
    plKey fExitTop, fExitBottom, fTopPos, fBottomPos;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
