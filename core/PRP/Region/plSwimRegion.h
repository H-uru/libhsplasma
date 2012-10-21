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

#ifndef _PLSWIMREGION_H
#define _PLSWIMREGION_H

#include "PRP/Object/plObjInterface.h"

class PLASMA_DLL plSwimRegionInterface : public virtual plObjInterface {
    CREATABLE(plSwimRegionInterface, kSwimRegionInterface, plObjInterface)

protected:
    float fDownBuoyancy, fUpBuoyancy, fMaxUpwardVel;

public:
    plSwimRegionInterface()
        : fDownBuoyancy(0.0f), fUpBuoyancy(0.0f), fMaxUpwardVel(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plSwimCircularCurrentRegion : public virtual plSwimRegionInterface {
    CREATABLE(plSwimCircularCurrentRegion, kSwimCircularCurrentRegion,
              plSwimRegionInterface)

protected:
    float fRotation;
    float fPullNearDistSq, fPullFarDistSq;
    float fPullNearVel, fPullFarVel;
    plKey fCurrentObj;

public:
    plSwimCircularCurrentRegion()
        : fRotation(0.0f), fPullNearDistSq(0.0f), fPullFarDistSq(0.0f),
          fPullNearVel(0.0f), fPullFarVel(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plSwimStraightCurrentRegion : public virtual plSwimRegionInterface {
    CREATABLE(plSwimStraightCurrentRegion, kSwimStraightCurrentRegion,
              plSwimRegionInterface)

protected:
    float fNearDist, fFarDist;
    float fNearVel, fFarVel;
    plKey fCurrentObj;

public:
    plSwimStraightCurrentRegion()
        : fNearDist(0.0f), fFarDist(0.0f), fNearVel(0.0f), fFarVel(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
