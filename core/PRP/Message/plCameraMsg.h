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

#ifndef _PLCAMERAMSG_H
#define _PLCAMERAMSG_H

#include "plMessage.h"
#include "Math/hsGeometry3.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plCameraConfig {
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


class PLASMA_DLL plCameraMsg : public plMessage {
    CREATABLE(plCameraMsg, kCameraMsg, plMessage)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
