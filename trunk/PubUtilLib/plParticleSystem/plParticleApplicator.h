#ifndef _PLPARTICLEAPPLICATOR_H
#define _PLPARTICLEAPPLICATOR_H

#include "PubUtilLib/plAvatar/plAGApplicator.h"

DllClass plParticleApplicator : public plAGApplicator {
public:
    plParticleApplicator();
    virtual ~plParticleApplicator();

    DECLARE_CREATABLE(plParticleApplicator)
};

DllClass plParticleAngleApplicator : public plParticleApplicator {
public:
    plParticleAngleApplicator();
    virtual ~plParticleAngleApplicator();

    DECLARE_CREATABLE(plParticleAngleApplicator)
};

/* Doesn't have unique Creatable Index
DllClass plParticleDragApplicator : public plParticleApplicator {
public:
    plParticleDragApplicator();
    virtual ~plParticleDragApplicator();

    DECLARE_CREATABLE(plParticleDragApplicator)
};*/

/* Doesn't have unique Creatable Index
DllClass plParticleGravityApplicator : public plParticleApplicator {
public:
    plParticleGravityApplicator();
    virtual ~plParticleGravityApplicator();

    DECLARE_CREATABLE(plParticleGravityApplicator)
};*/

DllClass plParticleLifeMinApplicator : public plParticleApplicator {
public:
    plParticleLifeMinApplicator();
    virtual ~plParticleLifeMinApplicator();

    DECLARE_CREATABLE(plParticleLifeMinApplicator)
};

DllClass plParticleLifeMaxApplicator : public plParticleApplicator {
public:
    plParticleLifeMaxApplicator();
    virtual ~plParticleLifeMaxApplicator();

    DECLARE_CREATABLE(plParticleLifeMaxApplicator)
};

DllClass plParticlePPSApplicator : public plParticleApplicator {
public:
    plParticlePPSApplicator();
    virtual ~plParticlePPSApplicator();

    DECLARE_CREATABLE(plParticlePPSApplicator)
};

DllClass plParticleScaleMinApplicator : public plParticleApplicator {
public:
    plParticleScaleMinApplicator();
    virtual ~plParticleScaleMinApplicator();

    DECLARE_CREATABLE(plParticleScaleMinApplicator)
};

DllClass plParticleScaleMaxApplicator : public plParticleApplicator {
public:
    plParticleScaleMaxApplicator();
    virtual ~plParticleScaleMaxApplicator();

    DECLARE_CREATABLE(plParticleScaleMaxApplicator)
};

DllClass plParticleVelMinApplicator : public plParticleApplicator {
public:
    plParticleVelMinApplicator();
    virtual ~plParticleVelMinApplicator();

    DECLARE_CREATABLE(plParticleVelMinApplicator)
};

DllClass plParticleVelMaxApplicator : public plParticleApplicator {
public:
    plParticleVelMaxApplicator();
    virtual ~plParticleVelMaxApplicator();

    DECLARE_CREATABLE(plParticleVelMaxApplicator)
};

#endif
