#include "plGeometrySpan.h"

plGeometrySpan::plGeometrySpan(PlasmaVer pv) { }
plGeometrySpan::~plGeometrySpan() { }

void plGeometrySpan::read(hsStream *S) {
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
        // this is hsPoint3[UVCount] + fPosition + fNormal.
        unsigned int size = ((fFormat & kUVCountMask) + 2) * sizeof(hsPoint3);
        if (fFormat & kSkinWeightMask == kSkin1Weight)
            size += 4;  // 1 float
        else if (fFormat & kSkinWeightMask == kSkin2Weights)
            size += 8;  // 2 floats
        else if (fFormat & kSkinWeightMask == kSkin3Weights)
            size += 12; // 3 floats
        if (fFormat & kSkinIndices)
            size += 4;  // uint32
        fVertexData = (unsigned char*)malloc(fNumVerts * size);
        S->read(fNumVerts * size, fVertexData);
        
        fMultColor = new hsColorRGBA[fNumVerts];
        fAddColor = new hsColorRGBA[fNumVerts];
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].read(S);
            fAddColor[i].read(S);
        }
        fDiffuseRGBA = new unsigned int[fNumVerts];
        fSpecularRGBA = new unsigned int[fNumVerts];
        S->readInts(fNumVerts, (int*)fDiffuseRGBA);
        S->readInts(fNumVerts, (int*)fSpecularRGBA);
    } else {
        fVertexData = NULL;
        fMultColor = NULL;
        fAddColor = NULL;
        fDiffuseRGBA = NULL;
        fSpecularRGBA = NULL;
    }
    if (fNumIndices > 0) {
        fIndexData = new unsigned short[fNumIndices];
        S->readShorts(fNumIndices, (short*)fIndexData);
    } else {
        fIndexData = NULL;
    }
    fInstanceGroup = S->readInt();
    if (fInstanceGroup != 0) {
        throw "Incomplete";
        //fInstanceRefs = IGetInstanceGroup(fInstanceGroup, S->readInt());
        //fInstanceRefs->append(this);
    }
}

void plGeometrySpan::write(hsStream *S) {
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
        // this is hsPoint3[UVCount] + fPosition + fNormal.
        unsigned int size = ((fFormat & kUVCountMask) + 2) * sizeof(hsPoint3);
        if (fFormat & kSkinWeightMask == kSkin1Weight)
            size += 4;  // 1 float
        else if (fFormat & kSkinWeightMask == kSkin2Weights)
            size += 8;  // 2 floats
        else if (fFormat & kSkinWeightMask == kSkin3Weights)
            size += 12; // 3 floats
        if (fFormat & kSkinIndices)
            size += 4;  // uint32
        S->write(fNumVerts * size, fVertexData);
        
        for (unsigned int i=0; i<fNumVerts; i++) {
            fMultColor[i].write(S);
            fAddColor[i].write(S);
        }
        S->writeInts(fNumVerts, (int*)fDiffuseRGBA);
        S->writeInts(fNumVerts, (int*)fSpecularRGBA);
        
    }
    if (fNumIndices > 0) {
        S->writeShorts(fNumIndices, (short*)fIndexData);
    }
    S->writeInt(fInstanceGroup);
    if (fInstanceGroup != 0) {
        throw "Incomplete";
    }
}

void plGeometrySpan::setMaterial(hsGMaterial* mat) { fMaterial = mat; }

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
	fLocalToOBB.Identity();
    fOBBToLocal.Identity();
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
