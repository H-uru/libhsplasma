#include "plCameraBrain.h"

/* plCameraBrain */
plCameraBrain::plCameraBrain() { }
plCameraBrain::~plCameraBrain() { }

IMPLEMENT_CREATABLE(plCameraBrain, kCameraBrain, hsKeyedObject)


/* plCameraBrain_M5 */
plCameraBrain_M5::plCameraBrain_M5() { }
plCameraBrain_M5::~plCameraBrain_M5() { }

IMPLEMENT_CREATABLE(plCameraBrain_M5, kCameraBrain_M5, plCameraBrain)


/* plCameraBrain_Novice */
plCameraBrain_Novice::plCameraBrain_Novice() { }
plCameraBrain_Novice::~plCameraBrain_Novice() { }

IMPLEMENT_CREATABLE(plCameraBrain_Novice, kCameraBrain_Novice, plCameraBrain_M5)


/* plCameraBrain_NovicePlus */
plCameraBrain_NovicePlus::plCameraBrain_NovicePlus() { }
plCameraBrain_NovicePlus::~plCameraBrain_NovicePlus() { }

IMPLEMENT_CREATABLE(plCameraBrain_NovicePlus, kCameraBrain_NovicePlus,
                    plCameraBrain_M5)


/* plCameraBrain_Expert */
plCameraBrain_Expert::plCameraBrain_Expert() { }
plCameraBrain_Expert::~plCameraBrain_Expert() { }

IMPLEMENT_CREATABLE(plCameraBrain_Expert, kCameraBrain_Expert, plCameraBrain_M5)


/* plCameraBrain_Flight */
plCameraBrain_Flight::plCameraBrain_Flight() { }
plCameraBrain_Flight::~plCameraBrain_Flight() { }

IMPLEMENT_CREATABLE(plCameraBrain_Flight, kCameraBrain_Flight, plCameraBrain_M5)


/* plCameraBrain_Ground */
plCameraBrain_Ground::plCameraBrain_Ground() { }
plCameraBrain_Ground::~plCameraBrain_Ground() { }

IMPLEMENT_CREATABLE(plCameraBrain_Ground, kCameraBrain_Ground, plCameraBrain_M5)


/* plCameraBrain1 */
plCameraBrain1::plCameraBrain1()
              : fVelocity(30.0f), fAccel(30.0f), fDecel(30.0f),
                fPOAVelocity(30.0f), fPOAAccel(30.0f), fPOADecel(30.0f),
                fXPanLimit(0.0f), fZPanLimit(0.0f), fPanSpeed(0.5f),
                fZoomRate(0.0f), fZoomMax(0.0f), fZoomMin(0.0f) {
    fFlags.setName(kCutPos, "kCutPos");
    fFlags.setName(kCutPosOnce, "kCutPosOnce");
    fFlags.setName(kCutPOA, "kCutPOA");
    fFlags.setName(kCutPOAOnce, "kCutPOAOnce");
    fFlags.setName(kAnimateFOV, "kAnimateFOV");
    fFlags.setName(kFollowLocalAvatar, "kFollowLocalAvatar");
    fFlags.setName(kPanicVelocity, "kPanicVelocity");
    fFlags.setName(kRailComponent, "kRailComponent");
    fFlags.setName(kSubject, "kSubject");
    fFlags.setName(kCircleTarget, "kCircleTarget");
    fFlags.setName(kMaintainLOS, "kMaintainLOS");
    fFlags.setName(kZoomEnabled, "kZoomEnabled");
    fFlags.setName(kIsTransitionCamera, "kIsTransitionCamera");
    fFlags.setName(kWorldspacePOA, "kWorldspacePOA");
    fFlags.setName(kWorldspacePos, "kWorldspacePos");
    fFlags.setName(kCutPosWhilePan, "kCutPosWhilePan");
    fFlags.setName(kCutPOAWhilePan, "kCutPOAWhilePan");
    fFlags.setName(kNonPhys, "kNonPhys");
    fFlags.setName(kNeverAnimateFOV, "kNeverAnimateFOV");
    fFlags.setName(kIgnoreSubworldMovement, "kIgnoreSubworldMovement");
    fFlags.setName(kFalling, "kFalling");
    fFlags.setName(kRunning, "kRunning");
    fFlags.setName(kVerticalWhenFalling, "kVerticalWhenFalling");
    fFlags.setName(kSpeedUpWhenRunning, "kSpeedUpWhenRunning");
    fFlags.setName(kFallingStopped, "kFallingStopped");
    fFlags.setName(kBeginFalling, "kBeginFalling");
}

plCameraBrain1::~plCameraBrain1() { }

IMPLEMENT_CREATABLE(plCameraBrain1, kCameraBrain1, plCameraBrain)

void plCameraBrain1::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fPOAOffset.read(S);
    fSubject = mgr->readKey(S);
    fRail = mgr->readKey(S);
    fFlags.read(S);

    fAccel = S->readFloat();
    fDecel = S->readFloat();
    fVelocity = S->readFloat();
    fPOAAccel = S->readFloat();
    fPOADecel = S->readFloat();
    fPOAVelocity = S->readFloat();
    fXPanLimit = S->readFloat();
    fZPanLimit = S->readFloat();
    fZoomRate = S->readFloat();
    fZoomMin = S->readFloat();
    fZoomMax = S->readFloat();
}

void plCameraBrain1::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    fPOAOffset.write(S);
    mgr->writeKey(S, fSubject);
    mgr->writeKey(S, fRail);
    fFlags.write(S);

    S->writeFloat(fAccel);
    S->writeFloat(fDecel);
    S->writeFloat(fVelocity);
    S->writeFloat(fPOAAccel);
    S->writeFloat(fPOADecel);
    S->writeFloat(fPOAVelocity);
    S->writeFloat(fXPanLimit);
    S->writeFloat(fZPanLimit);
    S->writeFloat(fZoomRate);
    S->writeFloat(fZoomMin);
    S->writeFloat(fZoomMax);
}

