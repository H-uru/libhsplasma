#include "plParticleSystem.h"

plParticleSystem::plParticleSystem()
                : fXTiles(0), fYTiles(0), fCurrTime(0.0), fLastTime(0.0),
                  fPreSim(0.0f), fDrag(0.0f), fWindMult(0.0f),
                  fMaxTotalParticles(0), fMaxTotalParticlesLeft(0),
                  fNumValidEmitters(0), fMaxEmitters(0), fNextEmitter(0),
                  fEmitters(NULL), fAmbientCtl(NULL), fDiffuseCtl(NULL),
                  fOpacityCtl(NULL), fWidthCtl(NULL), fHeightCtl(NULL) { }

plParticleSystem::~plParticleSystem() {
    if (fEmitters != NULL) {
        for (size_t i=0; i<fNumValidEmitters; i++)
            if (fEmitters[i] != NULL) delete fEmitters[i];
        delete[] fEmitters;
    }
    
    if (fAmbientCtl != NULL) delete fAmbientCtl;
    if (fDiffuseCtl != NULL) delete fDiffuseCtl;
    if (fOpacityCtl != NULL) delete fOpacityCtl;
    if (fWidthCtl != NULL) delete fWidthCtl;
    if (fHeightCtl != NULL) delete fHeightCtl;
}

IMPLEMENT_CREATABLE(plParticleSystem, kParticleSystem, plSynchedObject)

void plParticleSystem::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fMaterial = mgr->readKey(S);
    fAmbientCtl = plController::Convert(mgr->ReadCreatable(S));
    fDiffuseCtl = plController::Convert(mgr->ReadCreatable(S));
    fOpacityCtl = plController::Convert(mgr->ReadCreatable(S));
    fWidthCtl = plController::Convert(mgr->ReadCreatable(S));
    fHeightCtl = plController::Convert(mgr->ReadCreatable(S));

    fXTiles = S->readInt();
    fYTiles = S->readInt();
    fMaxTotalParticles = S->readInt();
    fMaxEmitters = S->readInt();
    fPreSim = S->readFloat();
    fAccel.read(S);
    fDrag = S->readFloat();
    fWindMult = S->readFloat();
    fNumValidEmitters = S->readInt();

    if (fNumValidEmitters > fMaxEmitters)
        throw hsBadParamException(__FILE__, __LINE__);
    fEmitters = new plParticleEmitter*[fMaxEmitters];
    for (size_t i=0; i<fNumValidEmitters; i++)
        fEmitters[i] = plParticleEmitter::Convert(mgr->ReadCreatable(S));
    for (size_t i=fNumValidEmitters; i<fMaxEmitters; i++)
        fEmitters[i] = NULL;

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
