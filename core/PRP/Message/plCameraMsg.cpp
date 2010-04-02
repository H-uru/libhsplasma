#include "plCameraMsg.h"

/* plCameraConfig */
plCameraConfig::plCameraConfig()
              : fAccel(0.0f), fDecel(0.0f), fVel(0.0f), fFPAccel(0.0f),
                fFPDecel(0.0f), fFPVel(0.0f), fFOVw(0.0f), fFOVh(0.0f),
                fWorldspace(false) { }

void plCameraConfig::read(hsStream* S) {
    fAccel = S->readFloat();
    fDecel = S->readFloat();
    fVel = S->readFloat();
    fFPAccel = S->readFloat();
    fFPDecel = S->readFloat();
    fFPVel = S->readFloat();
    fFOVw = S->readFloat();
    fFOVh = S->readFloat();
    fOffset.read(S);
    fWorldspace = S->readBool();
}

void plCameraConfig::write(hsStream* S) {
    S->writeFloat(fAccel);
    S->writeFloat(fDecel);
    S->writeFloat(fVel);
    S->writeFloat(fFPAccel);
    S->writeFloat(fFPDecel);
    S->writeFloat(fFPVel);
    S->writeFloat(fFOVw);
    S->writeFloat(fFOVh);
    fOffset.write(S);
    S->writeBool(fWorldspace);
}

void plCameraConfig::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plCameraConfig");
    prc->writeParam("Worldspace", fWorldspace);
    prc->writeParam("FOVw", fFOVw);
    prc->writeParam("FOVh", fFOVh);
    prc->endTag();

    prc->startTag("Params");
    prc->writeParam("Accel", fAccel);
    prc->writeParam("Decel", fDecel);
    prc->writeParam("Vel", fVel);
    prc->endTag(true);

    prc->startTag("FPParams");
    prc->writeParam("Accel", fFPAccel);
    prc->writeParam("Decel", fFPDecel);
    prc->writeParam("Vel", fFPVel);
    prc->endTag(true);

    prc->writeSimpleTag("Offset");
    fOffset.prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}

void plCameraConfig::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plCameraConfig")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fWorldspace = tag->getParam("Worldspace", "false").toBool();
    fFOVw = tag->getParam("FOVw", "0").toFloat();
    fFOVh = tag->getParam("FOVh", "0").toFloat();

    const pfPrcTag* child = tag->getFirstChild();
    size_t nChildren = tag->countChildren();
    for (size_t i=0; i<nChildren; i++) {
        if (child->getName() == "Params") {
            fAccel = child->getParam("Accel", "0").toFloat();
            fDecel = child->getParam("Decel", "0").toFloat();
            fVel = child->getParam("Vel", "0").toFloat();
        } else if (child->getName() == "FPParams") {
            fFPAccel = child->getParam("Accel", "0").toFloat();
            fFPDecel = child->getParam("Decel", "0").toFloat();
            fFPVel = child->getParam("Vel", "0").toFloat();
        } else if (child->getName() == "Offset") {
            if (child->hasChildren())
                fOffset.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* plCameraMsg */
plCameraMsg::plCameraMsg() : fTransTime(0.0), fActivated(false) {
    fCmd.setName(kSetSubject, "kSetSubject");
    fCmd.setName(kCameraMod, "kCameraMod");
    fCmd.setName(kSetAsPrimary, "kSetAsPrimary");
    fCmd.setName(kTransitionTo, "kTransitionTo");
    fCmd.setName(kPush, "kPush");
    fCmd.setName(kPop, "kPop");
    fCmd.setName(kEntering, "kEntring");
    fCmd.setName(kCut, "kCut");
    fCmd.setName(kResetOnEnter, "kResetOnEnter");
    fCmd.setName(kResetOnExit, "kResetOnExit");
    fCmd.setName(kChangeParams, "kChangeParams");
    fCmd.setName(kWorldspace, "kWorldspace");
    fCmd.setName(kCreateNewDefaultCam, "kCreateNewDefaultCam");
    fCmd.setName(kRegionPushCamera, "kRegionPushCamera");
    fCmd.setName(kRegionPopCamera, "kRegionPopCamera");
    fCmd.setName(kRegionPushPOA, "kRegionPushPOA");
    fCmd.setName(kRegionPopPOA, "kRegionPopPOA");
    fCmd.setName(kFollowLocalPlayer, "kFollowLocalPlayer");
    fCmd.setName(kResponderTrigger, "kResponderTrigger");
    fCmd.setName(kSetFOV, "kSetFOV");
    fCmd.setName(kAddFOVKeyFrame, "kAddFOVKeyFrame");
    fCmd.setName(kStartZoomIn, "kStartZoomIn");
    fCmd.setName(kStartZoomOut, "kStartZoomOut");
    fCmd.setName(kStopZoom, "kStopZoom");
    fCmd.setName(kSetAnimated, "kSetAnimated");
    fCmd.setName(kPythonOverridePush, "kPythonOverridePush");
    fCmd.setName(kPythonOverridePop, "kPythonOverridePop");
    fCmd.setName(kPythonOverridePushCut, "kPythonOverridePushCut");
    fCmd.setName(kPythonSetFirstPersonOverrideEnable, "kPythonSetFirstPersonOverrideEnable");
    fCmd.setName(kPythonUndoFirstPerson, "kPythonUndoFirstPerson");
    fCmd.setName(kUpdateCameras, "kUpdateCameras");
    fCmd.setName(kResponderSetThirdPerson, "kResponderSetThirdPerson");
    fCmd.setName(kResponderUndoThirdPerson, "kResponderUndoThirdPerson");
    fCmd.setName(kNonPhysOn, "kNonPhysOn");
    fCmd.setName(kNonPhysOff, "kNonPhysOff");
    fCmd.setName(kResetPanning, "kResetPanning");
}

void plCameraMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCmd.read(S);
    fTransTime = S->readDouble();
    fActivated = S->readBool();
    fNewCam = mgr->readKey(S);
    fTriggerer = mgr->readKey(S);
    fConfig.read(S);
}

void plCameraMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    fCmd.write(S);
    S->writeDouble(fTransTime);
    S->writeBool(fActivated);
    mgr->writeKey(S, fNewCam);
    mgr->writeKey(S, fTriggerer);
    fConfig.write(S);
}

void plCameraMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();

    prc->startTag("CameraParams");
    prc->writeParam("TransTime", fTransTime);
    prc->writeParam("Activated", fActivated);
    prc->endTag(true);

    prc->writeSimpleTag("NewCam");
    fNewCam->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Triggerer");
    fTriggerer->prcWrite(prc);
    prc->closeTag();

    fConfig.prcWrite(prc);
}

void plCameraMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "CameraParams") {
        fTransTime = tag->getParam("TransTime", "0").toFloat();
        fActivated = tag->getParam("Activated", "false").toBool();
    } else if (tag->getName() == "NewCam") {
        if (tag->hasChildren())
            fNewCam = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Triggerer") {
        if (tag->hasChildren())
            fTriggerer = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "plCameraConfig") {
        fConfig.prcParse(tag);
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
