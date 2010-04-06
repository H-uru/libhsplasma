#include "plParticleSystem.h"

plParticleSystem::plParticleSystem()
                : fXTiles(0), fYTiles(0), fPreSim(0.0f), fDrag(0.0f),
                  fWindMult(0.0f), fMaxTotalParticles(0),
                  fNumValidEmitters(0), fMaxEmitters(0),
                  fAmbientCtl(NULL), fDiffuseCtl(NULL), fOpacityCtl(NULL),
                  fWidthCtl(NULL), fHeightCtl(NULL) { }

plParticleSystem::~plParticleSystem() {
    for (size_t i=0; i<fEmitters.getSize(); i++)
        delete fEmitters[i];
    delete fAmbientCtl;
    delete fDiffuseCtl;
    delete fOpacityCtl;
    delete fWidthCtl;
    delete fHeightCtl;
}

void plParticleSystem::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fMaterial = mgr->readKey(S);
    setAmbientCtl(plController::Convert(mgr->ReadCreatable(S)));
    setDiffuseCtl(plController::Convert(mgr->ReadCreatable(S)));
    setOpacityCtl(plController::Convert(mgr->ReadCreatable(S)));
    setWidthCtl(plController::Convert(mgr->ReadCreatable(S)));
    setHeightCtl(plController::Convert(mgr->ReadCreatable(S)));

    fXTiles = S->readInt();
    fYTiles = S->readInt();
    fMaxTotalParticles = S->readInt();
    fMaxEmitters = S->readInt();
    fPreSim = S->readFloat();
    fAccel.read(S);
    fDrag = S->readFloat();
    fWindMult = S->readFloat();
    fNumValidEmitters = S->readInt();

    for (size_t i=0; i<fEmitters.getSize(); i++)
        delete fEmitters[i];
    fEmitters.setSizeNull(fMaxEmitters);
    if (fNumValidEmitters > fMaxEmitters)
        throw hsBadParamException(__FILE__, __LINE__);
    for (size_t i=0; i<fNumValidEmitters; i++)
        fEmitters[i] = plParticleEmitter::Convert(mgr->ReadCreatable(S));

    fForces.setSize(S->readInt());
    for (size_t i=0; i<fForces.getSize(); i++)
        fForces[i] = mgr->readKey(S);
    fEffects.setSize(S->readInt());
    for (size_t i=0; i<fEffects.getSize(); i++)
        fEffects[i] = mgr->readKey(S);
    fConstraints.setSize(S->readInt());
    for (size_t i=0; i<fConstraints.getSize(); i++)
        fConstraints[i] = mgr->readKey(S);

    fPermaLights.setSize(S->readInt());
    for (size_t i=0; i<fPermaLights.getSize(); i++)
        fPermaLights[i] = mgr->readKey(S);
}

void plParticleSystem::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fMaterial);
    mgr->WriteCreatable(S, fAmbientCtl);
    mgr->WriteCreatable(S, fDiffuseCtl);
    mgr->WriteCreatable(S, fOpacityCtl);
    mgr->WriteCreatable(S, fWidthCtl);
    mgr->WriteCreatable(S, fHeightCtl);

    S->writeInt(fXTiles);
    S->writeInt(fYTiles);
    S->writeInt(fMaxTotalParticles);
    S->writeInt(fMaxEmitters);
    S->writeFloat(fPreSim);
    fAccel.write(S);
    S->writeFloat(fDrag);
    S->writeFloat(fWindMult);
    S->writeInt(fNumValidEmitters);
    for (size_t i=0; i<fNumValidEmitters; i++)
        mgr->WriteCreatable(S, fEmitters[i]);

    S->writeInt(fForces.getSize());
    for (size_t i=0; i<fForces.getSize(); i++)
        mgr->writeKey(S, fForces[i]);
    S->writeInt(fEffects.getSize());
    for (size_t i=0; i<fEffects.getSize(); i++)
        mgr->writeKey(S, fEffects[i]);
    S->writeInt(fConstraints.getSize());
    for (size_t i=0; i<fConstraints.getSize(); i++)
        mgr->writeKey(S, fConstraints[i]);

    S->writeInt(fPermaLights.getSize());
    for (size_t i=0; i<fPermaLights.getSize(); i++)
        mgr->writeKey(S, fPermaLights[i]);
}

