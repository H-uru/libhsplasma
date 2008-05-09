#include "plParticleEffect.h"

/* plParticleEffect */
plParticleEffect::plParticleEffect() { }
plParticleEffect::~plParticleEffect() { }

IMPLEMENT_CREATABLE(plParticleEffect, kParticleEffect, hsKeyedObject)


/* plParticleCollisionEffect */
plParticleCollisionEffect::plParticleCollisionEffect() { }
plParticleCollisionEffect::~plParticleCollisionEffect() { }

IMPLEMENT_CREATABLE(plParticleCollisionEffect, kParticleCollisionEffect,
                    plParticleEffect)

void plParticleCollisionEffect::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fSceneObj = mgr->readKey(S);
}

void plParticleCollisionEffect::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    mgr->writeKey(S, fSceneObj);
}

void plParticleCollisionEffect::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    prc->writeSimpleTag("SceneObject");
    fSceneObj->prcWrite(prc);
    prc->closeTag();
}

void plParticleCollisionEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SceneObject") {
        if (tag->hasChildren())
            fSceneObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleCollisionEffectBeat */
plParticleCollisionEffectBeat::plParticleCollisionEffectBeat() { }
plParticleCollisionEffectBeat::~plParticleCollisionEffectBeat() { }

IMPLEMENT_CREATABLE(plParticleCollisionEffectBeat, kParticleCollisionEffectBeat,
                    plParticleCollisionEffect)


/* plParticleCollisionEffectBounce */
plParticleCollisionEffectBounce::plParticleCollisionEffectBounce()
                               : fBounce(0.0f), fFriction(0.0f) { }

plParticleCollisionEffectBounce::~plParticleCollisionEffectBounce() { }

IMPLEMENT_CREATABLE(plParticleCollisionEffectBounce,
                    kParticleCollisionEffectBounce,
                    plParticleCollisionEffect)

void plParticleCollisionEffectBounce::read(hsStream* S, plResManager* mgr) {
    plParticleCollisionEffect::read(S, mgr);
    fBounce = S->readFloat();
    fFriction = S->readFloat();
}

void plParticleCollisionEffectBounce::write(hsStream* S, plResManager* mgr) {
    plParticleCollisionEffect::write(S, mgr);
    S->writeFloat(fBounce);
    S->writeFloat(fFriction);
}

void plParticleCollisionEffectBounce::IPrcWrite(pfPrcHelper* prc) {
    plParticleCollisionEffect::IPrcWrite(prc);
    prc->startTag("BounceParams");
    prc->writeParam("Bounce", fBounce);
    prc->writeParam("Friction", fFriction);
    prc->endTag(true);
}

void plParticleCollisionEffectBounce::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BounceParams") {
        fBounce = tag->getParam("Bounce", "0").toFloat();
        fFriction = tag->getParam("Friction", "0").toFloat();
    } else {
        plParticleCollisionEffect::IPrcParse(tag, mgr);
    }
}


/* plParticleCollisionEffectDie */
plParticleCollisionEffectDie::plParticleCollisionEffectDie() { }
plParticleCollisionEffectDie::~plParticleCollisionEffectDie() { }

IMPLEMENT_CREATABLE(plParticleCollisionEffectDie, kParticleCollisionEffectDie,
                    plParticleCollisionEffect)


/* plParticleFadeOutEffect */
plParticleFadeOutEffect::plParticleFadeOutEffect()
                       : fLength(0.0f), fIgnoreZ(0.0f) { }

plParticleFadeOutEffect::~plParticleFadeOutEffect() { }

IMPLEMENT_CREATABLE(plParticleFadeOutEffect, kParticleFadeOutEffect,
                    plParticleEffect)

void plParticleFadeOutEffect::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fLength = S->readFloat();
    fIgnoreZ = S->readFloat();
}

void plParticleFadeOutEffect::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeFloat(fLength);
    S->writeFloat(fIgnoreZ);
}

void plParticleFadeOutEffect::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("FadeParams");
    prc->writeParam("Length", fLength);
    prc->writeParam("IgnoreZ", fIgnoreZ);
    prc->endTag(true);
}

void plParticleFadeOutEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FadeParams") {
        fLength = tag->getParam("Length", "0").toFloat();
        fIgnoreZ = tag->getParam("IgnoreZ", "0").toFloat();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleFadeVolumeEffect */
plParticleFadeVolumeEffect::plParticleFadeVolumeEffect()
                       : fLength(0.0f), fIgnoreZ(0.0f) { }

plParticleFadeVolumeEffect::~plParticleFadeVolumeEffect() { }

IMPLEMENT_CREATABLE(plParticleFadeVolumeEffect, kParticleFadeVolumeEffect,
                    plParticleEffect)

void plParticleFadeVolumeEffect::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fLength = S->readFloat();
    fIgnoreZ = S->readBool() ? 1.0f : 0.0f;
}

void plParticleFadeVolumeEffect::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeFloat(fLength);
    S->writeBool(fIgnoreZ != 0.0f);
}

void plParticleFadeVolumeEffect::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("FadeParams");
    prc->writeParam("Length", fLength);
    prc->writeParam("IgnoreZ", fIgnoreZ);
    prc->endTag(true);
}

void plParticleFadeVolumeEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FadeParams") {
        fLength = tag->getParam("Length", "0").toFloat();
        fIgnoreZ = tag->getParam("IgnoreZ", "0").toFloat();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleFlockEffect */
plParticleFlockEffect::plParticleFlockEffect()
                     : fInfAvgRadSq(0.0f), fInfRepRadSq(0.0f), fAvgVelStr(0.0f),
                       fRepDirStr(0.0f), fGoalOrbitStr(0.0f),
                       fGoalChaseStr(0.0f), fGoalDistSq(0.0f),
                       fFullChaseDistSq(0.0f), fMaxOrbitSpeed(0.0f),
                       fMaxChaseSpeed(0.0f), fMaxParticles(0), fDistSq(0.0f) { }

plParticleFlockEffect::~plParticleFlockEffect() { }

IMPLEMENT_CREATABLE(plParticleFlockEffect, kParticleFlockEffect,
                    plParticleEffect)

void plParticleFlockEffect::read(hsStream* S, plResManager* mgr) {
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

void plParticleFlockEffect::write(hsStream* S, plResManager* mgr) {
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

void plParticleFlockEffect::IPrcWrite(pfPrcHelper* prc) {
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

void plParticleFlockEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "TargetOffset") {
        if (tag->hasChildren())
            fTargetOffset.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DissenterTarget") {
        if (tag->hasChildren())
            fDissenterTarget.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FlockParams") {
        fInfAvgRadSq = tag->getParam("InfAvgRadSq", "0").toFloat();
        fInfRepRadSq = tag->getParam("InfRepRadSq", "0").toFloat();
        fGoalDistSq = tag->getParam("GoalDistSq", "0").toFloat();
        fFullChaseDistSq = tag->getParam("FullChaseDistSq", "0").toFloat();
        fAvgVelStr = tag->getParam("AvgVelStr", "0").toFloat();
        fRepDirStr = tag->getParam("RepDirStr", "0").toFloat();
        fGoalOrbitStr = tag->getParam("GoalOrbitStr", "0").toFloat();
        fGoalChaseStr = tag->getParam("GoalChaseStr", "0").toFloat();
        fMaxOrbitSpeed = tag->getParam("MaxOrbitSpeed", "0").toFloat();
        fMaxChaseSpeed = tag->getParam("MaxChaseSpeed", "0").toFloat();
        fMaxParticles = tag->getParam("MaxParticles", "0").toFloat();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}


/* plParticleFollowSystemEffect */
plParticleFollowSystemEffect::plParticleFollowSystemEffect() { }
plParticleFollowSystemEffect::~plParticleFollowSystemEffect() { }

IMPLEMENT_CREATABLE(plParticleFollowSystemEffect, kParticleFollowSystemEffect,
                    plParticleEffect)


/* plParticleWindEffect */
plParticleWindEffect::plParticleWindEffect()
                    : fStrength(0.0f), fConstancy(0.0f), fSwirl(0.0f),
                      fHorizontal(false), fLastDirSecs(0.0) { }

plParticleWindEffect::~plParticleWindEffect() { }

IMPLEMENT_CREATABLE(plParticleWindEffect, kParticleWindEffect, plParticleEffect)

void plParticleWindEffect::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fStrength = S->readFloat();
    fConstancy = S->readFloat();
    fSwirl = S->readFloat();
    fHorizontal = S->readBool();

    fRefDir.read(S);
    fDir.read(S);
    fRandDir = fDir;
}

void plParticleWindEffect::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeFloat(fStrength);
    S->writeFloat(fConstancy);
    S->writeFloat(fSwirl);
    S->writeBool(fHorizontal);

    fRefDir.write(S);
    fDir.write(S);
}

