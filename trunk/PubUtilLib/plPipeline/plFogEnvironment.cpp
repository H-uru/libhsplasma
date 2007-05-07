#include "plFogEnvironment.h"

plFogEnvironment::plFogEnvironment() : fType(kLinearFog), fStart(1.0f),
                  fEnd(1000.0f), fDensity(0.5f) { }
plFogEnvironment::~plFogEnvironment() { }

short plFogEnvironment::ClassIndex() { return kFogEnvironment; }
short plFogEnvironment::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kFogEnvironment, ver);
}

void plFogEnvironment::read(hsStream *S) {
    hsKeyedObject::read(S);
    fType = S->readByte();
    fStart = S->readFloat();
    fEnd = S->readFloat();
    fDensity = S->readFloat();
    fColor.read(S);
}

void plFogEnvironment::write(hsStream *S) {
    hsKeyedObject::write(S);
    S->writeByte(fType);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);
    S->writeFloat(fDensity);
    fColor.write(S);
}

