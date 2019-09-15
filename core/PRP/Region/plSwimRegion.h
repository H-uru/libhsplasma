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

class PLASMA_DLL plSwimRegionInterface : public plObjInterface
{
    CREATABLE(plSwimRegionInterface, kSwimRegionInterface, plObjInterface)

public:
    enum { kDisable };

protected:
    float fDownBuoyancy, fUpBuoyancy, fMaxUpwardVel;

public:
    plSwimRegionInterface()
        : fDownBuoyancy(), fUpBuoyancy(), fMaxUpwardVel() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getDownBuoyancy() const { return fDownBuoyancy; }
    float getUpBuoyancy() const { return fUpBuoyancy; }
    float getMaxUpwardVel() const { return fMaxUpwardVel; }

    void setDownBuoyancy(float buoyancy) { fDownBuoyancy = buoyancy; }
    void setUpBuoyancy(float buoyancy) { fUpBuoyancy = buoyancy; }
    void setMaxUpwardVel(float vel) { fMaxUpwardVel = vel; }
};


class PLASMA_DLL plSwimCircularCurrentRegion : public plSwimRegionInterface
{
    CREATABLE(plSwimCircularCurrentRegion, kSwimCircularCurrentRegion,
              plSwimRegionInterface)

protected:
    float fRotation;
    float fPullNearDistSq, fPullFarDistSq;
    float fPullNearVel, fPullFarVel;
    plKey fCurrentObj;

public:
    plSwimCircularCurrentRegion()
        : fRotation(), fPullNearDistSq(), fPullFarDistSq(), fPullNearVel(),
          fPullFarVel() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getRotation() const { return fRotation; }
    float getPullNearDistSq() const { return fPullNearDistSq; }
    float getPullFarDistSq() const { return fPullNearDistSq; }
    float getPullNearVel() const { return fPullNearVel; }
    float getPullFarVel() const { return fPullFarVel; }
    plKey getCurrentObj() const { return fCurrentObj; }

    void setRotation(float rotation) { fRotation = rotation; }
    void setPullNearDistSq(float distSq) { fPullNearDistSq = distSq; }
    void setPullFarDistSq(float distSq) { fPullFarDistSq = distSq; }
    void setPullNearVel(float vel) { fPullNearVel = vel; }
    void setPullFarVel(float vel) { fPullFarVel = vel; }
    void setCurrentObj(plKey currentObj) { fCurrentObj = std::move(currentObj); }
};


class PLASMA_DLL plSwimStraightCurrentRegion : public plSwimRegionInterface
{
    CREATABLE(plSwimStraightCurrentRegion, kSwimStraightCurrentRegion,
              plSwimRegionInterface)

protected:
    float fNearDist, fFarDist;
    float fNearVel, fFarVel;
    plKey fCurrentObj;

public:
    plSwimStraightCurrentRegion()
        : fNearDist(), fFarDist(), fNearVel(), fFarVel() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getNearDist() const { return fNearDist; }
    float getFarDist() const { return fFarDist; }
    float getNearVel() const { return fNearVel; }
    float getFarVel() const { return fFarVel; }
    plKey getCurrentObj() const { return fCurrentObj; }

    void setNearDist(float dist) { fNearDist = dist; }
    void setFarDist(float dist) { fFarDist = dist; }
    void setNearVel(float vel) { fNearVel = vel; }
    void setFarVel(float vel) { fFarVel = vel; }
    void setCurrentObj(plKey currentObj) { fCurrentObj = std::move(currentObj); }
};

#endif
