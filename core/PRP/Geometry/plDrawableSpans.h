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

#ifndef _PLDRAWABLESPANS_H
#define _PLDRAWABLESPANS_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Misc/plRenderLevel.h"
#include "PRP/Surface/hsGMaterial.h"
#include "plGBufferGroup.h"
#include "plGeometrySpan.h"
#include "plSpaceTree.h"
#include "plIcicle.h"
#include "plGeometrySpan.h"
#include <vector>
#include <list>

class PLASMA_DLL plDISpanIndex
{
public:
    enum
    {
        kNone = 0x0,
        kMatrixOnly = 0x1,
        kDontTransformSpans = 0x2
    };

    uint8_t fFlags;
    std::vector<unsigned int> fIndices;

public:
    plDISpanIndex() : fFlags() { }
    plDISpanIndex(const plDISpanIndex& init)
        : fFlags(init.fFlags), fIndices(init.fIndices) { }
    plDISpanIndex& operator=(const plDISpanIndex& cpy);
};


class PLASMA_DLL plDrawable : public hsKeyedObject
{
    CREATABLE(plDrawable, kDrawable, hsKeyedObject)

public:
    enum
    {
        kPropNoDraw = 0x1,
        kPropUNUSED = 0x2,
        kPropSortSpans = 0x4,
        kPropSortFaces = 0x8,
        kPropVolatile = 0x10,
        kPropNoReSort = 0x20,
        kPropPartialSort = 0x40,
        kPropCharacter = 0x80,
        kPropSortAsOne = 0x100,
        kPropHasVisLOS = 0x200
    };

    enum
    {
        kCritStatic = 0x1,
        kCritSortSpans = 0x2,
        kCritSortFaces = 0x8,
        kCritCharacter = 0x10
    };

    enum plDrawableType
    {
        kNormal = 0x1,
        kNonDrawable = 0x2,
        kEnviron = 0x4,
        kLightProxy = 0x10000,
        kOccluderProxy = 0x20000,
        kAudibleProxy = 0x40000,
        kPhysicalProxy = 0x80000,
        kCoordinateProxy = 0x100000,
        kOccSnapProxy = 0x200000,
        kGenericProxy = 0x400000,
        kCameraProxy = 0x800000,
        kAllProxies = 0xFF0000,
        kAllTypes = 0x0000FF
    };

    enum plSubDrawableType
    {
        kSubNormal = 0x1,
        kSubNonDrawable = 0x2,
        kSubEnviron = 0x4,
        kSubAllTypes = 0xFF
    };

    static const unsigned int kSpanTypeMask = 0xC0000000;
    static const unsigned int kSpanIDMask = 0x3FFFFFFF;
    static const unsigned int kSpanTypeIcicle = 0x00000000;
    static const unsigned int kSpanTypeUnknown = 0x80000000;
    static const unsigned int kSpanTypeParticleSpan = 0xC0000000;
};


class PLASMA_DLL plDrawableSpans : public plDrawable
{
    CREATABLE(plDrawableSpans, kDrawableSpans, plDrawable)

protected:
    hsBounds3Ext fLocalBounds, fWorldBounds, fMaxWorldBounds;
    std::vector<hsMatrix44> fLocalToWorlds, fWorldToLocals;
    std::vector<hsMatrix44> fLocalToBones, fBoneToLocals;
    std::vector<plKey> fMaterials;
    plSpaceTree* fSpaceTree;
    std::vector<plIcicle*> fIcicles;
    std::vector<plParticleSpan*> fParticleSpans;
    std::vector<plSpan*> fSpans;
    std::vector<unsigned int> fSpanSourceIndices;
    std::vector<plGBufferGroup*> fGroups;
    std::vector<plDISpanIndex> fDIIndices;
    unsigned int fProps, fCriteria;
    unsigned int fRenderLevel;
    plKey fSceneNode;
    std::vector<plGeometrySpan*> fSourceSpans;

public:
    plDrawableSpans() : fSpaceTree(), fProps(), fCriteria(), fRenderLevel() { }
    ~plDrawableSpans();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    void calcBounds();
    void BuildSpaceTree();

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

    plSpaceBuilderNode* IBuildTree(std::vector<plSpaceBuilderNode*>& nodes);
    void ISplitSpace(std::vector<plSpaceBuilderNode*>& nodes,
                     std::vector<plSpaceBuilderNode*>& left,
                     std::vector<plSpaceBuilderNode*>& right);
    void ISortSpace(std::vector<plSpaceBuilderNode*>& nodes, int axis);

