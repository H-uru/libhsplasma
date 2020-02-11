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

#ifndef _PLGEOMETRYSPAN_H
#define _PLGEOMETRYSPAN_H

#include "PRP/Surface/hsGMaterial.h"
#include "Math/hsMatrix44.h"
#include "PRP/Misc/plFogEnvironment.h"
#include "PRP/Region/hsBounds.h"
#include "Sys/hsColor.h"
#include "Math/hsGeometry3.h"
#include "PRP/KeyedObject/plKey.h"

class PLASMA_DLL plGeometrySpan
{
public:
    enum
    {
        kMaxNumUVChannels = 8
    };

    enum Formats
    {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40
    };

    enum Properties
    {
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

    enum { kNoGroupID = 0 };

    struct PLASMA_DLL TempVertex
    {
        hsVector3 fPosition, fNormal;
        unsigned int fColor, fSpecularColor;
        hsColorRGBA fMultColor, fAddColor;
        hsVector3 fUVs[8];
        float fWeights[3];
        unsigned int fIndices;
    };

protected:
    plKey fMaterial, fFogEnviron;
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    hsBounds3Ext fLocalBounds, fWorldBounds;
    unsigned int fFormat, fNumMatrices;
    unsigned int fBaseMatrix;
    unsigned short fLocalUVWChans, fMaxBoneIdx;
    unsigned int fPenBoneIdx;
    float fMinDist, fMaxDist;
    float fWaterHeight;
    unsigned int fProps;
    unsigned int fNumVerts;
    std::vector<unsigned char> fVertexData;
    std::vector<unsigned short> fIndexData;
    unsigned int fDecalLevel;
    std::vector<hsColorRGBA> fMultColor;
    std::vector<hsColorRGBA> fAddColor;
    std::vector<unsigned int> fDiffuseRGBA;
    std::vector<unsigned int> fSpecularRGBA;
    unsigned int fInstanceGroup;
    hsMatrix44 fLocalToOBB, fOBBToLocal;

    unsigned int numInstanceRefs;

    std::vector<plKey> fPermaLights;
    std::vector<plKey> fPermaProjs;

public:
    plGeometrySpan()
        : fFormat(), fNumMatrices(), fBaseMatrix(), fLocalUVWChans(),
          fMaxBoneIdx(), fPenBoneIdx(), fMinDist(-1), fMaxDist(-1), fWaterHeight(),
          fProps(), fNumVerts(), fDecalLevel(), fInstanceGroup() { }

    static unsigned int CalcVertexSize(unsigned char format);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    std::vector<TempVertex> getVertices() const;
    void setVertices(const std::vector<TempVertex>& verts);
    unsigned short getIndex(size_t idx) const { return fIndexData[idx]; }
    std::vector<unsigned short> getIndices() const { return fIndexData; }
    void setIndices(const std::vector<unsigned short>& indices) { fIndexData = indices; }

    hsMatrix44 getLocalToWorld() const { return fLocalToWorld; }
    hsMatrix44 getWorldToLocal() const { return fWorldToLocal; }
    hsBounds3Ext getLocalBounds() const { return fLocalBounds; }
    hsBounds3Ext getWorldBounds() const { return fWorldBounds; }
    plKey getMaterial() const { return fMaterial; }
    plKey getFogEnvironment() const { return fFogEnviron; }
    float getMinDist() const { return fMinDist; }
    float getMaxDist() const { return fMaxDist; }
    float getWaterHeight() const { return fWaterHeight; }
    unsigned int getFormat() const { return fFormat; }
    unsigned int getNumMatrices() const { return fNumMatrices; }
    unsigned int getProps() const { return fProps; }
    unsigned int getNumVertices() const { return fNumVerts; }
    unsigned int getNumIndices() const { return fIndexData.size(); }
    unsigned int getBaseMatrix() const { return fBaseMatrix; }
    unsigned int getLocalUVWChans() const { return fLocalUVWChans; }
    unsigned int getMaxBoneIdx() const { return fMaxBoneIdx; }
    unsigned int getPenBoneIdx() const { return fPenBoneIdx; }

    void setLocalToWorld(const hsMatrix44& l2w) { fLocalToWorld = l2w; }
    void setWorldToLocal(const hsMatrix44& w2l) { fWorldToLocal = w2l; }
    void setLocalBounds(const hsBounds3Ext& bounds) { fLocalBounds = bounds; }
    void setWorldBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
    void setMaterial(plKey mat) { fMaterial = std::move(mat); }
    void setFogEnvironment(plKey fog) { fFogEnviron = std::move(fog); }
    void setMinDist(float dist) { fMinDist = dist; }
    void setMaxDist(float dist) { fMaxDist = dist; }
    void setWaterHeight(float height) { fWaterHeight = height; }
    void setFormat(unsigned int format) { fFormat = format; }
    void setNumMatrices(unsigned int num) { fNumMatrices = num; }
    void setProps(unsigned int props) { fProps = props; }
    void setBaseMatrix(unsigned int base) { fBaseMatrix = base; }
    void setLocalUVWChans(unsigned int chans) { fLocalUVWChans = chans; }
    void setMaxBoneIdx(unsigned int idx) { fMaxBoneIdx = idx; }
    void setPenBoneIdx(unsigned int idx) { fPenBoneIdx = idx; }

    const std::vector<plKey>& getPermaLights() const { return fPermaLights; }
    std::vector<plKey>& getPermaLights() { return fPermaLights; }
    void setPermaLights(const std::vector<plKey>& lights) { fPermaLights = lights; }
    void addPermaLight(plKey light) { fPermaLights.emplace_back(std::move(light)); }
    void delPermaLight(size_t idx) { fPermaLights.erase(fPermaLights.begin() + idx); }
    void clearPermaLights() { fPermaLights.clear(); }

    const std::vector<plKey>& getPermaProjs() const { return fPermaProjs; }
    std::vector<plKey>& getPermaProjs() { return fPermaProjs; }
    void setPermaProjs(const std::vector<plKey>& lights) { fPermaProjs = lights; }
    void addPermaProj(plKey light) { fPermaProjs.emplace_back(std::move(light)); }
    void delPermaProj(size_t idx) { fPermaProjs.erase(fPermaProjs.begin() + idx); }
    void clearPermaProjs() { fPermaProjs.clear(); }
};

#endif
