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

#include "plParticleEffect.h"

/* plParticleCollisionEffect */
void plParticleCollisionEffect::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);
    fSceneObj = mgr->readKey(S);
}

void plParticleCollisionEffect::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);
    mgr->writeKey(S, fSceneObj);
}

void plParticleCollisionEffect::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);
    prc->writeSimpleTag("SceneObject");
    plResManager::PrcWriteKey(prc, fSceneObj);
    prc->closeTag();
}

void plParticleCollisionEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SceneObject") {
        if (tag->hasChildren())
            fSceneObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleCollisionEffectBounce */
void plParticleCollisionEffectBounce::read(hsStream* S, plResManager* mgr)
{
    plParticleCollisionEffect::read(S, mgr);
    fBounce = S->readFloat();
    fFriction = S->readFloat();
}

void plParticleCollisionEffectBounce::write(hsStream* S, plResManager* mgr)
{
    plParticleCollisionEffect::write(S, mgr);
    S->writeFloat(fBounce);
    S->writeFloat(fFriction);
}

void plParticleCollisionEffectBounce::IPrcWrite(pfPrcHelper* prc)
{
    plParticleCollisionEffect::IPrcWrite(prc);
    prc->startTag("BounceParams");
    prc->writeParam("Bounce", fBounce);
    prc->writeParam("Friction", fFriction);
    prc->endTag(true);
}

void plParticleCollisionEffectBounce::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "BounceParams") {
        fBounce = tag->getParam("Bounce", "0").to_float();
        fFriction = tag->getParam("Friction", "0").to_float();
    } else {
        plParticleCollisionEffect::IPrcParse(tag, mgr);
    }
}


/* plParticleFadeOutEffect */
void plParticleFadeOutEffect::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);
    fLength = S->readFloat();
    fIgnoreZ = S->readFloat();
}

void plParticleFadeOutEffect::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);
    S->writeFloat(fLength);
    S->writeFloat(fIgnoreZ);
}

void plParticleFadeOutEffect::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("FadeParams");
    prc->writeParam("Length", fLength);
    prc->writeParam("IgnoreZ", fIgnoreZ);
    prc->endTag(true);
}

void plParticleFadeOutEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FadeParams") {
        fLength = tag->getParam("Length", "0").to_float();
        fIgnoreZ = tag->getParam("IgnoreZ", "0").to_float();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleFadeVolumeEffect */
void plParticleFadeVolumeEffect::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);
    fLength = S->readFloat();
    fIgnoreZ = S->readBool() ? 1.0f : 0.0f;
}

void plParticleFadeVolumeEffect::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);
    S->writeFloat(fLength);
    S->writeBool(fIgnoreZ != 0.0f);
}

void plParticleFadeVolumeEffect::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("FadeParams");
    prc->writeParam("Length", fLength);
    prc->writeParam("IgnoreZ", fIgnoreZ);
    prc->endTag(true);
}

void plParticleFadeVolumeEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FadeParams") {
        fLength = tag->getParam("Length", "0").to_float();
        fIgnoreZ = tag->getParam("IgnoreZ", "0").to_float();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleFlockEffect */
void plParticleFlockEffect::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fTargetOffset.read(S);
    fDissenterTarget.read(S);
    fInfAvgRadSq = S->readFloat();
    fInfRepRadSq = S->readFloat();
    fGoalDistSq = S->readFloat();
    fFullChaseDistSq = S->readFloat();
    fAvgVelStr = S->readFloat();
    fRepDirStr = S->readFloat();
    fGoalOrbitStr = S->readFloat();
    fGoalChaseStr = S->readFloat();
    fMaxOrbitSpeed = S->readFloat();
    fMaxChaseSpeed = S->readFloat();
    fMaxParticles = S->readFloat();
}

void plParticleFlockEffect::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    fTargetOffset.write(S);
    fDissenterTarget.write(S);
    S->writeFloat(fInfAvgRadSq);
    S->writeFloat(fInfRepRadSq);
    S->writeFloat(fGoalDistSq);
    S->writeFloat(fFullChaseDistSq);
    S->writeFloat(fAvgVelStr);
    S->writeFloat(fRepDirStr);
    S->writeFloat(fGoalOrbitStr);
    S->writeFloat(fGoalChaseStr);
    S->writeFloat(fMaxOrbitSpeed);
    S->writeFloat(fMaxChaseSpeed);
    S->writeFloat(fMaxParticles);
}

void plParticleFlockEffect::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("TargetOffset");
    fTargetOffset.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DissenterTarget");
    fDissenterTarget.prcWrite(prc);
    prc->closeTag();

    prc->startTag("FlockParams");
    prc->writeParam("InfAvgRadSq", fInfAvgRadSq);
    prc->writeParam("InfRepRadSq", fInfRepRadSq);
    prc->writeParam("GoalDistSq", fGoalDistSq);
    prc->writeParam("FullChaseDistSq", fFullChaseDistSq);
    prc->writeParam("AvgVelStr", fAvgVelStr);
    prc->writeParam("RepDirStr", fRepDirStr);
    prc->writeParam("GoalOrbitStr", fGoalOrbitStr);
    prc->writeParam("GoalChaseStr", fGoalChaseStr);
    prc->writeParam("MaxOrbitSpeed", fMaxOrbitSpeed);
    prc->writeParam("MaxChaseSpeed", fMaxChaseSpeed);
    prc->writeParam("MaxParticles", fMaxParticles);
    prc->endTag(true);
}

void plParticleFlockEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "TargetOffset") {
        if (tag->hasChildren())
            fTargetOffset.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DissenterTarget") {
        if (tag->hasChildren())
            fDissenterTarget.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FlockParams") {
        fInfAvgRadSq = tag->getParam("InfAvgRadSq", "0").to_float();
        fInfRepRadSq = tag->getParam("InfRepRadSq", "0").to_float();
        fGoalDistSq = tag->getParam("GoalDistSq", "0").to_float();
        fFullChaseDistSq = tag->getParam("FullChaseDistSq", "0").to_float();
        fAvgVelStr = tag->getParam("AvgVelStr", "0").to_float();
        fRepDirStr = tag->getParam("RepDirStr", "0").to_float();
        fGoalOrbitStr = tag->getParam("GoalOrbitStr", "0").to_float();
        fGoalChaseStr = tag->getParam("GoalChaseStr", "0").to_float();
        fMaxOrbitSpeed = tag->getParam("MaxOrbitSpeed", "0").to_float();
        fMaxChaseSpeed = tag->getParam("MaxChaseSpeed", "0").to_float();
        fMaxParticles = tag->getParam("MaxParticles", "0").to_float();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleWindEffect */
void plParticleWindEffect::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fStrength = S->readFloat();
    fConstancy = S->readFloat();
    fSwirl = S->readFloat();
    fHorizontal = S->readBool();

    fRefDir.read(S);
    fDir.read(S);
}

void plParticleWindEffect::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeFloat(fStrength);
    S->writeFloat(fConstancy);
    S->writeFloat(fSwirl);
    S->writeBool(fHorizontal);

    fRefDir.write(S);
    fDir.write(S);
}

void plParticleWindEffect::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("WindParams");
    prc->writeParam("Strength", fStrength);
    prc->writeParam("Constancy", fConstancy);
    prc->writeParam("Swirl", fSwirl);
    prc->writeParam("Horizontal", fHorizontal);
    prc->endTag(true);

    prc->writeSimpleTag("RefDir");
    fRefDir.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Dir");
    fDir.prcWrite(prc);
    prc->closeTag();
}

void plParticleWindEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WindParams") {
        fStrength = tag->getParam("Strength", "0").to_float();
        fConstancy = tag->getParam("Constancy", "0").to_float();
        fSwirl = tag->getParam("Swirl", "0").to_float();
        fHorizontal = tag->getParam("Horizontal", "false").to_bool();
    } else if (tag->getName() == "RefDir") {
        if (tag->hasChildren())
            fRefDir.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Dir") {
        if (tag->hasChildren())
            fDir.prcParse(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleLocalWind */
void plParticleLocalWind::read(hsStream* S, plResManager* mgr)
{
    plParticleWindEffect::read(S, mgr);
    fScale.read(S);
    fSpeed = S->readFloat();
}

void plParticleLocalWind::write(hsStream* S, plResManager* mgr)
{
    plParticleWindEffect::write(S, mgr);
    fScale.write(S);
    S->writeFloat(fSpeed);
}

void plParticleLocalWind::IPrcWrite(pfPrcHelper* prc)
{
    plParticleWindEffect::IPrcWrite(prc);

    prc->writeSimpleTag("Scale");
    fScale.prcWrite(prc);
    prc->closeTag();

    prc->startTag("LocalWindParams");
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plParticleLocalWind::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LocalWindParams") {
        fSpeed = tag->getParam("Speed", "0").to_float();
    } else if (tag->getName() == "Scale") {
        if (tag->hasChildren())
            fScale.prcParse(tag->getFirstChild());
    } else {
        plParticleWindEffect::IPrcParse(tag, mgr);
    }
}


/* plParticleUniformWind */
void plParticleUniformWind::read(hsStream* S, plResManager* mgr)
{
    plParticleWindEffect::read(S, mgr);

    fFreqMin = S->readFloat();
    fFreqMax = S->readFloat();
    fFreqRate = S->readFloat();
}

void plParticleUniformWind::write(hsStream* S, plResManager* mgr)
{
    plParticleWindEffect::write(S, mgr);

    S->writeFloat(fFreqMin);
    S->writeFloat(fFreqMax);
    S->writeFloat(fFreqRate);
}

void plParticleUniformWind::IPrcWrite(pfPrcHelper* prc)
{
    plParticleWindEffect::IPrcWrite(prc);

    prc->startTag("UniformWindParams");
    prc->writeParam("FreqMin", fFreqMin);
    prc->writeParam("FreqMax", fFreqMax);
    prc->writeParam("FreqRate", fFreqRate);
    prc->endTag(true);
}

void plParticleUniformWind::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "UniformWindParams") {
        fFreqMin = tag->getParam("FreqMin", "0").to_float();
        fFreqMax = tag->getParam("FreqMax", "0").to_float();
        fFreqRate = tag->getParam("FreqRate", "0").to_float();
    } else {
        plParticleWindEffect::IPrcParse(tag, mgr);
    }
}
