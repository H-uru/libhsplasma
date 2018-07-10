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

#ifndef _PLCAMERABRAIN_H
#define _PLCAMERABRAIN_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Math/hsGeometry3.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plCameraBrain : public hsKeyedObject {
    CREATABLE(plCameraBrain, kCameraBrain, hsKeyedObject)
};

class PLASMA_DLL plCameraBrain_M5 : public plCameraBrain {
    CREATABLE(plCameraBrain_M5, kCameraBrain_M5, plCameraBrain)
};

class PLASMA_DLL plCameraBrain_Novice : public plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Novice, kCameraBrain_Novice, plCameraBrain_M5)
};

class PLASMA_DLL plCameraBrain_NovicePlus : public plCameraBrain_M5 {
    CREATABLE(plCameraBrain_NovicePlus, kCameraBrain_NovicePlus, plCameraBrain_M5)
};

class PLASMA_DLL plCameraBrain_Expert : public plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Expert, kCameraBrain_Expert, plCameraBrain_M5)
};

class PLASMA_DLL plCameraBrain_Flight : public plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Flight, kCameraBrain_Flight, plCameraBrain_M5)
};

class PLASMA_DLL plCameraBrain_Ground : public plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Ground, kCameraBrain_Ground, plCameraBrain_M5)
};


class PLASMA_DLL plCameraBrain1 : public plCameraBrain {
    CREATABLE(plCameraBrain1, kCameraBrain1, plCameraBrain)

public:
    enum {
        kCutPos, kCutPosOnce, kCutPOA, kCutPOAOnce, kAnimateFOV,
        kFollowLocalAvatar, kPanicVelocity, kRailComponent, kSubject,
        kCircleTarget, kMaintainLOS, kZoomEnabled, kIsTransitionCamera,
        kWorldspacePOA, kWorldspacePos, kCutPosWhilePan, kCutPOAWhilePan,
        kNonPhys, kNeverAnimateFOV, kIgnoreSubworldMovement, kFalling,
        kRunning, kVerticalWhenFalling, kSpeedUpWhenRunning, kFallingStopped,
        kBeginFalling
    };

protected:
    plKey fSubject, fRail;
    float fVelocity, fAccel, fDecel;
    float fPOAVelocity, fPOAAccel, fPOADecel;
    hsVector3 fPOAOffset;
    float fXPanLimit, fZPanLimit, fPanSpeed;
    float fZoomRate, fZoomMax, fZoomMin;
    hsBitVector fFlags, fEoaFlags;

public:
    plCameraBrain1();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    plKey getSubject() const { return fSubject; }
    plKey getRail() const { return fRail; }
    float getVelocity() const { return fVelocity; }
    float getAcceleration() const { return fAccel; }
    float getDeceleration() const { return fDecel; }
    float getPOAVelocity() const { return fPOAVelocity; }
    float getPOAAcceleration() const { return fPOAAccel; }
    float getPOADeceleration() const { return fPOADecel; }
    hsVector3 getPOAOffset() const { return fPOAOffset; }
    float getXPanLimit() const { return fXPanLimit; }
    float getZPanLimit() const { return fZPanLimit; }
    float getPanSpeed() const { return fPanSpeed; }
    float getZoomRate() const { return fZoomRate; }
    float getZoomMax() const { return fZoomMax; }
    float getZoomMin() const { return fZoomMin; }
    const hsBitVector& getFlags() const { return fFlags; }
    hsBitVector& getFlags() { return fFlags; }
    const hsBitVector& getEoAFlags() const { return fEoaFlags; }
    hsBitVector& getEoAFlags() { return fEoaFlags; }

    void setSubject(const plKey& subject) { fSubject = subject; }
    void setRail(const plKey& rail) { fRail = rail; }
    void setVelocity(float velocity) { fVelocity = velocity; }
    void setAcceleration(float acceleration) { fAccel = acceleration; }
    void setDeceleration(float deceleration) { fDecel = deceleration; }
    void setPOAVelocity(float poaVelocity) { fPOAVelocity = poaVelocity; }
    void setPOAAcceleration(float poaAcceleration) { fPOAAccel = poaAcceleration; }
    void setPOADeceleration(float poaDeceleration) { fPOADecel = poaDeceleration; }
    void setPOAOffset(hsVector3 poaOffset) { fPOAOffset = poaOffset; }
    void setXPanLimit(float xPanLimit) { fXPanLimit = xPanLimit; }
    void setZPanLimit(float zPanLimit) { fZPanLimit = zPanLimit; }
    void setPanSpeed(float panSpeed) { fPanSpeed = panSpeed; }
    void setZoomRate(float zoomRate) { fZoomRate = zoomRate; }
    void setZoomMax(float zoomMax) { fZoomMax = zoomMax; }
    void setZoomMin(float zoomMin) { fZoomMin = zoomMin; }

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plCameraBrain1_Drive : public plCameraBrain1 {
    CREATABLE(plCameraBrain1_Drive, kCameraBrain1_Drive, plCameraBrain1)
};


class PLASMA_DLL plCameraBrain1_Avatar : public plCameraBrain1 {
    CREATABLE(plCameraBrain1_Avatar, kCameraBrain1_Avatar, plCameraBrain1)

protected:
    hsVector3 fOffset;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getOffset() const { return fOffset; }
    void setOffset(const hsVector3& offset) { fOffset = offset; }
};


class PLASMA_DLL plCameraBrain1_FirstPerson : public plCameraBrain1_Avatar {
    CREATABLE(plCameraBrain1_FirstPerson, kCameraBrain1_FirstPerson,
              plCameraBrain1_Avatar)
};


class PLASMA_DLL plCameraBrain1_Fixed : public plCameraBrain1 {
    CREATABLE(plCameraBrain1_Fixed, kCameraBrain1_Fixed, plCameraBrain1)

protected:
    plKey fTargetPoint;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getTargetPoint() const { return fTargetPoint; }
    void setTargetPoint(const plKey& targetPoint) { fTargetPoint = targetPoint; }
};


class PLASMA_DLL plCameraBrain1_Circle : public plCameraBrain1_Fixed {
    CREATABLE(plCameraBrain1_Circle, kCameraBrain1_Circle, plCameraBrain1_Fixed)

public:
    enum CircleFlags {
        kLagged = 0x1,
        kAbsoluteLag = 0x3,
        kFarthest = 0x4,
        kTargetted = 0x8,
        kHasCenterObject = 0x10,
        kPOAObject = 0x20,
        kCircleLocalAvatar = 0x40
    };

protected:
    unsigned int fCircleFlags;
    hsVector3 fCenter;
    float fRadius;
    plKey fCenterObject, fPOAObject;
    float fCirPerSec;

public:
    plCameraBrain1_Circle() : fCircleFlags(0), fRadius(0), fCirPerSec(0) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getCircleFlags() const { return fCircleFlags; }
    hsVector3 getCenter() const { return fCenter; }
    float getRadius() const { return fRadius; }
    plKey getCenterObject() const { return fCenterObject; }
    plKey getPOAObject() const { return fPOAObject; }
    float getCirPerSec() const { return fCirPerSec; }

    void setCircleFlags(unsigned int flags) { fCircleFlags = flags; }
    void setCenter(const hsVector3& center) { fCenter = center; }
    void setRadius(float radius) { fRadius = radius; }
    void setCenterObject(const plKey& center) { fCenterObject = center; }
    void setPOAObject(const plKey& poa) { fPOAObject = poa; }
    void setCirPerSec(float cirPerSec) { fCirPerSec = cirPerSec; }
};

#endif