void plCameraBrain1::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Subject");
    fSubject->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Rail");
    fRail->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Flags");
    fFlags.prcWrite(prc);
    prc->closeTag();

    prc->startTag("CameraParams");
    prc->writeParam("Accel", fAccel);
    prc->writeParam("Decel", fDecel);
    prc->writeParam("Velocity", fVelocity);
    prc->writeParam("POAAccel", fPOAAccel);
    prc->writeParam("POADecel", fPOADecel);
    prc->writeParam("POAVelocity", fPOAVelocity);
    prc->writeParam("XPanLimit", fXPanLimit);
    prc->writeParam("ZPanLimit", fZPanLimit);
    prc->writeParam("ZoomRate", fZoomRate);
    prc->writeParam("ZoomMin", fZoomMin);
    prc->writeParam("ZoomMax", fZoomMax);
    prc->endTag(true);

    prc->writeSimpleTag("POAOffset");
    fPOAOffset.prcWrite(prc);
    prc->closeTag();
}


/* plCameraBrain1_Drive */
plCameraBrain1_Drive::plCameraBrain1_Drive() { }
plCameraBrain1_Drive::~plCameraBrain1_Drive() { }

IMPLEMENT_CREATABLE(plCameraBrain1_Drive, kCameraBrain1_Drive, plCameraBrain1)


/* plCameraBrain1_Avatar */
plCameraBrain1_Avatar::plCameraBrain1_Avatar() { }
plCameraBrain1_Avatar::~plCameraBrain1_Avatar() { }

IMPLEMENT_CREATABLE(plCameraBrain1_Avatar, kCameraBrain1_Avatar, plCameraBrain1)

void plCameraBrain1_Avatar::read(hsStream* S, plResManager* mgr) {
    plCameraBrain1::read(S, mgr);
    fOffset.read(S);

    fFlags[kCutPOA] = true;
}

void plCameraBrain1_Avatar::write(hsStream* S, plResManager* mgr) {
    plCameraBrain1::write(S, mgr);
    fOffset.write(S);
}

void plCameraBrain1_Avatar::IPrcWrite(pfPrcHelper* prc) {
    plCameraBrain1::IPrcWrite(prc);

    prc->writeSimpleTag("Offset");
    fOffset.prcWrite(prc);
    prc->closeTag();
}


/* plCameraBrain1_FirstPerson */
plCameraBrain1_FirstPerson::plCameraBrain1_FirstPerson() { }
plCameraBrain1_FirstPerson::~plCameraBrain1_FirstPerson() { }

IMPLEMENT_CREATABLE(plCameraBrain1_FirstPerson, kCameraBrain1_FirstPerson,
                    plCameraBrain1_Avatar)


/* plCameraBrain1_Fixed */
plCameraBrain1_Fixed::plCameraBrain1_Fixed() { }
plCameraBrain1_Fixed::~plCameraBrain1_Fixed() { }

IMPLEMENT_CREATABLE(plCameraBrain1_Fixed, kCameraBrain1_Fixed, plCameraBrain1)

void plCameraBrain1_Fixed::read(hsStream* S, plResManager* mgr) {
    plCameraBrain1::read(S, mgr);
    fTargetPoint = mgr->readKey(S);
}

void plCameraBrain1_Fixed::write(hsStream* S, plResManager* mgr) {
    plCameraBrain1::write(S, mgr);
    mgr->writeKey(S, fTargetPoint);
}

void plCameraBrain1_Fixed::IPrcWrite(pfPrcHelper* prc) {
    plCameraBrain1::IPrcWrite(prc);

    prc->writeSimpleTag("TargetPoint");
    fTargetPoint->prcWrite(prc);
    prc->closeTag();
}


/* plCameraBrain1_Circle */
plCameraBrain1_Circle::plCameraBrain1_Circle()
                     : fCircleFlags(0), fRadius(0), fCirPerSec(0) { }
plCameraBrain1_Circle::~plCameraBrain1_Circle() { }

IMPLEMENT_CREATABLE(plCameraBrain1_Circle, kCameraBrain1_Circle,
                    plCameraBrain1_Fixed)

void plCameraBrain1_Circle::read(hsStream* S, plResManager* mgr) {
    plCameraBrain1::read(S, mgr);
    
    fCircleFlags = S->readInt();
    fCenter.read(S);
    fRadius = S->readFloat();
    fCenterObject = mgr->readKey(S);
    fPOAObject = mgr->readKey(S);
    fCirPerSec = S->readFloat();
}

void plCameraBrain1_Circle::write(hsStream* S, plResManager* mgr) {
    plCameraBrain1::write(S, mgr);
    
    S->writeInt(fCircleFlags);
    fCenter.write(S);
    S->writeFloat(fRadius);
    mgr->writeKey(S, fCenterObject);
    mgr->writeKey(S, fPOAObject);
    S->writeFloat(fCirPerSec);
}

void plCameraBrain1_Circle::IPrcWrite(pfPrcHelper* prc) {
    plCameraBrain1::IPrcWrite(prc);

    prc->startTag("CircleParams");
    prc->writeParamHex("Flags", fCircleFlags);
    prc->writeParam("CirclesPerSec", fCirPerSec);
    prc->endTag(true);

    prc->startTag("Circle");
    prc->writeParam("radius", fRadius);
    prc->endTag();
    fCenter.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("CenterObject");
    fCenterObject->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("POAObject");
    fPOAObject->prcWrite(prc);
    prc->closeTag();
}
