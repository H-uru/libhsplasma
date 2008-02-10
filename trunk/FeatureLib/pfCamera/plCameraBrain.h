#ifndef _PLCAMERABRAIN_H
#define _PLCAMERABRAIN_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsBitVector.h"

DllClass plCameraBrain : public hsKeyedObject {
public:
    plCameraBrain();
    virtual ~plCameraBrain();

    DECLARE_CREATABLE(plCameraBrain)
};

DllClass plCameraBrain_M5 : public plCameraBrain {
public:
    plCameraBrain_M5();
    virtual ~plCameraBrain_M5();

    DECLARE_CREATABLE(plCameraBrain_M5)
};

DllClass plCameraBrain_Novice : public plCameraBrain_M5 {
public:
    plCameraBrain_Novice();
    virtual ~plCameraBrain_Novice();

    DECLARE_CREATABLE(plCameraBrain_Novice)
};

DllClass plCameraBrain_NovicePlus : public plCameraBrain_M5 {
public:
    plCameraBrain_NovicePlus();
    virtual ~plCameraBrain_NovicePlus();

    DECLARE_CREATABLE(plCameraBrain_NovicePlus)
};

DllClass plCameraBrain_Expert : public plCameraBrain_M5 {
public:
    plCameraBrain_Expert();
    virtual ~plCameraBrain_Expert();

    DECLARE_CREATABLE(plCameraBrain_Expert)
};

DllClass plCameraBrain_Flight : public plCameraBrain_M5 {
public:
    plCameraBrain_Flight();
    virtual ~plCameraBrain_Flight();

    DECLARE_CREATABLE(plCameraBrain_Flight)
};

DllClass plCameraBrain_Ground : public plCameraBrain_M5 {
public:
    plCameraBrain_Ground();
    virtual ~plCameraBrain_Ground();

    DECLARE_CREATABLE(plCameraBrain_Ground)
};

DllClass plCameraBrain1 : public plCameraBrain {
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
    hsBitVector fMoveFlags, fFlags;

public:
    plCameraBrain1();
    virtual ~plCameraBrain1();

    DECLARE_CREATABLE(plCameraBrain1)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plCameraBrain1_Drive : public plCameraBrain1 {
public:
    plCameraBrain1_Drive();
    virtual ~plCameraBrain1_Drive();

    DECLARE_CREATABLE(plCameraBrain1_Drive)
};

DllClass plCameraBrain1_Avatar : public plCameraBrain1 {
protected:
    hsVector3 fOffset;

public:
    plCameraBrain1_Avatar();
    virtual ~plCameraBrain1_Avatar();

    DECLARE_CREATABLE(plCameraBrain1_Avatar)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plCameraBrain1_FirstPerson : public plCameraBrain1_Avatar {
public:
    plCameraBrain1_FirstPerson();
    virtual ~plCameraBrain1_FirstPerson();

    DECLARE_CREATABLE(plCameraBrain1_FirstPerson)
};

DllClass plCameraBrain1_Fixed : public plCameraBrain1 {
protected:
    plKey fTargetPoint;

public:
    plCameraBrain1_Fixed();
    virtual ~plCameraBrain1_Fixed();

    DECLARE_CREATABLE(plCameraBrain1_Fixed)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plCameraBrain1_Circle : public plCameraBrain1_Fixed {
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
    hsPoint3 fCenter;
    float fRadius;
    plKey fCenterObject, fPOAObject;
    float fCirPerSec;

public:
    plCameraBrain1_Circle();
    virtual ~plCameraBrain1_Circle();

    DECLARE_CREATABLE(plCameraBrain1_Circle)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
