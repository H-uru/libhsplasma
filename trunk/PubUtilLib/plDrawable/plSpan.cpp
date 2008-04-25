#include "plSpan.h"

plSpan::plSpan() { }
plSpan::~plSpan() { }

const char* plSpan::ClassName() { return "plSpan"; }

void plSpan::read(hsStream* S) {
    fSubType = S->readInt();
    fMaterialIdx = S->readInt();
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fProps = S->readInt();
    fLocalBounds.read(S);
    fWorldBounds.read(S);
    fNumMatrices = S->readInt();
    fBaseMatrix = S->readInt();
    fLocalUVWChans = S->readShort();
    fMaxBoneIdx = S->readShort();
    fPenBoneIdx = S->readShort();
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
    if (fProps & kWaterHeight)
        fWaterHeight = S->readFloat();
}

void plSpan::write(hsStream* S) {
    S->writeInt(fSubType);
    S->writeInt(fMaterialIdx);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    S->writeInt(fProps);
    fLocalBounds.write(S);
    fWorldBounds.write(S);
    S->writeInt(fNumMatrices);
    S->writeInt(fBaseMatrix);
    S->writeShort(fLocalUVWChans);
    S->writeShort(fMaxBoneIdx);
    S->writeShort(fPenBoneIdx);
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
    if (fProps & kWaterHeight)
        S->writeFloat(fWaterHeight);
}

void plSpan::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag(ClassName());
    IPrcWrite(prc);
    prc->closeTag();
}

void plSpan::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("SpanInfo");
      prc->writeParam("SubType", fSubType);
      prc->writeParam("Material", fMaterialIdx);
      prc->writeParamHex("Properties", fProps);
    prc->endTag(true);
    prc->writeSimpleTag("Transforms");
      fLocalToWorld.prcWrite(prc);
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Bounds");
      fLocalBounds.prcWrite(prc);
      fWorldBounds.prcWrite(prc);
    prc->closeTag();
    prc->startTag("MatrixInfo");
      prc->writeParam("NumMatrices", fNumMatrices);
      prc->writeParam("BaseMatrix", fBaseMatrix);
      prc->writeParam("UVWChans", fLocalUVWChans);
    prc->endTag(true);
    prc->startTag("BoneIndices");
      prc->writeParam("Max", fMaxBoneIdx);
      prc->writeParam("Pen", fPenBoneIdx);
    prc->endTag(true);
    prc->startTag("Dists");
      prc->writeParam("Min", fMinDist);
      prc->writeParam("Max", fMaxDist);
    prc->endTag(true);
    if (fProps & kWaterHeight) {
        prc->startTag("WaterHeight");
        prc->writeParam("value", fWaterHeight);
        prc->endTag(true);
    }
}

const plKey& plSpan::getFogEnvironment() const { return fFogEnvironment; }
const hsTArray<plKey>& plSpan::getPermaLights() const { return fPermaLights; }
const hsTArray<plKey>& plSpan::getPermaProjs() const { return fPermaProjs; }
unsigned short plSpan::getTypeMask() const { return fTypeMask; }
unsigned int plSpan::getMaterialIdx() const { return fMaterialIdx; }
unsigned char plSpan::getNumMatrices() const { return fNumMatrices; }
unsigned int plSpan::getProps() const { return fProps; }

void plSpan::setFogEnvironment(const plKey& fog) {
    fFogEnvironment = fog;
}
void plSpan::addPermaLight(const plKey& light) {
    fPermaLights.append(light);
}
void plSpan::addPermaProj(const plKey& proj) {
    fPermaProjs.append(proj);
}

