#include "plGeometrySpan.h"
#include "Debug/plDebug.h"

plGeometrySpan::plGeometrySpan()
              : fVertexData(NULL), fIndexData(NULL), fMultColor(NULL),
                fAddColor(NULL), fDiffuseRGBA(NULL), fSpecularRGBA(NULL) { }

plGeometrySpan::~plGeometrySpan() {
    if (fVertexData != NULL)
        delete[] fVertexData;
    if (fMultColor != NULL)
        delete[] fMultColor;
    if (fAddColor != NULL)
        delete[] fAddColor;
    if (fDiffuseRGBA != NULL)
        delete[] fDiffuseRGBA;
    if (fSpecularRGBA != NULL)
        delete[] fSpecularRGBA;
    if (fIndexData != NULL)
        delete[] fIndexData;
}

unsigned int plGeometrySpan::CalcVertexSize(unsigned char format) {
    unsigned int size = ((format & kUVCountMask) + 2) * 12;
    size += ((format & kSkinWeightMask) >> 4) * sizeof(float);
    if (format & kSkinIndices)
        size += sizeof(int);
    return size;
}

void plGeometrySpan::read(hsStream* S) {
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLocalBounds.read(S);
    //if (fWorldBounds != fLocalBounds)
    //    fWorldBounds.Reset(fLocalBounds);
    //fWorldBounds.Transform(&fLocalToWorld);
    fOBBToLocal.read(S);
    fLocalToOBB.read(S);
    
    fBaseMatrix = S->readInt();
    fNumMatrices = S->readByte();
    fLocalUVWChans = S->readShort();
    fMaxBoneIdx = S->readShort();
    fPenBoneIdx = S->readShort();
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
    fFormat = S->readByte();
    fProps = S->readInt();
    fNumVerts = S->readInt();
    fNumIndices = S->readInt();
    S->readInt();  // Discarded
    S->readByte(); // Discarded
    fDecalLevel = S->readInt();
    
    if (fProps & kWaterHeight)
        fWaterHeight = S->readFloat();
    
    if (fNumVerts > 0) {
        unsigned int stride = CalcVertexSize(fFormat);
        fVertexData = new unsigned char[fNumVerts * stride];
        S->read(fNumVerts * stride, fVertexData);
        
        fMultColor = new hsColorRGBA[fNumVerts];
        fAddColor = new hsColorRGBA[fNumVerts];
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].read(S);
            fAddColor[i].read(S);
        }
        fDiffuseRGBA = new unsigned int[fNumVerts];
        fSpecularRGBA = new unsigned int[fNumVerts];
        S->readInts(fNumVerts, (hsUint32*)fDiffuseRGBA);
        S->readInts(fNumVerts, (hsUint32*)fSpecularRGBA);
    } else {
        fVertexData = NULL;
        fMultColor = NULL;
        fAddColor = NULL;
        fDiffuseRGBA = NULL;
        fSpecularRGBA = NULL;
    }

    if (fNumIndices > 0) {
        fIndexData = new unsigned short[fNumIndices];
        S->readShorts(fNumIndices, (hsUint16*)fIndexData);
    } else {
        fIndexData = NULL;
    }
    
    fInstanceGroup = S->readInt();
    if (fInstanceGroup != 0) {
        //fInstanceRefs = IGetInstanceGroup(fInstanceGroup, S->readInt());
        //fInstanceRefs->append(this);
        plDebug::Warning("WARNING: plGeometrySpan::read Incomplete");
        numInstanceRefs = S->readInt();
    }
}

void plGeometrySpan::write(hsStream* S) {
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    fLocalBounds.write(S);
    fOBBToLocal.write(S);
    fLocalToOBB.write(S);
    
    S->writeInt(fBaseMatrix);
    S->writeByte(fNumMatrices);
    S->writeShort(fLocalUVWChans);
    S->writeShort(fMaxBoneIdx);
    S->writeShort(fPenBoneIdx);
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
    S->writeByte(fFormat);
    S->writeInt(fProps);
    S->writeInt(fNumVerts);
    S->writeInt(fNumIndices);
    S->writeInt(0);
    S->writeByte(0);
    S->writeInt(fDecalLevel);
    
    if (fProps & kWaterHeight)
        S->writeFloat(fWaterHeight);
    
    if (fNumVerts > 0) {
        S->write(fNumVerts * CalcVertexSize(fFormat), fVertexData);
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].write(S);
            fAddColor[i].write(S);
        }
        S->writeInts(fNumVerts, (hsUint32*)fDiffuseRGBA);
        S->writeInts(fNumVerts, (hsUint32*)fSpecularRGBA);
        
    }
    if (fNumIndices > 0)
        S->writeShorts(fNumIndices, (hsUint16*)fIndexData);

    S->writeInt(fInstanceGroup);
    if (fInstanceGroup != 0) {
        plDebug::Warning("WARNING: plGeometrySpan::write Incomplete");
        S->writeInt(numInstanceRefs);
    }
}

