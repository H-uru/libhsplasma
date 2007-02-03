#ifndef _PLSPAN_H
#define _PLSPAN_H

#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsBitVector.h"
#include "../plPipeline/plFogEnvironment.h"
#include "../plGLight/plLightInfo.h"

class plSpan {
public:
    enum {
        kLiteMaterial = 0x0,
        kPropNoDraw = 0x1,
        kPropNoShadowCast = 0x2,
        kPropFacesSortable = 0x4,
        kPropVolatile = 0x8,
        kWaterHeight = 0x10,
        kPropRunTimeLight = 0x20,
        kPropReverseSort = 0x40,
        kPropHasPermaLights = 0x80,
        kPropHasPermaProjs = 0x100,
        kLiteVtxPreshaded = 0x200,
        kLiteVtxNonPreshaded = 0x400,
        kLiteProjection = 0x800,
        kLiteShadowErase = 0x1000,
        kLiteShadow = 0x2000,
        kPropMatHasSpecular = 0x10000,
        kPropProjAsVtx = 0x20000,
        kPropSkipProjection = 0x40000,
        kPropNoShadow = 0x80000,
        kPropForceShadow = 0x100000,
        kPropDisableNormal = 0x200000,
        kPropCharacter = 0x400000,
        kPartialSort = 0x800000,
        kVisLOS = 0x1000000
    };
    
    enum plSpanType {
        kSpan = 0x0,
        kVertexSpan = 0x1,
        kIcicleSpan = 0x2,
        kParticleSpan = 0x8,
        kParticleSet = 0x10
    };

protected:
    unsigned short typeMask, subType;
    unsigned int materialIdx;
    hsMatrix44 localToWorld, worldToLocal;
    unsigned int baseMatrix;
    unsigned char numMatrices;
    unsigned short localUVWChans;
    unsigned short maxBoneIdx, penBoneIdx;
    unsigned int props;
    hsBounds3Ext localBounds, worldBounds;
    plFogEnvironment* fogEnvironment;
    float minDist, maxDist, waterHeight;
    hsBitVector visSet, visNot;
    //plAccessSnapShot* snapShot;
    hsTArray<plLightInfo*> lights, projectors;
    hsTArray<float> lightStrengths, lightScales;
    hsTArray<float> projStrengths, projScales;
    hsBitVector shadowBits, shadowSlaveBits;
    //hsTArray<plAuxSpan*> auxSpans;
    hsTArray<plLightInfo*> permaLights, permaProjs;

public:
    plSpan();
    virtual ~plSpan();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

    unsigned short getTypeMask();
    unsigned int getMaterialIdx();
    unsigned char getNumMatrices();
    unsigned int getProps();
    void setFogEnviron(plKey* fog);
    void setPermaLight(plKey* light);
    void setPermaProj(plKey* proj);
};

#endif
