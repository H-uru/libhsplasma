/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLSPAN_H
#define _PLSPAN_H

#include "Math/hsMatrix44.h"
#include "PRP/Region/hsBounds.h"
#include "Util/hsBitVector.h"
#include "PRP/Misc/plFogEnvironment.h"
#include "PRP/Light/plLightInfo.h"
#include "plGeometrySpan.h"

class PLASMA_DLL plSpan
{
public:
    enum
    {
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

    enum plSpanType
    {
        kSpan = 0x0,
        kVertexSpan = 0x1,
        kIcicleSpan = 0x2,
        kNullSpan = 0x4,
        kParticleSpan = 0x8,
        kParticleSet = 0x10
    };

public:
    static uint32_t deswizzleGeoFlags(uint32_t flags);
    static uint32_t swizzleGeoFlags(uint32_t flags);

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
    std::vector<plKey> fPermaLights, fPermaProjs;

public:
    virtual const char* ClassName() const { return "plSpan"; }

    plSpan()
        : fSubType(kVertexSpan), fMaterialIdx(), fBaseMatrix(), fNumMatrices(),
          fLocalUVWChans(), fMaxBoneIdx(), fPenBoneIdx(), fProps(), fMinDist(),
          fMaxDist(), fWaterHeight() { }

    plSpan(const plSpan& init)
        : fSubType(init.fSubType), fMaterialIdx(init.fMaterialIdx),
          fLocalToWorld(init.fLocalToWorld), fWorldToLocal(init.fWorldToLocal),
          fBaseMatrix(init.fBaseMatrix), fNumMatrices(init.fNumMatrices),
          fLocalUVWChans(init.fLocalUVWChans), fMaxBoneIdx(init.fMaxBoneIdx),
          fPenBoneIdx(init.fPenBoneIdx), fProps(init.fProps),
          fLocalBounds(init.fLocalBounds), fWorldBounds(init.fWorldBounds),
          fFogEnvironment(init.fFogEnvironment), fMinDist(init.fMinDist),
          fMaxDist(init.fMaxDist), fWaterHeight(init.fWaterHeight),
          fPermaLights(init.fPermaLights), fPermaProjs(init.fPermaProjs) { }

    virtual ~plSpan() { }

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    plKey getFogEnvironment() const { return fFogEnvironment; }
    hsMatrix44 getLocalToWorld() const { return fLocalToWorld; }
    hsMatrix44 getWorldToLocal() const { return fWorldToLocal; }
    unsigned short getSubType() const { return fSubType; }
    unsigned int getMaterialIdx() const { return fMaterialIdx; }
    unsigned char getNumMatrices() const { return fNumMatrices; }
    unsigned int getProps() const { return fProps; }
    unsigned int getBaseMatrix() const { return fBaseMatrix; }
    unsigned short getMaxBoneIdx() const { return fMaxBoneIdx; }
    unsigned short getPenBoneIdx() const { return fPenBoneIdx; }
    unsigned short getLocalUVWChans() const { return fLocalUVWChans; }
    float getMinDist() const { return fMinDist; }
    float getMaxDist() const { return fMaxDist; }
    float getWaterHeight() const { return fWaterHeight; }
    const hsBounds3Ext& getLocalBounds() const { return fLocalBounds; }
    const hsBounds3Ext& getWorldBounds() const { return fWorldBounds; }

    void setFogEnvironment(plKey fog) { fFogEnvironment = std::move(fog); }
    void setLocalToWorld(hsMatrix44 l2w) { fLocalToWorld = l2w; }
    void setWorldToLocal(hsMatrix44 w2l) { fWorldToLocal = w2l; }
    void setSubType(unsigned short type) { fSubType = type; }
    void setMaterialIdx(unsigned int idx) { fMaterialIdx = idx; }
    void setNumMatrices(unsigned char mats) { fNumMatrices = mats; }
    void setProps(unsigned int props) { fProps = props; }
    void setBaseMatrix(unsigned int mat) { fBaseMatrix = mat; }
    void setMaxBoneIdx(unsigned short idx) { fMaxBoneIdx = idx; }
    void setPenBoneIdx(unsigned short idx) { fPenBoneIdx = idx; }
    void setLocalUVWChans(unsigned short chans) { fLocalUVWChans = chans; }
    void setMinDist(float dist) { fMinDist = dist; }
    void setMaxDist(float dist) { fMaxDist = dist; }
    void setWaterHeight(float height) { fWaterHeight = height; }
    void setLocalBounds(const hsBounds3Ext& bounds) { fLocalBounds = bounds; }
    void setWorldBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }

    const std::vector<plKey>& getPermaLights() const { return fPermaLights; }
    std::vector<plKey>& getPermaLights() { return fPermaLights; }
    void setPermaLights(const std::vector<plKey>& lights) { fPermaLights = lights; }
    void addPermaLight(plKey light) { fPermaLights.emplace_back(std::move(light)); }
    void delPermaLight(size_t idx) { fPermaLights.erase(fPermaLights.begin() + idx); }
    void clearPermaLights() { fPermaLights.clear(); }

    const std::vector<plKey>& getPermaProjs() const { return fPermaProjs; }
    std::vector<plKey>& getPermaProjs() { return fPermaProjs; }
    void setPermaProjs(const std::vector<plKey>& lights) { fPermaProjs = lights; }
    void addPermaProj(plKey proj) { fPermaProjs.emplace_back(std::move(proj)); }
    void delPermaProj(size_t idx) { fPermaProjs.erase(fPermaProjs.begin() + idx); }
    void clearPermaProjs() { fPermaProjs.clear(); }
};

#endif
