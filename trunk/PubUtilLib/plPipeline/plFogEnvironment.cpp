#include "plFogEnvironment.h"

plFogEnvironment::plFogEnvironment() : fType(kLinearFog), fStart(1.0f),
                  fEnd(1000.0f), fDensity(0.5f) { }
plFogEnvironment::~plFogEnvironment() { }

IMPLEMENT_CREATABLE(plFogEnvironment, kFogEnvironment, hsKeyedObject)

void plFogEnvironment::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fType = S->readByte();
    fStart = S->readFloat();
    fEnd = S->readFloat();
    fDensity = S->readFloat();
    fColor.read(S);
}

void plFogEnvironment::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeByte(fType);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);
    S->writeFloat(fDensity);
    fColor.write(S);
}

