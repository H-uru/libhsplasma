#include "plSpan.h"

plSpan::plSpan() { }
plSpan::~plSpan() { }

const char* plSpan::ClassName() { return "plSpan"; }

void plSpan::read(hsStream* S) {
    fSubType = S->readInt();
    fFogEnvironment = NULL;
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
    prc->startTag("SpanInfo");
      prc->writeParam("SubType", fSubType);
      prc->writeParam("Material", fMaterialIdx);
      prc->writeParam("Properties", fProps);
    prc->endTag(true);
    prc->writeSimpleTag("Transforms");
      fLocalToWorld.prcWrite(prc);
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Bounds");
      fLocalBounds.prcWrite(prc);
      prc->closeTag();
      fWorldBounds.prcWrite(prc);
      prc->closeTag();
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

plKey* plSpan::getFogEnvironment() { return fFogEnvironment; }
hsTArray<plKey*>& plSpan::getPermaLights() { return fPermaLights; }
hsTArray<plKey*>& plSpan::getPermaProjs() { return fPermaProjs; }
unsigned short plSpan::getTypeMask() { return fTypeMask; }
unsigned int plSpan::getMaterialIdx() { return fMaterialIdx; }
unsigned char plSpan::getNumMatrices() { return fNumMatrices; }
unsigned int plSpan::getProps() { return fProps; }

void plSpan::setFogEnvironment(plKey* fog) {
    //fFogEnvironment = plFogEnvironment::Convert(fog);
    fFogEnvironment = fog;
}
void plSpan::addPermaLight(plKey* light) {
    //plLightInfo* li = plLightInfo::Convert(light);
    //fPermaLights.append(li);
    fPermaLights.append(light);
}
void plSpan::addPermaProj(plKey* proj) {
    //plLightInfo* li = plLightInfo::Convert(proj);
    //fPermaProjs.append(li);
    fPermaProjs.append(proj);
}

