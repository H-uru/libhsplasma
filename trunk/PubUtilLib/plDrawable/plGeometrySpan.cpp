#include "plGeometrySpan.h"

plGeometrySpan::plGeometrySpan(PlasmaVer pv) { }
plGeometrySpan::~plGeometrySpan() { }

void plGeometrySpan::read(hsStream *S) {
	//ClearBuffers();
    localToWorld.read(S);
    worldToLocal.read(S);
    localBounds.read(S);
    //if (worldBounds != localBounds)
    //    worldBounds.Reset(localBounds);
    //worldBounds.Transform(&localToWorld);
    OBBToLocal.read(S);
    localToOBB.read(S);
    
    baseMatrix = S->readInt();
    numMatrices = S->readByte();
    localUVWChans = S->readShort();
    maxBoneIdx = S->readShort();
    penBoneIdx = S->readShort();
    minDist = S->readFloat();
    maxDist = S->readFloat();
    format = S->readByte();
    props = S->readInt();
    numVerts = S->readInt();
    numIndices = S->readInt();
    S->readInt();  // Discarded
    S->readByte(); // Discarded
    decalLevel = S->readInt();
    
    if (props & kWaterHeight)
        waterHeight = S->readFloat();
    
    if (numVerts > 0) {
        // this is hsPoint3[UVCount] + position + normal.
        unsigned int size = ((format & kUVCountMask) + 2) * sizeof(hsPoint3);
        if (format & kSkinWeightMask == kSkin1Weight)
            size += 4;  // 1 float
        else if (format & kSkinWeightMask == kSkin2Weights)
            size += 8;  // 2 floats
        else if (format & kSkinWeightMask == kSkin3Weights)
            size += 12; // 3 floats
        if (format & kSkinIndices)
            size += 4;  // uint32
        vertexData = (unsigned char*)malloc(numVerts * size);
        S->read(numVerts * size, vertexData);
        
        multColor = new hsColorRGBA[numVerts];
        addColor = new hsColorRGBA[numVerts];
        for (unsigned int i=0; i<numVerts; i++) {
            multColor[i].read(S);
            addColor[i].read(S);
        }
        diffuseRGBA = new unsigned int[numVerts];
        specularRGBA = new unsigned int[numVerts];
        S->readInts(numVerts, (int*)diffuseRGBA);
        S->readInts(numVerts, (int*)specularRGBA);
    } else {
        vertexData = NULL;
        multColor = NULL;
        addColor = NULL;
        diffuseRGBA = NULL;
        specularRGBA = NULL;
    }
    if (numIndices > 0) {
        indexData = new unsigned short[numIndices];
        S->readShorts(numIndices, (short*)indexData);
    } else {
        indexData = NULL;
    }
    instanceGroup = S->readInt();
    if (instanceGroup != 0) {
        throw "Incomplete";
        //instanceRefs = IGetInstanceGroup(instanceGroup, S->readInt());
        //instanceRefs->append(this);
    }
}

void plGeometrySpan::write(hsStream *S) {
    localToWorld.write(S);
    worldToLocal.write(S);
    localBounds.write(S);
    OBBToLocal.write(S);
    localToOBB.write(S);
    
    S->writeInt(baseMatrix);
    S->writeByte(numMatrices);
    S->writeShort(localUVWChans);
    S->writeShort(maxBoneIdx);
    S->writeShort(penBoneIdx);
    S->writeFloat(minDist);
    S->writeFloat(maxDist);
    S->writeByte(format);
    S->writeInt(props);
    S->writeInt(numVerts);
    S->writeInt(numIndices);
    S->writeInt(0);
    S->writeByte(0);
    S->writeInt(decalLevel);
    
    if (props & kWaterHeight)
        S->writeFloat(waterHeight);
    
    if (numVerts > 0) {
        // this is hsPoint3[UVCount] + position + normal.
        unsigned int size = ((format & kUVCountMask) + 2) * sizeof(hsPoint3);
        if (format & kSkinWeightMask == kSkin1Weight)
            size += 4;  // 1 float
        else if (format & kSkinWeightMask == kSkin2Weights)
            size += 8;  // 2 floats
        else if (format & kSkinWeightMask == kSkin3Weights)
            size += 12; // 3 floats
        if (format & kSkinIndices)
            size += 4;  // uint32
        S->write(numVerts * size, vertexData);
        
        for (unsigned int i=0; i<numVerts; i++) {
            multColor[i].write(S);
            addColor[i].write(S);
        }
        S->writeInts(numVerts, (int*)diffuseRGBA);
        S->writeInts(numVerts, (int*)specularRGBA);
        
    }
    if (numIndices > 0) {
        S->writeShorts(numIndices, (short*)indexData);
    }
    S->writeInt(instanceGroup);
    if (instanceGroup != 0) {
        throw "Incomplete";
    }
}

void plGeometrySpan::setMaterial(hsGMaterial* mat) { material = mat; }

#ifdef Tahg
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
}
#endif
