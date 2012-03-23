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

class PLASMA_DLL plArmatureBrain : public plCreatable {
    CREATABLE(plArmatureBrain, kArmatureBrain, plCreatable)

public:
    plArmatureBrain() : plCreatable(), fAvBrainUserInt(0), fAvBrainUserFloat(0.0f), fAvBrainUserDouble(0.0) {}
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

private:
    uint32_t fAvBrainUserInt;
    float fAvBrainUserFloat;
    double fAvBrainUserDouble;
};


class PLASMA_DLL plAvBrainHuman : public plArmatureBrain {
    CREATABLE(plAvBrainHuman, kAvBrainHuman, plArmatureBrain)

protected:
    bool fIsCustomAvatar;

public:
    plAvBrainHuman();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isCustomAvatar() const { return fIsCustomAvatar; }
    void setIsCustomAvatar(bool value) { fIsCustomAvatar = value; }
};


class PLASMA_DLL plAvBrainClimb : public plArmatureBrain {
    CREATABLE(plAvBrainClimb, kAvBrainClimb, plArmatureBrain)
};


class PLASMA_DLL plAvBrainAvatar : public plArmatureBrain {
    CREATABLE(plAvBrainAvatar, kAvBrainAvatar, plArmatureBrain)
};

class PLASMA_DLL plAvBrainCritter : public plArmatureBrain {
    CREATABLE(plAvBrainCritter, kAvBrainCritter, plArmatureBrain)
};


class PLASMA_DLL plAvBrainDrive : public plArmatureBrain {
    CREATABLE(plAvBrainDrive, kAvBrainDrive, plArmatureBrain)
};


class PLASMA_DLL plAvBrainPirahna : public plArmatureBrain {
    CREATABLE(plAvBrainPirahna, kAvBrainPirahna, plArmatureBrain)
};


class PLASMA_DLL plAvBrainQuab : public plArmatureBrain {
    CREATABLE(plAvBrainQuab, kAvBrainQuab, plArmatureBrain)
};


class PLASMA_DLL plAvBrainRideAnimatedPhysical : public plArmatureBrain {
    CREATABLE(plAvBrainRideAnimatedPhysical, kAvBrainRideAnimatedPhysical,
              plArmatureBrain)
};


class PLASMA_DLL plAvBrainSwim : public plArmatureBrain {
    CREATABLE(plAvBrainSwim, kAvBrainSwim, plArmatureBrain)
};

#endif
