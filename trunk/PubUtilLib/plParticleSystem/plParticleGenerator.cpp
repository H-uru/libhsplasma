#include "plParticleGenerator.h"

// plParticleGenerator //
plParticleGenerator::plParticleGenerator() { }
plParticleGenerator::~plParticleGenerator() { }

IMPLEMENT_CREATABLE(plParticleGenerator, kParticleGenerator, plCreatable)


// plOneTimeParticleGenerator //
plOneTimeParticleGenerator::plOneTimeParticleGenerator()
                          : fCount(0), fPosition(NULL), fDirection(NULL),
                            fXSize(0.0f), fYSize(0.0f), fScaleMin(0.0f),
                            fScaleMax(0.0f), fPartRadsPerSecRange(0.0f) { }

plOneTimeParticleGenerator::~plOneTimeParticleGenerator() {
    if (fPosition != NULL)
        delete[] fPosition;
    if (fDirection != NULL)
        delete[] fDirection;
}

IMPLEMENT_CREATABLE(plOneTimeParticleGenerator, kOneTimeParticleGenerator,
                    plParticleGenerator)

void plOneTimeParticleGenerator::read(hsStream* S, plResManager* mgr) {
    fCount = S->readInt();
    fXSize = S->readFloat();
    fYSize = S->readFloat();
    fScaleMin = S->readFloat();
    fScaleMax = S->readFloat();
    fPartRadsPerSecRange = S->readFloat();

    fPosition = new hsPoint3[fCount];
    fDirection = new hsVector3[fCount];
    for (size_t i=0; i<fCount; i++) {
        fPosition[i].read(S);
        fDirection[i].read(S);
    }
}

void plOneTimeParticleGenerator::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fCount);
    S->writeFloat(fXSize);
    S->writeFloat(fYSize);
    S->writeFloat(fScaleMin);
    S->writeFloat(fScaleMax);
    S->writeFloat(fPartRadsPerSecRange);

    for (size_t i=0; i<fCount; i++) {
        fPosition[i].write(S);
        fDirection[i].write(S);
    }
}

void plOneTimeParticleGenerator::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("GeneratorParams");
    prc->writeParam("XSize", fXSize);
    prc->writeParam("YSize", fYSize);
    prc->writeParam("ScaleMin", fScaleMin);
    prc->writeParam("ScaleMax", fScaleMax);
    prc->writeParam("RadsPerSecond", fPartRadsPerSecRange);
    prc->endTag(true);

    prc->writeSimpleTag("Sources");
    for (size_t i=0; i<fCount; i++) {
        prc->writeSimpleTag("Source");
        fPosition[i].prcWrite(prc);
        fDirection[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}


// plSimpleParticleGenerator //
plSimpleParticleGenerator::plSimpleParticleGenerator()
                         : fParticlesPerSecond(0.0f), fNumSources(0),
                           fInitPos(NULL), fInitPitch(NULL), fInitYaw(NULL),
                           fAngleRange(0.0f), fVelMin(0.0f), fVelMax(0.0f),
                           fXSize(0.0f), fYSize(0.0f), fScaleMin(0.0f),
                           fScaleMax(0.0f), fGenLife(0.0f), fPartLifeMin(0.0f),
                           fPartLifeMax(0.0f),fPartMassRange(0.0f),
                           fPartRadsPerSecRange(0.0f), fParticleSum(0.0f),
                           fMiscFlags(0) { }

plSimpleParticleGenerator::~plSimpleParticleGenerator() {
    if (fInitPos != NULL)
        delete[] fInitPos;
    if (fInitPitch != NULL)
        delete[] fInitPitch;
    if (fInitYaw != NULL)
        delete[] fInitYaw;
}

IMPLEMENT_CREATABLE(plSimpleParticleGenerator, kSimpleParticleGenerator,
                    plParticleGenerator)

void plSimpleParticleGenerator::read(hsStream* S, plResManager* mgr) {
    fGenLife = S->readFloat();
    fPartLifeMin = S->readFloat();
    fPartLifeMax = S->readFloat();
    fParticlesPerSecond = S->readFloat();
    
    fNumSources = S->readInt();
    fInitPos = new hsPoint3[fNumSources];
    fInitPitch = new float[fNumSources];
    fInitYaw = new float[fNumSources];
    for (size_t i=0; i<fNumSources; i++) {
        fInitPos[i].read(S);
        fInitPitch[i] = S->readFloat();
        fInitYaw[i] = S->readFloat();
    }

    fAngleRange = S->readFloat();
    fVelMin = S->readFloat();
    fVelMax = S->readFloat();
    fXSize = S->readFloat();
    fYSize = S->readFloat();
    fScaleMin = S->readFloat();
    fScaleMax = S->readFloat();
    fPartMassRange = S->readFloat();
    fPartRadsPerSecRange = S->readFloat();
}

void plSimpleParticleGenerator::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fGenLife);
    S->writeFloat(fPartLifeMin);
    S->writeFloat(fPartLifeMax);
    S->writeFloat(fParticlesPerSecond);

    S->writeInt(fNumSources);
    for (size_t i=0; i<fNumSources; i++) {
        fInitPos[i].write(S);
        S->writeFloat(fInitPitch[i]);
        S->writeFloat(fInitYaw[i]);
    }

    S->writeFloat(fAngleRange);
    S->writeFloat(fVelMin);
    S->writeFloat(fVelMax);
    S->writeFloat(fXSize);
    S->writeFloat(fYSize);
    S->writeFloat(fScaleMin);
    S->writeFloat(fScaleMax);
    S->writeFloat(fPartMassRange);
    S->writeFloat(fPartRadsPerSecRange);
}

void plSimpleParticleGenerator::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("GeneratorParams");
    prc->writeParam("GenLife", fGenLife);
    prc->writeParam("PartLifeMin", fPartLifeMin);
    prc->writeParam("PartLifeMax", fPartLifeMax);
    prc->writeParam("ParticlesPerSecond", fParticlesPerSecond);
    prc->endTag(true);

    prc->writeSimpleTag("Sources");
    for (size_t i=0; i<fNumSources; i++) {
        prc->startTag("Source");
        prc->writeParam("Pitch", fInitPitch[i]);
        prc->writeParam("Yaw", fInitYaw[i]);
        prc->endTag();
        fInitPos[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->startTag("GeneratorParams2");
    prc->writeParam("AngleRange", fAngleRange);
    prc->writeParam("VelMin", fVelMin);
    prc->writeParam("VelMax", fVelMax);
    prc->writeParam("XSize", fXSize);
    prc->writeParam("YSize", fYSize);
    prc->writeParam("ScaleMin", fScaleMin);
    prc->writeParam("ScaleMax", fScaleMax);
    prc->writeParam("ParticleMass", fPartMassRange);
    prc->writeParam("RadsPerSecond", fPartRadsPerSecRange);
    prc->endTag(true);
}
