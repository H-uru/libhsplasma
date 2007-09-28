#include "plGeometrySpan.h"

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
        printf("WARNING: plGeometrySpan::read Incomplete\n");
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
        //throw "Incomplete";
        printf("WARNING: plGeometrySpan::write Incomplete\n");
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
    
    unsigned int i;
    unsigned int size = fNumVerts * CalcVertexSize(fFormat);
    char buf[10];
    prc->writeTagNoBreak("VertexData");
    for (i=0; i<size; i++) {
        sprintf(buf, "%02X", fVertexData[i]);
        prc->getStream()->writeStr(buf);
    }
    prc->closeTagNoBreak();

    prc->writeSimpleTag("MultColors");
    for (i=0; i<fNumVerts; i++)
        fMultColor[i].prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AddColors");
    for (i=0; i<fNumVerts; i++)
        fAddColor[i].prcWrite(prc);
    prc->closeTag();
    prc->writeTagNoBreak("DiffuseColors");
    for (i=0; i<fNumVerts; i++) {
        sprintf(buf, "%08X ", fDiffuseRGBA[i]);
        prc->getStream()->writeStr(buf);
    }
    prc->closeTagNoBreak();
    prc->writeTagNoBreak("SpecularColors");
    for (i=0; i<fNumVerts; i++) {
        sprintf(buf, "%08X ", fSpecularRGBA[i]);
        prc->getStream()->writeStr(buf);
    }
    prc->closeTagNoBreak();

    prc->writeTagNoBreak("IndexData");
    for (i=0; i<fNumIndices; i++) {
        sprintf(buf, "%04X ", fIndexData[i]);
        prc->getStream()->writeStr(buf);
    }
    prc->closeTagNoBreak();

    prc->startTag("InstanceGroup");
    prc->writeParam("value", fInstanceGroup);
    if (fInstanceGroup != 0)
        prc->writeParam("NumRefs", numInstanceRefs);
    prc->endTag(true);

    prc->closeTag();
}

void plGeometrySpan::setMaterial(const plKey& mat) { fMaterial = mat; }
void plGeometrySpan::setFogEnvironment(const plKey& fog) { fFogEnviron = fog; }

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
    throw "Dependancies Incomplete";
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
