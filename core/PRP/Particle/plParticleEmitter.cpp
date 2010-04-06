#include "plParticleEmitter.h"

plParticleEmitter::plParticleEmitter()
                 : fMiscFlags(0), fSpanIndex(0), fMaxParticles(0),
                   fGenerator(NULL) { }

plParticleEmitter::~plParticleEmitter() {
    delete fGenerator;
}

void plParticleEmitter::read(hsStream* S, plResManager* mgr) {
    setGenerator(plParticleGenerator::Convert(mgr->ReadCreatable(S)));

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

void plParticleEmitter::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Generator") {
        if (tag->hasChildren())
            setGenerator(plParticleGenerator::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "EmitterParams") {
        fSpanIndex = tag->getParam("SpanIndex", "0").toUint();
        fMaxParticles = tag->getParam("MaxParticles", "0").toUint();
        fMiscFlags = tag->getParam("MiscFlags", "0").toUint();
    } else if (tag->getName() == "Color") {
        if (tag->hasChildren())
            fColor.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plParticleEmitter::setGenerator(plParticleGenerator* generator) {
    delete fGenerator;
    fGenerator = generator;
}
