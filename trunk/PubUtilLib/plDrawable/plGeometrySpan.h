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
    hsGMaterial* fMaterial;
    hsMatrix44 fLocalToWorld;
    hsMatrix44 fWorldToLocal;
    hsBounds3Ext fLocalBounds;
    hsBounds3Ext fWorldBounds;
    plFogEnvironment* fFogEnviron;
    unsigned int fBaseMatrix;
    unsigned char fNumMatrices;
    unsigned short fLocalUVWChans;
    unsigned short fMaxBoneIdx;
    unsigned int fPenBoneIdx;
    float fMinDist;
    float fMaxDist;
    float fWaterHeight;
    unsigned char fFormat;
    unsigned int fProps;
    unsigned int fNumVerts;
    unsigned int fNumIndices;
    unsigned char* fVertexData;
    unsigned short* fIndexData;
    unsigned int fDecalLevel;
    hsColorRGBA* fMultColor;
    hsColorRGBA* fAddColor;
    unsigned int* fDiffuseRGBA;
    unsigned int* fSpecularRGBA;
    hsTArray<plGeometrySpan*>* fInstanceRefs;
    unsigned int fInstanceGroup;
    unsigned char* fMaxOwner;
    unsigned int fSpanRefIndex;
    hsMatrix44 fLocalToOBB;
    hsMatrix44 fOBBToLocal;
    bool fCreating;
    hsTArray<TempVertex> fVertAccum;
    hsTArray<unsigned short> fIndexAccum;
    
public:
    plGeometrySpan();
    virtual ~plGeometrySpan();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    void setMaterial(hsGMaterial* mat);
    void setFogEnvironment(plFogEnvironment* fog);

    void IClearMembers();
    void ClearBuffers();
};

#endif