void plGeometrySpan::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGeometrySpan");
    prc->writeParam("BaseMatrix", fBaseMatrix);
    prc->writeParam("NumMatrices", fNumMatrices);
    prc->writeParam("LocalUVWChans", fLocalUVWChans);
    prc->writeParam("MaxBoneIdx", fMaxBoneIdx);
    prc->writeParam("PenBoneIdx", fPenBoneIdx);
    prc->writeParam("MinDist", fMinDist);
    prc->writeParam("MaxDist", fMaxDist);
    prc->writeParamHex("Format", fFormat);
    prc->writeParamHex("Props", fProps);
    prc->writeParam("DecalLevel", fDecalLevel);
    if (fProps & kWaterHeight)
        prc->writeParam("WaterHeight", fWaterHeight);
    prc->endTag();
    
    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        hsTArray<TempVertex> verts = getVertices();
        prc->writeSimpleTag("Vertices");
        for (size_t i=0; i<verts.getSize(); i++) {
            prc->writeSimpleTag("Vertex");

            prc->writeSimpleTag("Position");
            verts[i].fPosition.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("Normal");
            verts[i].fNormal.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("UVWMaps");
            for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++)
                verts[i].fUVs[j].prcWrite(prc);
            prc->closeTag();

            prc->startTag("Weights");
            if (fFormat & kSkinIndices)
                prc->writeParam("Index", verts[i].fIndices);
            prc->endTagNoBreak();
            for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                prc->getStream()->writeStr(plString::Format("%f ", verts[i].fWeights[j]));
            prc->closeTagNoBreak();

            prc->closeTag();    // Vertex
        }
        prc->closeTag();    // Vertices

        prc->writeSimpleTag("MultColors");
        for (size_t i=0; i<fNumVerts; i++)
            fMultColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("AddColors");
        for (size_t i=0; i<fNumVerts; i++)
            fAddColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("DiffuseColors");
        for (size_t i=0; i<fNumVerts; i++) {
            hsColor32 cl(fDiffuseRGBA[i]);
            cl.prcWrite(prc);
        }
        prc->closeTag();
        prc->writeSimpleTag("SpecularColors");
        for (size_t i=0; i<fNumVerts; i++) {
            hsColor32 cl(fSpecularRGBA[i]);
            cl.prcWrite(prc);
        }
        prc->closeTag();

        prc->writeSimpleTag("Triangles");
        for (size_t i=0; i<fNumIndices; i += 3) {
            prc->writeTagNoBreak("Triangle");
            prc->getStream()->writeStr(plString::Format("%d %d %d",
                                       fIndexData[i], fIndexData[i+1], fIndexData[i+2]));
            prc->closeTagNoBreak();
        }
        prc->closeTag();

        prc->startTag("InstanceGroup");
        prc->writeParam("value", fInstanceGroup);
        if (fInstanceGroup != 0)
            prc->writeParam("NumRefs", numInstanceRefs);
        prc->endTag(true);
    } else {
        prc->writeComment("Vertex data excluded");
    }
    prc->closeTag();    // plGeometrySpan
}

