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

#ifndef _PLWINDBONEMOD_H
#define _PLWINDBONEMOD_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plWindBoneOscillator
{
protected:
    float fDistX, fDistY, fDirX, fDirY, fSpeed;

public:
    plWindBoneOscillator()
        : fDistX(), fDistY(), fDirX(), fDirY(), fSpeed() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

class PLASMA_DLL plWindBoneMod : public plModifier
{
    CREATABLE(plWindBoneMod, kWindBoneMod, plModifier)

public:
    enum { kNumOscillators = 4 };

protected:
    plWindBoneOscillator fOscillators[kNumOscillators];
    std::vector<plKey> fTargets;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    size_t getTargetsCount() const HS_OVERRIDE { return fTargets.size(); }
    plKey getTarget(size_t pos) const HS_OVERRIDE { return fTargets[pos]; };
    void addTarget(plKey target) HS_OVERRIDE { fTargets.emplace_back(std::move(target)); };
    void removeTarget(const plKey& target) HS_OVERRIDE;
};

#endif

