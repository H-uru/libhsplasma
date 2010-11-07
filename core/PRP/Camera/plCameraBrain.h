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

DllClass plCameraBrain : public virtual hsKeyedObject {
    CREATABLE(plCameraBrain, kCameraBrain, hsKeyedObject)
};

DllClass plCameraBrain_M5 : public virtual plCameraBrain {
    CREATABLE(plCameraBrain_M5, kCameraBrain_M5, plCameraBrain)
};

DllClass plCameraBrain_Novice : public virtual plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Novice, kCameraBrain_Novice, plCameraBrain_M5)
};

DllClass plCameraBrain_NovicePlus : public virtual plCameraBrain_M5 {
    CREATABLE(plCameraBrain_NovicePlus, kCameraBrain_NovicePlus, plCameraBrain_M5)
};

DllClass plCameraBrain_Expert : public virtual plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Expert, kCameraBrain_Expert, plCameraBrain_M5)
};

DllClass plCameraBrain_Flight : public virtual plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Flight, kCameraBrain_Flight, plCameraBrain_M5)
};

DllClass plCameraBrain_Ground : public virtual plCameraBrain_M5 {
    CREATABLE(plCameraBrain_Ground, kCameraBrain_Ground, plCameraBrain_M5)
};


DllClass plCameraBrain1 : public virtual plCameraBrain {
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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plCameraBrain1_Drive : public virtual plCameraBrain1 {
    CREATABLE(plCameraBrain1_Drive, kCameraBrain1_Drive, plCameraBrain1)
};


DllClass plCameraBrain1_Avatar : public virtual plCameraBrain1 {
    CREATABLE(plCameraBrain1_Avatar, kCameraBrain1_Avatar, plCameraBrain1)

protected:
    hsVector3 fOffset;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plCameraBrain1_FirstPerson : public virtual plCameraBrain1_Avatar {
    CREATABLE(plCameraBrain1_FirstPerson, kCameraBrain1_FirstPerson,
              plCameraBrain1_Avatar)
};


DllClass plCameraBrain1_Fixed : public virtual plCameraBrain1 {
    CREATABLE(plCameraBrain1_Fixed, kCameraBrain1_Fixed, plCameraBrain1)

protected:
    plKey fTargetPoint;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plCameraBrain1_Circle : public virtual plCameraBrain1_Fixed {
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
    plCameraBrain1_Circle();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
