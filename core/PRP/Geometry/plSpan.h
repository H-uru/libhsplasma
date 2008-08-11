#ifndef _PLSPAN_H
#define _PLSPAN_H

#include "Math/hsMatrix44.h"
#include "PRP/Region/hsBounds.h"
#include "Util/hsBitVector.h"
#include "PRP/Misc/plFogEnvironment.h"
#include "PRP/Light/plLightInfo.h"

DllClass plSpan {
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
        kNullSpan = 0x4,
        kParticleSpan = 0x8,
        kParticleSet = 0x10
    };

protected:
    unsigned short fSubType;
    unsigned int fMaterialIdx;
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    unsigned int fBaseMatrix;
    unsigned char fNumMatrices;
    unsigned short fLocalUVWChans;
    unsigned short fMaxBoneIdx, fPenBoneIdx;
    unsigned int fProps;
    hsBounds3Ext fLocalBounds, fWorldBounds;
    plKey fFogEnvironment;
    float fMinDist, fMaxDist, fWaterHeight;
    hsTArray<plKey> fPermaLights, fPermaProjs;

public:
    plSpan();
    plSpan(const plSpan& init);
    virtual ~plSpan();

    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

    plKey getFogEnvironment() const;
    const hsTArray<plKey>& getPermaLights() const;
    const hsTArray<plKey>& getPermaProjs() const;
    hsMatrix44 getLocalToWorld() const;
    hsMatrix44 getWorldToLocal() const;
    unsigned short getSubType() const;
    unsigned int getMaterialIdx() const;
    unsigned char getNumMatrices() const;
    unsigned int getProps() const;
    unsigned int getBaseMatrix() const;
    unsigned short getMaxBoneIdx() const;
    unsigned short getPenBoneIdx() const;
    unsigned short getLocalUVWChans() const;
    float getMinDist() const;
    float getMaxDist() const;
    float getWaterHeight() const;
    hsBounds3Ext& getLocalBounds();
    hsBounds3Ext& getWorldBounds();

    void setFogEnvironment(plKey fog);
    void clearPermaLights();
    void addPermaLight(plKey light);
    void clearPermaProjs();
    void addPermaProj(plKey proj);
    void setLocalToWorld(hsMatrix44 l2w);
    void setWorldToLocal(hsMatrix44 w2l);
    void setSubType(unsigned short type);
    void setMaterialIdx(unsigned int idx);
    void setNumMatrices(unsigned char mats);
    void setProps(unsigned int props);
    void setBaseMatrix(unsigned int mat);
    void getMaxBoneIdx(unsigned short idx);
    void getPenBoneIdx(unsigned short idx);
    void getLocalUVWChans(unsigned short chans);
    void getMinDist(float dist);
    void getMaxDist(float dist);
    void getWaterHeight(float height);
};

#endif
