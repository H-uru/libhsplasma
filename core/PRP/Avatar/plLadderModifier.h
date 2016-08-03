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

class PLASMA_DLL plAvLadderMod : public plSingleModifier {
    CREATABLE(plAvLadderMod, kAvLadderMod, plSingleModifier)

public:
    enum TypeField { kBig, kFourFeet, kTwoFeet, kNumTypeFields };

protected:
    bool fGoingUp, fEnabled, fAvatarInBox, fAvatarMounting;
    int fType, fLoops;
    hsVector3 fLadderView;

public:
    plAvLadderMod() : fGoingUp(false), fEnabled(true), fAvatarInBox(false),
                      fAvatarMounting(false), fType(kBig), fLoops(0) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plLadderModifier : public plSingleModifier {
    CREATABLE(plLadderModifier, kLadderModifier, plSingleModifier)

protected:
    plKey fTopLogic, fBottomLogic, fMainLogic;
    plKey fExitTop, fExitBottom, fTopPos, fBottomPos;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
