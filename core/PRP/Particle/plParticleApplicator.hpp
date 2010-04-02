#ifndef _PLPARTICLEAPPLICATOR_H
#define _PLPARTICLEAPPLICATOR_H

#include "PRP/Avatar/plAGApplicator.h"

DllClass plParticleApplicator : public plAGApplicator {
    CREATABLE(plParticleApplicator, kParticleApplicator, plAGApplicator)
};


DllClass plParticleAngleApplicator : public plParticleApplicator {
    CREATABLE(plParticleAngleApplicator, kParticleAngleApplicator,
              plParticleApplicator)
};


DllClass plParticleLifeMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleLifeMinApplicator, kParticleLifeMinApplicator,
              plParticleApplicator)
};


DllClass plParticleLifeMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleLifeMaxApplicator, kParticleLifeMaxApplicator,
              plParticleApplicator)
};


DllClass plParticlePPSApplicator : public plParticleApplicator {
    CREATABLE(plParticlePPSApplicator, kParticlePPSApplicator,
              plParticleApplicator)
};


DllClass plParticleScaleMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleScaleMinApplicator, kParticleScaleMinApplicator,
              plParticleApplicator)
};


DllClass plParticleScaleMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleScaleMaxApplicator, kParticleScaleMaxApplicator,
              plParticleApplicator)
};


DllClass plParticleVelMinApplicator : public plParticleApplicator {
    CREATABLE(plParticleVelMinApplicator, kParticleVelMinApplicator,
              plParticleApplicator)
};


DllClass plParticleVelMaxApplicator : public plParticleApplicator {
    CREATABLE(plParticleVelMaxApplicator, kParticleVelMaxApplicator,
              plParticleApplicator)
};

#endif
