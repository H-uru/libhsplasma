#ifndef _PLSPAN_H
#define _PLSPAN_H

#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsBitVector.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"
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
        kNullSpan = 0x4,    // Don't actually know what this one is
        kParticleSpan = 0x8,
        kParticleSet = 0x10
    };

protected:
    unsigned short fTypeMask, fSubType;
    unsigned int fMaterialIdx;
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    unsigned int fBaseMatrix;
    unsigned char fNumMatrices;
    unsigned short fLocalUVWChans;
    unsigned short fMaxBoneIdx, fPenBoneIdx;
    unsigned int fProps;
    hsBounds3Ext fLocalBounds, fWorldBounds;
    plKey* fFogEnvironment;
    float fMinDist, fMaxDist, fWaterHeight;
    hsBitVector fVisSet, fVisNot;
    //plAccessSnapShot* fSnapShot;
    hsTArray<plLightInfo*> fLights, fProjectors;
    hsTArray<float> fLightStrengths, fLightScales;
    hsTArray<float> fProjStrengths, fProjScales;
    hsBitVector fShadowBits, fShadowSlaveBits;
    //hsTArray<plAuxSpan*> fAuxSpans;
    hsTArray<plKey*> fPermaLights, fPermaProjs;

public:
    plSpan();
    virtual ~plSpan();

    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);

    plKey* getFogEnvironment();
    hsTArray<plKey*>& getPermaLights();
    hsTArray<plKey*>& getPermaProjs();
    unsigned short getTypeMask();
    unsigned int getMaterialIdx();
    unsigned char getNumMatrices();
    unsigned int getProps();

    void setFogEnvironment(plKey* fog);
    void addPermaLight(plKey* light);
    void addPermaProj(plKey* proj);
};

#endif
