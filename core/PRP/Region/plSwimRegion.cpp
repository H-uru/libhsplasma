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

#include "plSwimRegion.h"

/* plSwimRegionInterface */
void plSwimRegionInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fDownBuoyancy = S->readFloat();
    fUpBuoyancy = S->readFloat();
    fMaxUpwardVel = S->readFloat();
}

void plSwimRegionInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    S->writeFloat(fDownBuoyancy);
    S->writeFloat(fUpBuoyancy);
    S->writeFloat(fMaxUpwardVel);
}

void plSwimRegionInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->startTag("SwimRegionParams");
    prc->writeParam("DownBuoyancy", fDownBuoyancy);
    prc->writeParam("UpBuoyancy", fUpBuoyancy);
    prc->writeParam("MaxUpwardVel", fMaxUpwardVel);
    prc->endTag(true);
}

void plSwimRegionInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SwimRegionParams") {
        fDownBuoyancy = tag->getParam("DownBuoyancy", "0").toFloat();
        fUpBuoyancy = tag->getParam("UpBuoyancy", "0").toFloat();
        fMaxUpwardVel = tag->getParam("MaxUpwardVel", "0").toFloat();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}


/* plSwimCircularCurrentRegion */
void plSwimCircularCurrentRegion::read(hsStream* S, plResManager* mgr) {
    plSwimRegionInterface::read(S, mgr);

    fRotation = S->readFloat();
    fPullNearDistSq = S->readFloat();
    fPullNearVel = S->readFloat();
    fPullFarDistSq = S->readFloat();
    fPullFarVel = S->readFloat();
    fCurrentObj = mgr->readKey(S);
}

void plSwimCircularCurrentRegion::write(hsStream* S, plResManager* mgr) {
    plSwimRegionInterface::write(S, mgr);

    S->writeFloat(fRotation);
    S->writeFloat(fPullNearDistSq);
    S->writeFloat(fPullNearVel);
    S->writeFloat(fPullFarDistSq);
    S->writeFloat(fPullFarVel);
    mgr->writeKey(S, fCurrentObj);
}

void plSwimCircularCurrentRegion::IPrcWrite(pfPrcHelper* prc) {
    plSwimRegionInterface::IPrcWrite(prc);

    prc->startTag("CircularCurrent");
    prc->writeParam("Rotation", fRotation);
    prc->writeParam("PullNearDistSq", fPullNearDistSq);
    prc->writeParam("PullFarDistSq", fPullFarDistSq);
    prc->writeParam("PullNearVel", fPullNearVel);
    prc->writeParam("PullFarVel", fPullFarVel);
    prc->endTag(true);

    prc->writeSimpleTag("Current");
    fCurrentObj->prcWrite(prc);
    prc->closeTag();
}

void plSwimCircularCurrentRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CircularCurrent") {
        fRotation = tag->getParam("Rotation", "0").toFloat();
        fPullNearDistSq = tag->getParam("PullNearDistSq", "0").toFloat();
        fPullFarDistSq = tag->getParam("PullFarDistSq", "0").toFloat();
        fPullNearVel = tag->getParam("PullNearVel", "0").toFloat();
        fPullFarVel = tag->getParam("PullFarVel", "0").toFloat();
    } else if (tag->getName() == "Current") {
        if (tag->hasChildren())
            fCurrentObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSwimRegionInterface::IPrcParse(tag, mgr);
    }
}


/* plSwimStraightCurrentRegion */
void plSwimStraightCurrentRegion::read(hsStream* S, plResManager* mgr) {
    plSwimRegionInterface::read(S, mgr);

    fNearDist = S->readFloat();
    fNearVel = S->readFloat();
    fFarDist = S->readFloat();
    fFarVel = S->readFloat();
    fCurrentObj = mgr->readKey(S);
}

void plSwimStraightCurrentRegion::write(hsStream* S, plResManager* mgr) {
    plSwimRegionInterface::write(S, mgr);

    S->writeFloat(fNearDist);
    S->writeFloat(fNearVel);
    S->writeFloat(fFarDist);
    S->writeFloat(fFarVel);
    mgr->writeKey(S, fCurrentObj);
}

void plSwimStraightCurrentRegion::IPrcWrite(pfPrcHelper* prc) {
    plSwimRegionInterface::IPrcWrite(prc);

    prc->startTag("StraightCurrent");
    prc->writeParam("NearDist", fNearDist);
    prc->writeParam("FarDist", fFarDist);
    prc->writeParam("NearVel", fNearVel);
    prc->writeParam("FarVel", fFarVel);
    prc->endTag(true);

    prc->writeSimpleTag("Current");
    fCurrentObj->prcWrite(prc);
    prc->closeTag();
}

void plSwimStraightCurrentRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "StraightCurrent") {
        fNearDist = tag->getParam("NearDist", "0").toFloat();
        fFarDist = tag->getParam("FarDist", "0").toFloat();
        fNearVel = tag->getParam("NearVel", "0").toFloat();
        fFarVel = tag->getParam("FarVel", "0").toFloat();
    } else if (tag->getName() == "Current") {
        if (tag->hasChildren())
            fCurrentObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSwimRegionInterface::IPrcParse(tag, mgr);
    }
}
