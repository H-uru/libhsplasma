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

#include "plCameraBrain.h"

/* plCameraBrain1 */
plCameraBrain1::plCameraBrain1()
    : fVelocity(30.0f), fAccel(30.0f), fDecel(30.0f), fPOAVelocity(30.0f),
      fPOAAccel(30.0f), fPOADecel(30.0f), fXPanLimit(), fZPanLimit(),
      fPanSpeed(0.5f), fZoomRate(), fZoomMax(), fZoomMin()
{
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

void plCameraBrain1::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fPOAOffset.read(S);
    fSubject = mgr->readKey(S);
    fRail = mgr->readKey(S);
    if (S->getVer().isNewPlasma()) {
        fEoaFlags.read(S);
    }
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

void plCameraBrain1::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    fPOAOffset.write(S);
    mgr->writeKey(S, fSubject);
    mgr->writeKey(S, fRail);
    if (S->getVer().isNewPlasma()) {
        fEoaFlags.write(S);
    }
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

void plCameraBrain1::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Subject");
    plResManager::PrcWriteKey(prc, fSubject);
    prc->closeTag();

    prc->writeSimpleTag("Rail");
    plResManager::PrcWriteKey(prc, fRail);
    prc->closeTag();

    prc->writeSimpleTag("Flags");
    fFlags.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("EoaFlags");
    fEoaFlags.prcWrite(prc);
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

void plCameraBrain1::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Subject") {
        if (tag->hasChildren())
            fSubject = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Rail") {
        if (tag->hasChildren())
            fRail = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Flags") {
        if (tag->hasChildren())
            fFlags.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "EoaFlags") {
        if (tag->hasChildren())
            fEoaFlags.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "CameraParams") {
        fAccel = tag->getParam("Accel", "0").to_float();
        fDecel = tag->getParam("Decel", "0").to_float();
        fVelocity = tag->getParam("Velocity", "0").to_float();
        fPOAAccel = tag->getParam("POAAccel", "0").to_float();
        fPOADecel = tag->getParam("POADecel", "0").to_float();
        fPOAVelocity = tag->getParam("POAVelocity", "0").to_float();
        fXPanLimit = tag->getParam("XPanLimit", "0").to_float();
        fZPanLimit = tag->getParam("ZPanLimit", "0").to_float();
        fZoomRate = tag->getParam("ZoomRate", "0").to_float();
        fZoomMin = tag->getParam("ZoomMin", "0").to_float();
        fZoomMax = tag->getParam("ZoomMax", "0").to_float();
    } else if (tag->getName() == "POAOffset") {
        if (tag->hasChildren())
            fPOAOffset.prcParse(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plCameraBrain1_Avatar */
void plCameraBrain1_Avatar::read(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::read(S, mgr);
    fOffset.read(S);

    /*fFlags[kCutPOA] = true;*/
}

void plCameraBrain1_Avatar::write(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::write(S, mgr);
    fOffset.write(S);
}

void plCameraBrain1_Avatar::IPrcWrite(pfPrcHelper* prc)
{
    plCameraBrain1::IPrcWrite(prc);

    prc->writeSimpleTag("Offset");
    fOffset.prcWrite(prc);
    prc->closeTag();
}

void plCameraBrain1_Avatar::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Offset") {
        if (tag->hasChildren())
            fOffset.prcParse(tag->getFirstChild());
    } else {
        plCameraBrain1::IPrcParse(tag, mgr);
    }
}


/* plCameraBrain1_Fixed */
void plCameraBrain1_Fixed::read(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::read(S, mgr);
    fTargetPoint = mgr->readKey(S);
}

void plCameraBrain1_Fixed::write(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::write(S, mgr);
    mgr->writeKey(S, fTargetPoint);
}

void plCameraBrain1_Fixed::IPrcWrite(pfPrcHelper* prc)
{
    plCameraBrain1::IPrcWrite(prc);

    prc->writeSimpleTag("TargetPoint");
    plResManager::PrcWriteKey(prc, fTargetPoint);
    prc->closeTag();
}

void plCameraBrain1_Fixed::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "TargetPoint") {
        if (tag->hasChildren())
            fTargetPoint = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plCameraBrain1::IPrcParse(tag, mgr);
    }
}


/* plCameraBrain1_Circle */
void plCameraBrain1_Circle::read(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::read(S, mgr);

    fCircleFlags = S->readInt();
    fCenter.read(S);
    fRadius = S->readFloat();
    fCenterObject = mgr->readKey(S);
    fPOAObject = mgr->readKey(S);
    fCirPerSec = S->readFloat();
}

void plCameraBrain1_Circle::write(hsStream* S, plResManager* mgr)
{
    plCameraBrain1::write(S, mgr);

    S->writeInt(fCircleFlags);
    fCenter.write(S);
    S->writeFloat(fRadius);
    mgr->writeKey(S, fCenterObject);
    mgr->writeKey(S, fPOAObject);
    S->writeFloat(fCirPerSec);
}

void plCameraBrain1_Circle::IPrcWrite(pfPrcHelper* prc)
{
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
    plResManager::PrcWriteKey(prc, fCenterObject);
    prc->closeTag();

    prc->writeSimpleTag("POAObject");
    plResManager::PrcWriteKey(prc, fPOAObject);
    prc->closeTag();
}

void plCameraBrain1_Circle::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CircleParams") {
        fCircleFlags = tag->getParam("Flags", "0").to_uint();
        fCirPerSec = tag->getParam("CirclesPerSec", "0").to_float();
    } else if (tag->getName() == "Circle") {
        fRadius = tag->getParam("radius", "0").to_float();
        if (tag->hasChildren())
            fCenter.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "CenterObject") {
        if (tag->hasChildren())
            fCenterObject = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "POAObject") {
        if (tag->hasChildren())
            fPOAObject = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plCameraBrain1::IPrcParse(tag, mgr);
    }
}
