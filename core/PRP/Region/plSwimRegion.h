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

DllClass plSwimRegionInterface : public virtual plObjInterface {
    CREATABLE(plSwimRegionInterface, kSwimRegionInterface, plObjInterface)

protected:
    float fDownBuoyancy, fUpBuoyancy, fMaxUpwardVel;

public:
    plSwimRegionInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSwimCircularCurrentRegion : public virtual plSwimRegionInterface {
    CREATABLE(plSwimCircularCurrentRegion, kSwimCircularCurrentRegion,
              plSwimRegionInterface)

protected:
    float fRotation;
    float fPullNearDistSq, fPullFarDistSq;
    float fPullNearVel, fPullFarVel;
    plKey fCurrentObj;

public:
    plSwimCircularCurrentRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSwimStraightCurrentRegion : public virtual plSwimRegionInterface {
    CREATABLE(plSwimStraightCurrentRegion, kSwimStraightCurrentRegion,
              plSwimRegionInterface)

protected:
    float fNearDist, fFarDist;
    float fNearVel, fFarVel;
    plKey fCurrentObj;

public:
    plSwimStraightCurrentRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
