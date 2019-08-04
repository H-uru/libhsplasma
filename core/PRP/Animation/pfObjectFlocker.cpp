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

#include "pfObjectFlocker.h"

/* pfObjectFlocker */
void pfObjectFlocker::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    S->readByte();
    fNumBoids = S->readByte();
    fBoidKey = mgr->readKey(S);

    fFlock.fGoalWeight = S->readFloat();
    fFlock.fRandomWeight = S->readFloat();
    fFlock.fSeparationWeight = S->readFloat();
    fFlock.fSeparationRadius = S->readFloat();
    fFlock.fCohesionWeight = S->readFloat();
    fFlock.fCohesionRadius = S->readFloat();
    fFlock.fMaxForce = S->readFloat();
    fFlock.fMaxSpeed = S->readFloat();
    fFlock.fMinSpeed = S->readFloat();

    fUseTargetRotation = S->readBool();
    fRandomizeAnimationStart = S->readBool();
}

void pfObjectFlocker::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeByte(1);
    S->writeByte(fNumBoids);
    mgr->writeKey(S, fBoidKey);

    S->writeFloat(fFlock.fGoalWeight);
    S->writeFloat(fFlock.fRandomWeight);
    S->writeFloat(fFlock.fSeparationWeight);
    S->writeFloat(fFlock.fSeparationRadius);
    S->writeFloat(fFlock.fCohesionWeight);
    S->writeFloat(fFlock.fCohesionRadius);
    S->writeFloat(fFlock.fMaxForce);
    S->writeFloat(fFlock.fMaxSpeed);
    S->writeFloat(fFlock.fMinSpeed);

    S->writeBool(fUseTargetRotation);
    S->writeBool(fRandomizeAnimationStart);
}

void pfObjectFlocker::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("FlockParams");
    prc->writeParam("NumBoids", fNumBoids);
    prc->writeParam("UseTargetRotation", fUseTargetRotation);
    prc->writeParam("RandomizeAnimationStart", fRandomizeAnimationStart);
    prc->endTag(true);

    prc->writeSimpleTag("Boid");
    plResManager::PrcWriteKey(prc, fBoidKey);
    prc->closeTag();

    prc->startTag("Flock");
    prc->writeParam("GoalWeight", fFlock.fGoalWeight);
    prc->writeParam("RandomWeight", fFlock.fRandomWeight);
    prc->writeParam("SeparationWeight", fFlock.fSeparationWeight);
    prc->writeParam("SeparationRadius", fFlock.fSeparationRadius);
    prc->writeParam("CohesionWeight", fFlock.fCohesionWeight);
    prc->writeParam("CohesionRadius", fFlock.fCohesionRadius);
    prc->writeParam("MaxForce", fFlock.fMaxForce);
    prc->writeParam("MaxSpeed", fFlock.fMaxSpeed);
    prc->writeParam("MinSpeed", fFlock.fMinSpeed);
    prc->endTag(true);
}

void pfObjectFlocker::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FlockParams") {
        fNumBoids = tag->getParam("NumBoids", "0").to_uint();
        fUseTargetRotation = tag->getParam("UseTargetRotation", "false").to_bool();
        fRandomizeAnimationStart = tag->getParam("RandomizeAnimationStart", "false").to_bool();
    } else if (tag->getName() == "Boid") {
        if (tag->hasChildren())
            fBoidKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Flock") {
        fFlock.fGoalWeight = tag->getParam("GoalWeight", "0").to_float();
        fFlock.fRandomWeight = tag->getParam("RandomWeight", "0").to_float();
        fFlock.fSeparationWeight = tag->getParam("SeparationWeight", "0").to_float();
        fFlock.fSeparationRadius = tag->getParam("SeparationRadius", "0").to_float();
        fFlock.fCohesionWeight = tag->getParam("CohesionWeight", "0").to_float();
        fFlock.fCohesionRadius = tag->getParam("CohesionRadius", "0").to_float();
        fFlock.fMaxForce = tag->getParam("MaxForce", "0").to_float();
        fFlock.fMaxSpeed = tag->getParam("MaxSpeed", "0").to_float();
        fFlock.fMinSpeed = tag->getParam("MinSpeed", "0").to_float();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
