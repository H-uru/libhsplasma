#include "plFogEnvironment.h"

plFogEnvironment::plFogEnvironment(PlasmaVer pv) : c10(0), f14(0.0f), f18(0.0f),
                  f1C(0.0f), f20(0.0f), f24(0.0f), f28(0.0f), f2C(0.0f) { }

plFogEnvironment::~plFogEnvironment() { }

void plFogEnvironment::read(hsStream *S) {
    hsKeyedObject::read(S);
    c10 = S->readByte();
    f14 = S->readFloat();
    f18 = S->readFloat();
    f1C = S->readFloat();
    f20 = S->readFloat();
    f24 = S->readFloat();
    f28 = S->readFloat();
    f2C = S->readFloat();
}

void plFogEnvironment::write(hsStream *S) {
    hsKeyedObject::write(S);
    S->writeByte(c10);
    S->writeFloat(f14);
    S->writeFloat(f18);
    S->writeFloat(f1C);
    S->writeFloat(f20);
    S->writeFloat(f24);
    S->writeFloat(f28);
    S->writeFloat(f2C);
}