void plGeometrySpan::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plGeometrySpan")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fBaseMatrix = tag->getParam("BaseMatrix", "0").toUint();
    fNumMatrices = tag->getParam("NumMatrices", "0").toUint();
    fLocalUVWChans = tag->getParam("LocalUVWChans", "0").toUint();
    fMaxBoneIdx = tag->getParam("MaxBoneIdx", "0").toUint();
    fPenBoneIdx = tag->getParam("PenBoneIdx", "0").toUint();
    fMinDist = tag->getParam("MinDist", "0").toFloat();
    fMaxDist = tag->getParam("MaxDist", "0").toFloat();
    fFormat = tag->getParam("Format", "0").toUint();
    fProps = tag->getParam("Props", "0").toUint();
    fDecalLevel = tag->getParam("DecalLevel", "0").toUint();
    fWaterHeight = tag->getParam("WaterHeight", "0").toFloat();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Vertices") {
            fNumVerts = child->countChildren();
            hsTArray<TempVertex> verts;
            verts.setSize(fNumVerts);
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                if (vertChild->getName() != "Vertex")
                    throw pfPrcTagException(__FILE__, __LINE__, vertChild->getName());
                const pfPrcTag* subChild = vertChild->getFirstChild();
                while (subChild != NULL) {
                    if (subChild->getName() == "Position") {
                        if (subChild->hasChildren())
                            verts[i].fPosition.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "Normal") {
                        if (subChild->hasChildren())
                            verts[i].fNormal.prcParse(subChild->getFirstChild());
                    } else if (subChild->getName() == "UVWMaps") {
                        if (subChild->countChildren() != (size_t)(fFormat & kUVCountMask))
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of UV maps");
                        const pfPrcTag* uvChild = subChild->getFirstChild();
                        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
                            verts[i].fUVs[j].prcParse(uvChild);
                            uvChild = uvChild->getNextSibling();
                        }
                    } else if (subChild->getName() == "Weights") {
                        verts[i].fIndices = subChild->getParam("Index", "0").toUint();
                        hsTList<plString> wgtList = subChild->getContents();
                        if (wgtList.getSize() != (size_t)((fFormat & kSkinWeightMask) >> 4))
                            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect Number of Weights");
                        for (size_t j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                            verts[i].fWeights[j] = wgtList.pop().toFloat();
                    } else {
                        throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                    }
                    subChild = subChild->getNextSibling();
                }
                vertChild = vertChild->getNextSibling();
            }
            setVertices(verts);
        } else if (child->getName() == "MultColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fMultColor = new hsColorRGBA[fNumVerts];
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                fMultColor[i].prcParse(clrChild);
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "AddColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fAddColor = new hsColorRGBA[fNumVerts];
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                fAddColor[i].prcParse(clrChild);
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "DiffuseColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fDiffuseRGBA = new unsigned int[fNumVerts];
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                hsColor32 cl;
                cl.prcParse(clrChild);
                fDiffuseRGBA[i] = cl.color;
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "SpecularColors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of colors");
            fSpecularRGBA = new unsigned int[fNumVerts];
            const pfPrcTag* clrChild = child->getFirstChild();
            for (size_t i=0; i<fNumVerts; i++) {
                hsColor32 cl;
                cl.prcParse(clrChild);
                fSpecularRGBA[i] = cl.color;
                clrChild = clrChild->getNextSibling();
            }
        } else if (child->getName() == "Triangles") {
            fNumIndices = child->countChildren() * 3;
            fIndexData = new unsigned short[fNumIndices];
            const pfPrcTag* triChild = child->getFirstChild();
            for (size_t i=0; i<fNumIndices; i += 3) {
                if (triChild->getName() != "Triangle")
                    throw pfPrcTagException(__FILE__, __LINE__, triChild->getName());
                hsTList<plString> idxList = triChild->getContents();
                if (idxList.getSize() != 3)
                    throw pfPrcParseException(__FILE__, __LINE__, "Triangles should have exactly 3 indices");
                fIndexData[i] = idxList.pop().toUint();
                fIndexData[i+1] = idxList.pop().toUint();
                fIndexData[i+2] = idxList.pop().toUint();
                triChild = triChild->getNextSibling();
            }
        } else if (child->getName() == "InstanceGroup") {
            fInstanceGroup = child->getParam("value", "0").toUint();
            numInstanceRefs = child->getParam("NumRefs", "0").toUint();
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

void plGeometrySpan::setMaterial(const plKey& mat) { fMaterial = mat; }
void plGeometrySpan::setFogEnvironment(const plKey& fog) { fFogEnviron = fog; }

hsTArray<plGeometrySpan::TempVertex> plGeometrySpan::getVertices() const {
    hsTArray<TempVertex> buf;
    buf.setSize(fNumVerts);
    
    unsigned char* cp = fVertexData;
    for (size_t i=0; i<fNumVerts; i++) {
        buf[i].fPosition.X = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.Z = *(float*)cp; cp += sizeof(float);

        buf[i].fNormal.X = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Y = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.Z = *(float*)cp; cp += sizeof(float);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            buf[i].fUVs[j].X = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].Y = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].Z = *(float*)cp; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        for (int j=0; j<weightCount; j++) {
            buf[i].fWeights[j] = *(float*)cp;
            cp += sizeof(float);
        }
        if (fFormat & kSkinIndices) {
            buf[i].fIndices = *(int*)cp;
            cp += sizeof(int);
        }
    }
    return buf;
}

void plGeometrySpan::setVertices(const hsTArray<TempVertex>& verts) {
    unsigned int stride = CalcVertexSize(fFormat);
    fNumVerts = verts.getSize();
    fVertexData = new unsigned char[fNumVerts * stride];

    unsigned char* cp = fVertexData;
    for (size_t i=0; i<fNumVerts; i++) {
        *(float*)cp = verts[i].fPosition.X; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fPosition.Z; cp += sizeof(float);

        *(float*)cp = verts[i].fNormal.X; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Y; cp += sizeof(float);
        *(float*)cp = verts[i].fNormal.Z; cp += sizeof(float);

        for (size_t j=0; j<(size_t)(fFormat & kUVCountMask); j++) {
            *(float*)cp = verts[i].fUVs[j].X; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Y; cp += sizeof(float);
            *(float*)cp = verts[i].fUVs[j].Z; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        for (int j=0; j<weightCount; j++) {
            *(float*)cp = verts[i].fWeights[j];
            cp += sizeof(float);
        }
        if (fFormat & kSkinIndices) {
            *(int*)cp = verts[i].fIndices;
            cp += sizeof(int);
        }
    }
}

hsTArray<unsigned short> plGeometrySpan::getIndices() const {
    hsTArray<unsigned short> buf;
    buf.setSize(fNumIndices);
    for (size_t i=0; i<fNumIndices; i++)
        buf[i] = fIndexData[i];
    return buf;
}

void plGeometrySpan::setIndices(const hsTArray<unsigned short>& indices) {
    if (fIndexData != NULL)
        delete[] fIndexData;
    fNumIndices = indices.getSize();
    if (fNumIndices > 0) {
        fIndexData = new unsigned short[fNumIndices];
        for (size_t i=0; i<fNumIndices; i++)
            fIndexData[i] = indices[i];
    } else {
        fIndexData = NULL;
    }
}
