#include "plSpan.h"

plSpan::plSpan() { }
plSpan::~plSpan() { }

void plSpan::read(hsStream *S) {
    subType = S->readInt();
    fogEnvironment = NULL;
    materialIdx = S->readInt();
    localToWorld.read(S);
    worldToLocal.read(S);
    props = S->readInt();
    localBounds.read(S);
    worldBounds.read(S);
    numMatrices = S->readInt();
    baseMatrix = S->readInt();
    localUVWChans = S->readShort();
    maxBoneIdx = S->readShort();
    penBoneIdx = S->readShort();
    minDist = S->readFloat();
    maxDist = S->readFloat();
    if (props & kWaterHeight)
        waterHeight = S->readFloat();
}

void plSpan::write(hsStream *S) {
    S->writeInt(subType);
    S->writeInt(materialIdx);
    localToWorld.write(S);
    worldToLocal.write(S);
    S->writeInt(props);
    localBounds.write(S);
    worldBounds.write(S);
    S->writeInt(numMatrices);
    S->writeInt(baseMatrix);
    S->writeShort(localUVWChans);
    S->writeShort(maxBoneIdx);
    S->writeShort(penBoneIdx);
    S->writeFloat(minDist);
    S->writeFloat(maxDist);
    if (props & kWaterHeight)
        S->writeFloat(waterHeight);
}

unsigned short plSpan::getTypeMask() { return typeMask; }
unsigned int plSpan::getMaterialIdx() { return materialIdx; }
unsigned char plSpan::getNumMatrices() { return numMatrices; }
unsigned int plSpan::getProps() { return props; }

void plSpan::setFogEnviron(plKey* fog) { fogEnvironment = (plFogEnvironment*)fog->objPtr; }
void plSpan::setPermaLight(plKey* light) { permaLights.append((plLightInfo*&)light->objPtr); }
void plSpan::setPermaProj(plKey* proj) { permaProjs.append((plLightInfo*&)proj->objPtr); }
