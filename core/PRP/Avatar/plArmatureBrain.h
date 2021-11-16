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

#ifndef _PLARMATUREBRAIN_H
#define _PLARMATUREBRAIN_H

#include "PRP/plCreatable.h"

class HSPLASMA_EXPORT plArmatureBrain : public plCreatable
{
    CREATABLE(plArmatureBrain, kArmatureBrain, plCreatable)

public:
    plArmatureBrain()
        : fAvBrainUserInt(), fAvBrainUserFloat(), fAvBrainUserDouble() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE { }

private:
    uint32_t fAvBrainUserInt;
    float fAvBrainUserFloat;
    double fAvBrainUserDouble;
};


class HSPLASMA_EXPORT plAvBrainHuman : public plArmatureBrain
{
    CREATABLE(plAvBrainHuman, kAvBrainHuman, plArmatureBrain)

protected:
    bool fIsCustomAvatar;

public:
    plAvBrainHuman() : fIsCustomAvatar() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool isCustomAvatar() const { return fIsCustomAvatar; }
    void setIsCustomAvatar(bool value) { fIsCustomAvatar = value; }
};


class HSPLASMA_EXPORT plAvBrainClimb : public plArmatureBrain
{
    CREATABLE(plAvBrainClimb, kAvBrainClimb, plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainAvatar : public plArmatureBrain
{
    CREATABLE(plAvBrainAvatar, kAvBrainAvatar, plArmatureBrain)
};

class HSPLASMA_EXPORT plAvBrainCritter : public plArmatureBrain
{
    CREATABLE(plAvBrainCritter, kAvBrainCritter, plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainDrive : public plArmatureBrain
{
    CREATABLE(plAvBrainDrive, kAvBrainDrive, plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainPirahna : public plArmatureBrain
{
    CREATABLE(plAvBrainPirahna, kAvBrainPirahna, plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainQuab : public plArmatureBrain
{
    CREATABLE(plAvBrainQuab, kAvBrainQuab, plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainRideAnimatedPhysical : public plArmatureBrain
{
    CREATABLE(plAvBrainRideAnimatedPhysical, kAvBrainRideAnimatedPhysical,
              plArmatureBrain)
};


class HSPLASMA_EXPORT plAvBrainSwim : public plArmatureBrain
{
    CREATABLE(plAvBrainSwim, kAvBrainSwim, plArmatureBrain)
};

#endif