    /**
     * Finds a buffer group with enough space for the requested amount of vertices.
     */
    size_t IFindBufferGroup(unsigned int format, unsigned int vertsNeeded);

public:
    size_t getNumSpans() const { return fSpans.size(); }
    plSpan* getSpan(size_t idx) const { return fSpans[idx]; }
    plIcicle* getIcicle(size_t idx) const { return (plIcicle*)fSpans[idx]; }
    size_t addIcicle(plIcicle* span);
    void clearSpans();

    size_t getNumBufferGroups() const { return fGroups.size(); }
    plGBufferGroup* getBuffer(size_t group) const { return fGroups[group]; }
    size_t createBufferGroup(unsigned char format);
    void deleteBufferGroup(size_t group);
    std::vector<plGBufferVertex> getVerts(const plIcicle* span) const;
    std::vector<unsigned short> getIndices(const plIcicle* span) const;
    std::vector<plGBufferCell> getCells(size_t group, size_t buffer) const;
    void addVerts(size_t group, const std::vector<plGBufferVertex>& verts);
    void addIndices(size_t group, const std::vector<unsigned short>& indices);
    void addCells(size_t group, const std::vector<plGBufferCell>& cells);

    size_t getNumDIIndices() const { return fDIIndices.size(); }
    const plDISpanIndex& getDIIndex(size_t idx) const { return fDIIndices[idx]; }
    plDISpanIndex& getDIIndex(size_t idx) { return fDIIndices[idx]; }
    const std::vector<plDISpanIndex>& getDIIndices() const { return fDIIndices; }
    std::vector<plDISpanIndex>& getDIIndices() { return fDIIndices; }
    size_t addDIIndex(const plDISpanIndex& idx);
    void delDIIndex(size_t idx) { fDIIndices.erase(fDIIndices.begin() + idx); }
    void clearDIIndices() { fDIIndices.clear(); }

    size_t getNumTransforms() const { return fLocalToWorlds.size(); }
    hsMatrix44 getLocalToWorld(size_t idx) const { return fLocalToWorlds[idx]; }
    hsMatrix44 getWorldToLocal(size_t idx) const { return fWorldToLocals[idx]; }
    hsMatrix44 getLocalToBone(size_t idx) const { return fLocalToBones[idx]; }
    hsMatrix44 getBoneToLocal(size_t idx) const { return fBoneToLocals[idx]; }
    void clearTransforms();
    size_t addTransform(const hsMatrix44& l2w, const hsMatrix44& w2l,
                        const hsMatrix44& l2b, const hsMatrix44& b2l);

    const hsBounds3Ext& getLocalBounds() { return fLocalBounds; }
    const hsBounds3Ext& getWorldBounds() { return fWorldBounds; }
    const hsBounds3Ext& getMaxWorldBounds() { return fMaxWorldBounds; }
    void setLocalBounds(const hsBounds3Ext& bounds) { fLocalBounds = bounds; }
    void setWorldBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
    void setMaxWorldBounds(const hsBounds3Ext& bounds) { fMaxWorldBounds = bounds; }

    const std::vector<plKey>& getMaterials() const { return fMaterials; }
    std::vector<plKey>& getMaterials() { return fMaterials; }
    void addMaterial(plKey mat) { fMaterials.emplace_back(std::move(mat)); }
    void clearMaterials() { fMaterials.clear(); }

    plSpaceTree* getSpaceTree() const { return fSpaceTree; }
    void setSpaceTree(plSpaceTree* tree);

    unsigned int getProps() const { return fProps; }
    unsigned int getCriteria() const { return fCriteria; }
    unsigned int getRenderLevel() const { return fRenderLevel; }
    plKey getSceneNode() const { return fSceneNode; }
    void setProps(unsigned int props) { fProps = props; }
    void setCriteria(unsigned int crit) { fCriteria = crit; }
    void setRenderLevel(unsigned int level) { fRenderLevel = level; }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }

    void composeGeometry(bool clearspans=true, bool calcbounds=false);
    void decomposeGeometry(bool clearcolors=false);
    size_t buildDIIndex(const std::vector<plGeometrySpan*>& spans);

    const std::vector<plGeometrySpan*>& getSourceSpans() const { return fSourceSpans; }
    std::vector<plGeometrySpan*>& getSourceSpans() { return fSourceSpans; }
    size_t addSourceSpan(plGeometrySpan* span);
};

#endif
