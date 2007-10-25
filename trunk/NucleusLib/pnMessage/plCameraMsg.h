#ifndef _PLCAMERAMSG_H
#define _PLCAMERAMSG_H

#include "plMessage.h"
#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsBitVector.h"

DllClass plCameraConfig {
public:
    enum {
        kOffset = 0x1,
        kSpeeds = 0x2,
        kFOV = 0x4
    };

protected:
    int fType;
    hsPoint3 fOffset;
    float fAccel, fDecel, fVel;
    float fFPAccel, fFPDecel, fFPVel;
    float fFOVw, fFOVh;
    bool fWorldspace;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllClass plCameraMsg : public plMessage {
public:
    enum ModCmds {
        kSetSubject, kCameraMod, kSetAsPrimary, kTransitionTo, kPush, kPop,
        kEntering, kCut, kResetOnEnter, kResetOnExit, kChangeParams,
        kWorldspace, kCreateNewDefaultCam, kRegionPUshCamera, kRegionPopCamera,
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
    //plSceneObject* fSubject;
    //plPipeline* fPipe;
    plCameraConfig fConfig;
    bool fActivated;
    hsBitVector fCmd;

public:
    plCameraMsg();
    virtual ~plCameraMsg();

    DECLARE_CREATABLE(plCameraMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