void plParticleWindEffect::IPrcWrite(pfPrcHelper* prc) {
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

void plParticleWindEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WindParams") {
        fStrength = tag->getParam("Strength", "0").toFloat();
        fConstancy = tag->getParam("Constancy", "0").toFloat();
        fSwirl = tag->getParam("Swirl", "0").toFloat();
        fHorizontal = tag->getParam("Horizontal", "false").toBool();
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
plParticleLocalWind::plParticleLocalWind()
                   : fSpeed(0.0f), fLastPhaseSecs(0.0) { }

plParticleLocalWind::~plParticleLocalWind() { }

IMPLEMENT_CREATABLE(plParticleLocalWind, kParticleLocalWind,
                    plParticleWindEffect)

void plParticleLocalWind::read(hsStream* S, plResManager* mgr) {
    plParticleWindEffect::read(S, mgr);
    fScale.read(S);
    fSpeed = S->readFloat();
}

void plParticleLocalWind::write(hsStream* S, plResManager* mgr) {
    plParticleWindEffect::write(S, mgr);
    fScale.write(S);
    S->writeFloat(fSpeed);
}

void plParticleLocalWind::IPrcWrite(pfPrcHelper* prc) {
    plParticleWindEffect::IPrcWrite(prc);

    prc->writeSimpleTag("Scale");
    fScale.prcWrite(prc);
    prc->closeTag();

    prc->startTag("LocalWindParams");
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plParticleLocalWind::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LocalWindParams") {
        fSpeed = tag->getParam("Speed", "0").toFloat();
    } else if (tag->getName() == "Scale") {
        if (tag->hasChildren())
            fScale.prcParse(tag->getFirstChild());
    } else {
        plParticleWindEffect::IPrcParse(tag, mgr);
    }
}


/* plParticleUniformWind */
plParticleUniformWind::plParticleUniformWind()
                     : fFreqMin(0.0f), fFreqMax(0.0f), fFreqCurr(0.0f),
                       fFreqRate(0.0f), fCurrPhase(0.0), fLastFreqSecs(0.0),
                       fCurrentStrength(0.0f) { }

plParticleUniformWind::~plParticleUniformWind() { }

IMPLEMENT_CREATABLE(plParticleUniformWind, kParticleUniformWind,
                    plParticleWindEffect)

void plParticleUniformWind::read(hsStream* S, plResManager* mgr) {
    plParticleWindEffect::read(S, mgr);

    fFreqMin = S->readFloat();
    fFreqMax = S->readFloat();
    fFreqRate = S->readFloat();
    fFreqCurr = fFreqMin;
}

void plParticleUniformWind::write(hsStream* S, plResManager* mgr) {
    plParticleWindEffect::write(S, mgr);

    S->writeFloat(fFreqMin);
    S->writeFloat(fFreqMax);
    S->writeFloat(fFreqRate);
}

void plParticleUniformWind::IPrcWrite(pfPrcHelper* prc) {
    plParticleWindEffect::IPrcWrite(prc);

    prc->startTag("UniformWindParams");
    prc->writeParam("FreqMin", fFreqMin);
    prc->writeParam("FreqMax", fFreqMax);
    prc->writeParam("FreqRate", fFreqRate);
    prc->endTag(true);
}

void plParticleUniformWind::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "UniformWindParams") {
        fFreqMin = tag->getParam("FreqMin", "0").toFloat();
        fFreqMax = tag->getParam("FreqMax", "0").toFloat();
        fFreqRate = tag->getParam("FreqRate", "0").toFloat();
    } else {
        plParticleWindEffect::IPrcParse(tag, mgr);
    }
}
