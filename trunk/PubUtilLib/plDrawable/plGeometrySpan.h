#ifndef _PLGEOMETRYSPAN_H
#define _PLGEOMETRYSPAN_H

#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../plSurface/hsGMaterial.h"
#include "../../CoreLib/hsMatrix44.h"
#include "../plPipeline/plFogEnvironment.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsColor.h"
#include "../../CoreLib/hsGeometry3.h"

class plGeometrySpan {
public:
    enum {
        kMaxNumUVChannels = 8
    };

    enum Formats {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40
    };

    enum Properties {
        kLiteMaterial = 0x0,
        kPropRunTimeLight = 0x1,
        kPropNoPreShade = 0x2,
        kLiteVtxPreshaded = 0x4,
        kLiteVtxNonPreshaded = 0x8,
        kLiteMask = 0xC,
        kRequiresBlending = 0x10,
        kInstanced = 0x20,
        kUserOwned = 0x40,
        kPropNoShadow = 0x80,
        kPropForceShadow = 0x100,
        kDiffuseFoldedIn = 0x200,
        kPropReverseSort = 0x400,
        kWaterHeight = 0x800,
        kFirstInstance = 0x1000,
        kPartialSort = 0x2000,
        kVisLOS = 0x4000,
        kPropNoShadowCast = 0x8000
    };

    enum {
        kNoGroupID = 0
    };

    struct TempVertex {
        hsPoint3 fPosition;
        hsPoint3 fNormal;
        unsigned int fColor;
        unsigned int fSpecularColor;
        hsColorRGBA fMultColor;
        hsColorRGBA fAddColor;
        hsPoint3 fUVs[8];
        float fWeights[3];
        unsigned int fIndices;
    };

protected:
    hsGMaterial* material;
    hsMatrix44 localToWorld;
    hsMatrix44 worldToLocal;
    hsBounds3Ext localBounds;
    hsBounds3Ext worldBounds;
    plFogEnvironment* fogEnviron;
    unsigned int baseMatrix;
    unsigned char numMatrices;
    unsigned short localUVWChans;
    unsigned short maxBoneIdx;
    unsigned int penBoneIdx;
    float minDist;
    float maxDist;
    float waterHeight;
    unsigned char format;
    unsigned int props;
    unsigned int numVerts;
    unsigned int numIndices;
    unsigned char* vertexData;
    unsigned short* indexData;
    unsigned int decalLevel;
    hsColorRGBA* multColor;
    hsColorRGBA* addColor;
    unsigned int* diffuseRGBA;
    unsigned int* specularRGBA;
    hsTArray<plGeometrySpan*>* instanceRefs;
    unsigned int instanceGroup;
    unsigned char* maxOwner;
    unsigned int spanRefIndex;
    hsMatrix44 localToOBB;
    hsMatrix44 OBBToLocal;
    bool creating;
    hsTArray<TempVertex> vertAccum;
    hsTArray<unsigned short> indexAccum;
    
public:
    plGeometrySpan(PlasmaVer pv = pvUnknown);
    virtual ~plGeometrySpan();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    void setMaterial(hsGMaterial* mat);

#ifdef Tahg
    void IClearMembers();
    void ClearBuffers();
#endif
};

#endif
