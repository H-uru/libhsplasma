#include "plParticleApplicator.h"

// plParticleApplicator //
plParticleApplicator::plParticleApplicator() { }
plParticleApplicator::~plParticleApplicator() { }

IMPLEMENT_CREATABLE(plParticleApplicator, kParticleApplicator, plAGApplicator)


// plParticleAngleApplicator //
plParticleAngleApplicator::plParticleAngleApplicator() { }
plParticleAngleApplicator::~plParticleAngleApplicator() { }

IMPLEMENT_CREATABLE(plParticleAngleApplicator, kParticleAngleApplicator,
                    plParticleApplicator)


// plParticleLifeMinApplicator //
plParticleLifeMinApplicator::plParticleLifeMinApplicator() { }
plParticleLifeMinApplicator::~plParticleLifeMinApplicator() { }

IMPLEMENT_CREATABLE(plParticleLifeMinApplicator, kParticleLifeMinApplicator,
                    plParticleApplicator)


// plParticleLifeMaxApplicator //
plParticleLifeMaxApplicator::plParticleLifeMaxApplicator() { }
plParticleLifeMaxApplicator::~plParticleLifeMaxApplicator() { }

IMPLEMENT_CREATABLE(plParticleLifeMaxApplicator, kParticleLifeMaxApplicator,
                    plParticleApplicator)


// plParticlePPSApplicator //
plParticlePPSApplicator::plParticlePPSApplicator() { }
plParticlePPSApplicator::~plParticlePPSApplicator() { }

IMPLEMENT_CREATABLE(plParticlePPSApplicator, kParticlePPSApplicator,
                    plParticleApplicator)


// plParticleScaleMinApplicator //
plParticleScaleMinApplicator::plParticleScaleMinApplicator() { }
plParticleScaleMinApplicator::~plParticleScaleMinApplicator() { }

IMPLEMENT_CREATABLE(plParticleScaleMinApplicator, kParticleScaleMinApplicator,
                    plParticleApplicator)


// plParticleScaleMaxApplicator //
plParticleScaleMaxApplicator::plParticleScaleMaxApplicator() { }
plParticleScaleMaxApplicator::~plParticleScaleMaxApplicator() { }

IMPLEMENT_CREATABLE(plParticleScaleMaxApplicator, kParticleScaleMaxApplicator,
                    plParticleApplicator)


// plParticleVelMinApplicator //
plParticleVelMinApplicator::plParticleVelMinApplicator() { }
plParticleVelMinApplicator::~plParticleVelMinApplicator() { }

IMPLEMENT_CREATABLE(plParticleVelMinApplicator, kParticleVelMinApplicator,
                    plParticleApplicator)


// plParticleVelMaxApplicator //
plParticleVelMaxApplicator::plParticleVelMaxApplicator() { }
plParticleVelMaxApplicator::~plParticleVelMaxApplicator() { }

IMPLEMENT_CREATABLE(plParticleVelMaxApplicator, kParticleVelMaxApplicator,
                    plParticleApplicator)
