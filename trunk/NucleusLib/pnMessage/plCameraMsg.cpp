#include "plCameraMsg.h"

/* plCameraConfig */
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


/* plCameraMsg */
plCameraMsg::plCameraMsg() : fTransTime(0.0), fActivated(false) { }
plCameraMsg::~plCameraMsg() { }

IMPLEMENT_CREATABLE(plCameraMsg, kCameraMsg, plMessage)

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

void plCameraMsg::prcWrite(pfPrcHelper* prc) {
    plMessage::prcWrite(prc);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Params");
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
