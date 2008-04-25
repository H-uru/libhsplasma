#include "plParticleEmitter.h"

plParticleEmitter::plParticleEmitter()
                 : fMiscFlags(0), fGenerator(NULL), fSpanIndex(0),
                   fNumValidParticles(0), fMaxParticles(0), fTimeToLive(0.0f) { }

plParticleEmitter::~plParticleEmitter() {
    if (fGenerator != NULL)
        delete fGenerator;
}

IMPLEMENT_CREATABLE(plParticleEmitter, kParticleEmitter, plCreatable)

void plParticleEmitter::read(hsStream* S, plResManager* mgr) {
    fGenerator = plParticleGenerator::Convert(mgr->ReadCreatable(S));

    fSpanIndex = S->readInt();
    fMaxParticles = S->readInt();
    fMiscFlags = S->readInt();
    fColor.read(S);
}

void plParticleEmitter::write(hsStream* S, plResManager* mgr) {
    mgr->WriteCreatable(S, fGenerator);

    S->writeInt(fSpanIndex);
    S->writeInt(fMaxParticles);
    S->writeInt(fMiscFlags);
    fColor.write(S);
}

void plParticleEmitter::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Generator");
    fGenerator->prcWrite(prc);
    prc->closeTag();
    
    prc->startTag("EmitterParams");
    prc->writeParam("SpanIndex", fSpanIndex);
    prc->writeParam("MaxParticles", fMaxParticles);
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);

    prc->writeSimpleTag("Color");
    fColor.prcWrite(prc);
    prc->closeTag();
}
