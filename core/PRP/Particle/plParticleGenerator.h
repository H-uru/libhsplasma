#ifndef _PLPARTICLEGENERATOR_H
#define _PLPARTICLEGENERATOR_H

#include "PRP/plCreatable.h"
#include "Math/hsGeometry3.h"

DllClass plParticleGenerator : public plCreatable {
    CREATABLE(plParticleGenerator, kParticleGenerator, plCreatable)
};


DllClass plOneTimeParticleGenerator : public plParticleGenerator {
    CREATABLE(plOneTimeParticleGenerator, kOneTimeParticleGenerator,
              plParticleGenerator)

protected:
    unsigned int fCount;
    hsVector3* fPosition;
    hsVector3* fDirection;
    float fXSize, fYSize, fScaleMin, fScaleMax, fPartRadsPerSecRange;

public:
    plOneTimeParticleGenerator();
    virtual ~plOneTimeParticleGenerator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearParticles();
};


DllClass plSimpleParticleGenerator : public plParticleGenerator {
    CREATABLE(plSimpleParticleGenerator, kSimpleParticleGenerator,
              plParticleGenerator)

public:
    enum {
        kImmortal = 0x1,
        kDisabled = 0x2
    };

protected:
    float fParticlesPerSecond;
    unsigned int fNumSources;
    hsVector3* fInitPos;
    float* fInitPitch;
    float* fInitYaw;
    float fAngleRange, fVelMin, fVelMax, fXSize, fYSize, fScaleMin, fScaleMax;
    float fGenLife, fPartLifeMin, fPartLifeMax, fPartMassRange;
    float fPartRadsPerSecRange;

public:
    plSimpleParticleGenerator();
    virtual ~plSimpleParticleGenerator();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearSources();
};

#endif
