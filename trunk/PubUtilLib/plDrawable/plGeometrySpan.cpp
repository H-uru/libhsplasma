#include "plGeometrySpan.h"
#include "CoreLib/plDebug.h"

plGeometrySpan::plGeometrySpan()
              : fVertexData(NULL), fIndexData(NULL), fMultColor(NULL),
                fAddColor(NULL), fDiffuseRGBA(NULL), fSpecularRGBA(NULL) { }

plGeometrySpan::~plGeometrySpan() {
    if (fVertexData) delete[] fVertexData;
    if (fMultColor) delete[] fMultColor;
    if (fAddColor) delete[] fAddColor;
    if (fDiffuseRGBA) delete[] fDiffuseRGBA;
    if (fSpecularRGBA) delete[] fSpecularRGBA;
    if (fIndexData) delete[] fIndexData;
}

unsigned int plGeometrySpan::CalcVertexSize(unsigned char format) {
    unsigned int size = ((format & kUVCountMask) + 2) * 12;
    size += ((format & kSkinWeightMask) >> 4) * sizeof(float);
    if (format & kSkinIndices)
        size += sizeof(int);
    return size;
}

void plGeometrySpan::read(hsStream* S) {
	//ClearBuffers();
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
        unsigned int size = CalcVertexSize(fFormat);
        fVertexData = new unsigned char[fNumVerts * size];
        S->read(fNumVerts * size, fVertexData);
        
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
        //throw "Incomplete";
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
    prc->writeParam("Format", fFormat);
    prc->writeParam("Props", fProps);
    prc->writeParam("DecalLevel", fDecalLevel);
    if (fProps & kWaterHeight)
        prc->writeParam("WaterHeight", fWaterHeight);
    prc->endTag();
    
    unsigned int i, j;
    if (!prc->isExcluded(pfPrcHelper::kExcludeVertexData)) {
        hsTArray<TempVertex> verts = getVertices();
        prc->writeSimpleTag("Vertices");
        for (i=0; i<verts.getSize(); i++) {
            prc->writeSimpleTag("Vertex");

            prc->writeSimpleTag("Position");
            verts[i].fPosition.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("Normal");
            verts[i].fNormal.prcWrite(prc);
            prc->closeTag();

            prc->writeSimpleTag("UVWMaps");
            for (j=0; j<(fFormat & kUVCountMask); j++)
                verts[i].fUVs[j].prcWrite(prc);
            prc->closeTag();

            prc->startTag("Weights");
            if (fFormat & kSkinIndices)
                prc->writeParam("Index", verts[i].fIndices);
            prc->endTagNoBreak();
            for (j=0; j<(size_t)((fFormat & kSkinWeightMask) >> 4); j++)
                prc->getStream()->writeStr(plString::Format("%f ", verts[i].fWeights[j]));
            prc->closeTagNoBreak();

            prc->closeTag();    // Vertex
        }
        prc->closeTag();    // Vertices

        prc->writeSimpleTag("MultColors");
        for (i=0; i<fNumVerts; i++)
            fMultColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("AddColors");
        for (i=0; i<fNumVerts; i++)
            fAddColor[i].prcWrite(prc);
        prc->closeTag();
        prc->writeTagNoBreak("DiffuseColors");
        for (i=0; i<fNumVerts; i++)
            prc->getStream()->writeStr(plString::Format("%08X ", fDiffuseRGBA[i]));
        prc->closeTagNoBreak();
        prc->writeTagNoBreak("SpecularColors");
        for (i=0; i<fNumVerts; i++)
            prc->getStream()->writeStr(plString::Format("%08X ", fSpecularRGBA[i]));
        prc->closeTagNoBreak();

        prc->writeTagNoBreak("IndexData");
        for (i=0; i<fNumIndices; i++)
            prc->getStream()->writeStr(plString::Format("%04X ", fIndexData[i]));
        prc->closeTagNoBreak();

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

void plGeometrySpan::setMaterial(const plKey& mat) { fMaterial = mat; }
void plGeometrySpan::setFogEnvironment(const plKey& fog) { fFogEnviron = fog; }

hsTArray<plGeometrySpan::TempVertex> plGeometrySpan::getVertices() {
    hsTArray<TempVertex> buf;
    buf.setSize(fNumVerts);
    
    unsigned char* cp = fVertexData;
    for (size_t i=0; i<fNumVerts; i++) {
        buf[i].fPosition.fX = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.fY = *(float*)cp; cp += sizeof(float);
        buf[i].fPosition.fZ = *(float*)cp; cp += sizeof(float);

        buf[i].fNormal.fX = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.fY = *(float*)cp; cp += sizeof(float);
        buf[i].fNormal.fZ = *(float*)cp; cp += sizeof(float);

        for (size_t j=0; j<(fFormat & kUVCountMask); j++) {
            buf[i].fUVs[j].fX = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].fY = *(float*)cp; cp += sizeof(float);
            buf[i].fUVs[j].fZ = *(float*)cp; cp += sizeof(float);
        }

        int weightCount = (fFormat & kSkinWeightMask) >> 4;
        if (weightCount > 0) {
            for (int j=0; j<weightCount; j++) {
                buf[i].fWeights[j] = *(float*)cp;
                cp += sizeof(float);
            }
        }
        if (fFormat & kSkinIndices) {
            buf[i].fIndices = *(int*)cp;
            cp += sizeof(int);
        }
    }
    return buf;
}

void plGeometrySpan::IClearMembers() {
    fVertexData = NULL;
    fIndexData = NULL;
    fMaterial = NULL;
    fNumIndices = 0;
    fNumVerts = 0;
    fNumMatrices = 0;
    fBaseMatrix = 0;
    fLocalUVWChans = 0;
    fMaxBoneIdx = 0;
    fPenBoneIdx = 0;
    fCreating = false;
    fFogEnviron = NULL;
    fProps = 0;
    fWaterHeight = 0.0;
    fMultColor = NULL;
    fAddColor = NULL;
    fDiffuseRGBA = NULL;
    fSpecularRGBA = NULL;
    fInstanceRefs = NULL;
    fInstanceGroup = 0;
    fSpanRefIndex = 0xFFFFFFFF;
    fMaxDist = -1.0;
    fMinDist = -1.0;
	fLocalToOBB.Reset();
    fOBBToLocal.Reset();
    fDecalLevel = 0;
    fMaxOwner = NULL;
}

void plGeometrySpan::ClearBuffers() {
    if (fProps & kUserOwned) {
        IClearMembers();
        return;
    }
    throw hsNotImplementedException(__FILE__, __LINE__, "Dependancies");
    /*
    if (fInstanceRefs != NULL) {
        if (fInstanceRefs->getSize() != 1) {
            delete fInstanceRefs;
            IClearGroupID(fInstanceGroupID);
        } else {
            fInstanceRefs->remove(fInstanceRefs->Find(this));
        }
        fInstanceRefs = NULL;
        fInstanceGroupID = 0;
    } else {
        delete[] fVertexData;
        fVertexData = NULL;
        delete[] fMultColor;
        delete[] fAddColor;
        fMultColor = NULL;
        fAddColor = NULL;
    }
    delete[] fIndexData;
    delete[] fDiffuseRGBA;
    delete[] fSpecularRGBA;
    fIndexData = NULL;
    fDiffuseRGBA = NULL;
    fSpecularRGBA = NULL;
    */
}
