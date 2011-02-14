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

#ifndef _PLSHADOWMASTER_H
#define _PLSHADOWMASTER_H

#include "PRP/Object/plObjInterface.h"
#include "plLightInfo.h"

class PLASMA_DLL plShadowMaster : public virtual plObjInterface {
    CREATABLE(plShadowMaster, kShadowMaster, plObjInterface)

public:
    enum DrawProperties {
        kDisable, kSelfShadow, kNumProps
    };

protected:
    float fAttenDist, fMaxDist, fMinDist, fPower;
    unsigned int fMaxSize, fMinSize;

public:
    plShadowMaster();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAttenDist() const { return fAttenDist; }
    float getMaxDist() const { return fMaxDist; }
    float getMinDist() const { return fMinDist; }
    float getPower() const { return fPower; }
    unsigned int getMaxSize() const { return fMaxSize; }
    unsigned int getMinSize() const { return fMinSize; }

    void setAttenDist(float dist) { fAttenDist = dist; }
    void setDist(float min, float max) { fMinDist = min; fMaxDist = max; }
    void setPower(float power) { fPower = power; }
    void setSize(unsigned int min, unsigned int max) { fMinSize = min; fMaxSize = max; }
};


class PLASMA_DLL plPointShadowMaster : public virtual plShadowMaster {
    CREATABLE(plPointShadowMaster, kPointShadowMaster, plShadowMaster)
};


class PLASMA_DLL plDirectShadowMaster : public virtual plShadowMaster {
    CREATABLE(plDirectShadowMaster, kDirectShadowMaster, plShadowMaster)
};

#endif
