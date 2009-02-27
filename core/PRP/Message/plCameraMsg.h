#ifndef _PLCAMERAMSG_H
#define _PLCAMERAMSG_H

#include "plMessage.h"
#include "Math/hsGeometry3.h"
#include "Util/hsBitVector.h"

DllClass plCameraConfig {
public:
    enum {
        kOffset = 0x1,
        kSpeeds = 0x2,
        kFOV = 0x4
    };

protected:
    hsVector3 fOffset;
    float fAccel, fDecel, fVel;
    float fFPAccel, fFPDecel, fFPVel;
    float fFOVw, fFOVh;
    bool fWorldspace;

public:
    plCameraConfig();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plCameraMsg : public plMessage {
public:
    enum ModCmds {
        kSetSubject, kCameraMod, kSetAsPrimary, kTransitionTo, kPush, kPop,
        kEntering, kCut, kResetOnEnter, kResetOnExit, kChangeParams,
        kWorldspace, kCreateNewDefaultCam, kRegionPushCamera, kRegionPopCamera,
        kRegionPushPOA, kRegionPopPOA, kFollowLocalPlayer, kResponderTrigger,
        kSetFOV, kAddFOVKeyFrame, kStartZoomIn, kStartZoomOut, kStopZoom,
        kSetAnimated, kPythonOverridePush, kPythonOverridePop,
        kPythonOverridePushCut, kPythonSetFirstPersonOverrideEnable,
        kPythonUndoFirstPerson, kUpdateCameras, kResponderSetThirdPerson,
        kResponderUndoThirdPerson, kNonPhysOn, kNonPhysOff, kResetPanning,
        kNumCmds
    };

protected:
    plKey fNewCam, fTriggerer;
    double fTransTime;
    plCameraConfig fConfig;
    bool fActivated;
    hsBitVector fCmd;

public:
    plCameraMsg();
    virtual ~plCameraMsg();

    DECLARE_CREATABLE(plCameraMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
