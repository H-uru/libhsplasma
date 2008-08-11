#include "plSpan.h"

plSpan::plSpan()
      : fSubType(kVertexSpan), fMaterialIdx(0), fBaseMatrix(0), fNumMatrices(0),
        fLocalUVWChans(0), fMaxBoneIdx(0), fPenBoneIdx(0), fProps(0),
        fMinDist(0), fMaxDist(0), fWaterHeight(0) { }

plSpan::plSpan(const plSpan& init)
      : fSubType(init.fSubType), fMaterialIdx(init.fMaterialIdx),
        fLocalToWorld(init.fLocalToWorld), fWorldToLocal(init.fWorldToLocal),
        fBaseMatrix(init.fBaseMatrix), fNumMatrices(init.fNumMatrices),
        fLocalUVWChans(init.fLocalUVWChans), fMaxBoneIdx(init.fMaxBoneIdx),
        fPenBoneIdx(init.fPenBoneIdx), fProps(init.fProps),
        fLocalBounds(init.fLocalBounds), fWorldBounds(init.fWorldBounds),
        fFogEnvironment(init.fFogEnvironment), fMinDist(init.fMinDist),
        fMaxDist(init.fMaxDist), fWaterHeight(init.fWaterHeight),
        fPermaLights(init.fPermaLights), fPermaProjs(init.fPermaProjs) { }

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

void plSpan::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        IPrcParse(child);
        child = child->getNextSibling();
    }
}

void plSpan::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("SpanInfo");
      prc->writeParam("SubType", fSubType);
      prc->writeParam("Material", fMaterialIdx);
      prc->writeParamHex("Properties", fProps);
    prc->endTag(true);
    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalBounds");
      fLocalBounds.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldBounds");
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

void plSpan::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "SpanInfo") {
        fSubType = tag->getParam("SubType", "0").toUint();
        fMaterialIdx = tag->getParam("Material", "0").toUint();
        fProps = tag->getParam("Properties", "0").toUint();
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "MatrixInfo") {
        fNumMatrices = tag->getParam("NumMatrices", "0").toUint();
        fBaseMatrix = tag->getParam("BaseMatrix", "0").toUint();
        fLocalUVWChans = tag->getParam("UVWChans", "0").toUint();
    } else if (tag->getName() == "BoneIndices") {
        fMaxBoneIdx = tag->getParam("Max", "0").toUint();
        fPenBoneIdx = tag->getParam("Pen", "0").toUint();
    } else if (tag->getName() == "Dists") {
        fMinDist = tag->getParam("Min", "0").toFloat();
        fMaxDist = tag->getParam("Max", "0").toFloat();
    } else if (tag->getName() == "WaterHeight") {
        fWaterHeight = tag->getParam("value", "0").toFloat();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

plKey plSpan::getFogEnvironment() const { return fFogEnvironment; }
const hsTArray<plKey>& plSpan::getPermaLights() const { return fPermaLights; }
const hsTArray<plKey>& plSpan::getPermaProjs() const { return fPermaProjs; }
hsMatrix44 plSpan::getLocalToWorld() const { return fLocalToWorld; }
hsMatrix44 plSpan::getWorldToLocal() const { return fWorldToLocal; }
unsigned short plSpan::getSubType() const { return fSubType; }
unsigned int plSpan::getMaterialIdx() const { return fMaterialIdx; }
unsigned char plSpan::getNumMatrices() const { return fNumMatrices; }
unsigned int plSpan::getProps() const { return fProps; }
unsigned int plSpan::getBaseMatrix() const { return fBaseMatrix; }
unsigned short plSpan::getMaxBoneIdx() const { return fMaxBoneIdx; }
unsigned short plSpan::getPenBoneIdx() const { return fPenBoneIdx; }
unsigned short plSpan::getLocalUVWChans() const { return fLocalUVWChans; }
float plSpan::getMinDist() const { return fMinDist; }
float plSpan::getMaxDist() const { return fMaxDist; }
float plSpan::getWaterHeight() const { return fWaterHeight; }
hsBounds3Ext& plSpan::getLocalBounds() { return fLocalBounds; }
hsBounds3Ext& plSpan::getWorldBounds() { return fWorldBounds; }

void plSpan::setFogEnvironment(plKey fog) { fFogEnvironment = fog; }
void plSpan::clearPermaLights() { fPermaLights.clear(); }
void plSpan::addPermaLight(plKey light) { fPermaLights.append(light); }
void plSpan::clearPermaProjs() { fPermaProjs.clear(); }
void plSpan::addPermaProj(plKey proj) { fPermaProjs.append(proj); }
void plSpan::setLocalToWorld(hsMatrix44 l2w) { fLocalToWorld = l2w; }
void plSpan::setWorldToLocal(hsMatrix44 w2l) { fWorldToLocal = w2l; }
void plSpan::setSubType(unsigned short type) { fSubType = type; }
void plSpan::setMaterialIdx(unsigned int idx) { fMaterialIdx = idx; }
void plSpan::setNumMatrices(unsigned char mats) { fNumMatrices = mats; }
void plSpan::setProps(unsigned int props) { fProps = props; }
void plSpan::setBaseMatrix(unsigned int mat) { fBaseMatrix = mat; }
void plSpan::getMaxBoneIdx(unsigned short idx) { fMaxBoneIdx = idx; }
void plSpan::getPenBoneIdx(unsigned short idx) { fPenBoneIdx = idx; }
void plSpan::getLocalUVWChans(unsigned short chans) { fLocalUVWChans = chans; }
void plSpan::getMinDist(float dist) { fMinDist = dist; }
void plSpan::getMaxDist(float dist) { fMaxDist = dist; }
void plSpan::getWaterHeight(float height) { fWaterHeight = height; }
