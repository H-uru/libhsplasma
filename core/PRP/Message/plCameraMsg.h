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

class PLASMA_DLL plCameraConfig
{
public:
    enum
    {
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
    plCameraConfig()
        : fAccel(), fDecel(), fVel(), fFPAccel(), fFPDecel(), fFPVel(),
          fFOVw(), fFOVh(), fWorldspace() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    hsVector3 getOffset() const { return fOffset; }
    float getAccel() const { return fAccel; }
    float getDecel() const { return fDecel; }
    float getVel() const { return fVel; }
    float getFPAccel() const { return fFPAccel; }
    float getFPDecel() const { return fFPDecel; }
    float getFPVel() const { return fFPVel; }
    float getFOVw() const { return fFOVw; }
    float getFOVh() const { return fFOVh; }
    bool getWorldspace() const { return fWorldspace; }

    void setOffset(const hsVector3& offset) { fOffset = offset; }
    void setAccel(float accel) { fAccel = accel; }
    void setDecel(float decel) { fDecel = decel; }
    void setVel(float vel) { fVel = vel; }
    void setFPAccel(float fpAccel) { fFPAccel = fpAccel; }
    void setFPDecel(float fpDecel) { fFPDecel = fpDecel; }
    void setFPVel(float fpVel) { fFPVel = fpVel; }
    void setFOVw(float fovW) { fFOVw = fovW; }
    void setFOVh(float fovH) { fFOVh = fovH; }
    void setWorldspace(bool worldspace) { fWorldspace = worldspace; }
};


class PLASMA_DLL plCameraMsg : public plMessage
{
    CREATABLE(plCameraMsg, kCameraMsg, plMessage)

public:
    enum ModCmds
    {
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

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getCmd(size_t idx) const { return fCmd.get(idx); }
    void setCmd(size_t idx, bool value=true) { fCmd.set(idx, value); }

    plKey getNewCam() const { return fNewCam; }
    plKey getTriggerer() const { return fTriggerer; }
    double getTransTime() const { return fTransTime; }
    const plCameraConfig& getConfig() const { return fConfig; }
    plCameraConfig& getConfig() { return fConfig; }
    bool getActivated() const { return fActivated; }

    void setNewCam(plKey newCam) { fNewCam = std::move(newCam); }
    void setTriggerer(plKey triggerer) { fTriggerer = std::move(triggerer); }
    void setTransTime(double time) { fTransTime = time; }
    void setConfig(const plCameraConfig& config) { fConfig = config; }
    void setActivated(bool activated) { fActivated = activated; }
};

#endif