void plParticleSystem::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Material");
    fMaterial->prcWrite(prc);
    prc->closeTag();

    if (fAmbientCtl != NULL) {
        prc->writeSimpleTag("AmbientCtl");
        fAmbientCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("AmbientCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fDiffuseCtl != NULL) {
        prc->writeSimpleTag("DiffuseCtl");
        fDiffuseCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("DiffuseCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fOpacityCtl != NULL) {
        prc->writeSimpleTag("OpacityCtl");
        fOpacityCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("OpacityCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fWidthCtl != NULL) {
        prc->writeSimpleTag("WidthCtl");
        fWidthCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("WidthCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fHeightCtl != NULL) {
        prc->writeSimpleTag("HeightCtl");
        fHeightCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("HeightCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->startTag("ParticleParams");
    prc->writeParam("XTiles", fXTiles);
    prc->writeParam("YTiles", fYTiles);
    prc->writeParam("MaxTotalParticles", fMaxTotalParticles);
    prc->writeParam("MaxEmitters", fMaxEmitters);
    prc->writeParam("PreSim", fPreSim);
    prc->writeParam("Drag", fDrag);
    prc->writeParam("WindMult", fWindMult);
    prc->endTag(true);

    prc->writeSimpleTag("Accel");
    fAccel.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Emitters");
    for (size_t i=0; i<fNumValidEmitters; i++)
        fEmitters[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Forces");
    for (size_t i=0; i<fForces.getSize(); i++)
        fForces[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Effects");
    for (size_t i=0; i<fEffects.getSize(); i++)
        fEffects[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Constraints");
    for (size_t i=0; i<fConstraints.getSize(); i++)
        fConstraints[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("PermaLights");
    for (size_t i=0; i<fPermaLights.getSize(); i++)
        fPermaLights[i]->prcWrite(prc);
    prc->closeTag();
}

void plParticleSystem::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "AmbientCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").toBool())
            setAmbientCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "DiffuseCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").toBool())
            setDiffuseCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "OpacityCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").toBool())
            setOpacityCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "WidthCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").toBool())
            setWidthCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "HeightCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").toBool())
            setHeightCtl(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "ParticleParams") {
        fXTiles = tag->getParam("XTiles", "0").toUint();
        fYTiles = tag->getParam("YTiles", "0").toUint();
        fMaxTotalParticles = tag->getParam("MaxTotalParticles", "0").toUint();
        fMaxEmitters = tag->getParam("MaxEmitters", "0").toUint();
        fPreSim = tag->getParam("PreSim", "0").toFloat();
        fDrag = tag->getParam("Drag", "0").toFloat();
        fWindMult = tag->getParam("WindMult", "0").toFloat();
    } else if (tag->getName() == "Accel") {
        if (tag->hasChildren())
            fAccel.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Emitters") {
        for (size_t i=0; i<fEmitters.getSize(); i++)
            delete fEmitters[i];
        fEmitters.setSizeNull(fMaxEmitters);
        fNumValidEmitters = tag->countChildren();
        if (fNumValidEmitters > fMaxEmitters)
            throw pfPrcParseException(__FILE__, __LINE__, "Too many particle emitters");
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumValidEmitters; i++) {
            fEmitters[i] = plParticleEmitter::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Forces") {
        fForces.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fForces.getSize(); i++) {
            fForces[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Effects") {
        fEffects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEffects.getSize(); i++) {
            fEffects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Constraints") {
        fConstraints.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fConstraints.getSize(); i++) {
            fConstraints[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PermaLights") {
        fPermaLights.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPermaLights.getSize(); i++) {
            fPermaLights[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

void plParticleSystem::setAmbientCtl(plController* ctl) {
    delete fAmbientCtl;
    fAmbientCtl = ctl;
}

void plParticleSystem::setDiffuseCtl(plController* ctl) {
    delete fDiffuseCtl;
    fDiffuseCtl = ctl;
}

void plParticleSystem::setOpacityCtl(plController* ctl) {
    delete fOpacityCtl;
    fOpacityCtl = ctl;
}

void plParticleSystem::setWidthCtl(plController* ctl) {
    delete fWidthCtl;
    fWidthCtl = ctl;
}

void plParticleSystem::setHeightCtl(plController* ctl) {
    delete fHeightCtl;
    fHeightCtl = ctl;
}

void plParticleSystem::allocEmitters(unsigned int max) {
    for (size_t i=max; i<fMaxEmitters; i++)
        // When max < fMaxEmitters
        delete fEmitters[i];
    fEmitters.setSize(max);
    for (size_t i=fMaxEmitters; i<max; i++)
        // When fMaxEmitters < max
        fEmitters[i] = NULL;
    fMaxEmitters = max;
    if (fNumValidEmitters > fMaxEmitters)
        fNumValidEmitters = fMaxEmitters;
}

void plParticleSystem::setEmitter(size_t idx, plParticleEmitter* emitter) {
    delete fEmitters[idx];
    fEmitters[idx] = emitter;
}

void plParticleSystem::addEmitter(plParticleEmitter* emitter) {
    fNumValidEmitters++;
    if (fNumValidEmitters > fMaxEmitters) {
        fMaxEmitters = fNumValidEmitters;
        fEmitters.setSize(fMaxEmitters);
    }
    fEmitters[fNumValidEmitters-1] = emitter;
}

void plParticleSystem::delEmitter(size_t idx) {
    delete fEmitters[idx];
    for (size_t i=idx; i<fMaxEmitters-1; i++)
        fEmitters[i] = fEmitters[i+1];
    fEmitters[fMaxEmitters-1] = NULL;
    fNumValidEmitters--;
}

void plParticleSystem::clearEmitters() {
    for (size_t i=0; i<fEmitters.getSize(); i++)
        delete fEmitters[i];
    fEmitters.clear();
    fNumValidEmitters = 0;
    fMaxEmitters = 0;
}
