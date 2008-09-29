#ifndef _PLPARTICLEEMITTER_H
#define _PLPARTICLEEMITTER_H

#include "PRP/plCreatable.h"
#include "PRP/Region/hsBounds.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "plParticleGenerator.h"

DllClass plParticleEmitter : public plCreatable {
public:
    enum {
        kMatIsEmissive = 0x1,
        kNormalUp = 0x10,
        kNormalVelUpVel = 0x20,
        kNormalFromCenter = 0x40,
        kNormalDynamicMask = kNormalFromCenter | kNormalVelUpVel,
        kNormalPrecalcMask = kNormalDynamicMask | kNormalUp,
        kNormalViewFacing = 0x100,
        kNormalNearestLight = 0x200,
        kNeedsUpdate = 0x1000000,
        kBorrowedGenerator = 0x2000000,
        kOverrideLocalToWorld = 0x4000000,
        kOnReserve = 0x8000000,
        kOrientationUp = 0x10000000,
        kOrientationVelocityBased = 0x20000000,
        kOrientationVelocityStretch = 0x40000000,
        kOrientationVelocityFlow = 0x80000000,
        kOrientationVelocityMask =
            kOrientationVelocityFlow | kOrientationVelocityStretch |
            kOrientationVelocityBased,
        kOrientationMask = kOrientationVelocityMask | kOrientationUp
    };

protected:
    unsigned int fMiscFlags, fSpanIndex, fMaxParticles;
    plParticleGenerator* fGenerator;
    hsColorRGBA fColor;

public:
    plParticleEmitter();
    virtual ~plParticleEmitter();

    DECLARE_CREATABLE(plParticleEmitter)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
