#ifndef _PLLINEFOLLOWMOD_H
#define _PLLINEFOLLOWMOD_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "PubUtilLib/plInterp/plAnimPath.h"

DllClass plLineFollowMod : public plMultiModifier {
public:
    enum FollowMode {
        kFollowObject, kFollowListener, kFollowCamera, kFollowLocalAvatar
    };

    enum {
        kNone = 0,
        kFullMatrix = 0x1,
        kOffsetFeet = 0x2,
        kOffsetAng = 0x4,
        kOffset = kOffsetFeet | kOffsetAng,
        kOffsetClamp = 0x8,
        kForceToLine = 0x10,
        kSpeedClamp = 0x20,
        kSearchPopPos = 0x40
    };

protected:
    FollowMode fFollowMode;
    unsigned short fFollowFlags;
    plAnimPath* fPath;
    plKey fPathParent, fRefObj;
    hsVector3 fSearchPos;
    hsTArray<plKey> fStereizers;
    float fTanOffset, fOffset;
    float fOffsetClamp, fSpeedClamp;

public:
    plLineFollowMod();
    virtual ~plLineFollowMod();

    DECLARE_CREATABLE(plLineFollowMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plRailCameraMod : public plLineFollowMod {
protected:
    hsMatrix44 fDesiredMatrix;
    float fCurrentTime, fTargetTime;
    hsVector3 fGoal;
    int fFarthest;

public:
    plRailCameraMod();
    virtual ~plRailCameraMod();

    DECLARE_CREATABLE(plRailCameraMod)
};

#endif
