#ifndef _PLPARTICLEGENERATOR_H
#define _PLPARTICLEGENERATOR_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "CoreLib/hsGeometry3.h"

DllClass plParticleGenerator : public plCreatable {
public:
    plParticleGenerator();
    virtual ~plParticleGenerator();

    DECLARE_CREATABLE(plParticleGenerator)
};

DllClass plOneTimeParticleGenerator : public plParticleGenerator {
protected:
    unsigned int fCount;
    hsPoint3* fPosition;
    hsVector3* fDirection;
    float fXSize, fYSize, fScaleMin, fScaleMax, fPartRadsPerSecRange;

public:
    plOneTimeParticleGenerator();
    virtual ~plOneTimeParticleGenerator();

    DECLARE_CREATABLE(plOneTimeParticleGenerator);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plSimpleParticleGenerator : public plParticleGenerator {
public:
    enum {
        kImmortal = 0x1,
        kDisabled = 0x2
    };

protected:
    float fParticlesPerSecond;
    unsigned int fNumSources;
    hsPoint3* fInitPos;
    float* fInitPitch;
    float* fInitYaw;
    float fAngleRange, fVelMin, fVelMax, fXSize, fYSize, fScaleMin, fScaleMax;
    float fGenLife, fPartLifeMin, fPartLifeMax, fPartMassRange;
    float fPartRadsPerSecRange, fParticleSum;
    unsigned int fMiscFlags;

public:
    plSimpleParticleGenerator();
    virtual ~plSimpleParticleGenerator();

    DECLARE_CREATABLE(plSimpleParticleGenerator);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
