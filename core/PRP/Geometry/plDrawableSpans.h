#ifndef _PLDRAWABLESPANS_H
#define _PLDRAWABLESPANS_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Misc/plRenderLevel.h"
#include "PRP/Surface/hsGMaterial.h"
#include "plGBufferGroup.h"
#include "plSpaceTree.h"
#include "plIcicle.h"
#include "plGeometrySpan.h"

DllClass plDISpanIndex {
public:
    enum {
        kNone = 0x0,
        kMatrixOnly = 0x1,
        kDontTransformSpans = 0x2
    };

    unsigned char fFlags;
    hsTArray<unsigned int> fIndices;

public:
    plDISpanIndex();
    plDISpanIndex(const plDISpanIndex& init);
    plDISpanIndex& operator=(const plDISpanIndex& cpy);
};

DllClass plDrawable : public hsKeyedObject {
public:
    enum {
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
    
    enum {
        kCritStatic = 0x1,
        kCritSortSpans = 0x2,
        kCritSortFaces = 0x8,
        kCritCharacter = 0x10
    };
    
    enum plDrawableType {
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
    
    enum plSubDrawableType {
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

public:
    plDrawable();
    virtual ~plDrawable();

    DECLARE_CREATABLE(plDrawable)
};


DllClass plDrawableSpans : public plDrawable {
protected:
    hsBounds3Ext fLocalBounds, fWorldBounds, fMaxWorldBounds;
    hsTArray<hsMatrix44> fLocalToWorlds, fWorldToLocals;
    hsTArray<hsMatrix44> fLocalToBones, fBoneToLocals;
    hsTArray<plKey> fMaterials;
    plSpaceTree* fSpaceTree;
    hsTArray<plIcicle> fIcicles;
    hsTArray<plParticleSpan> fParticleSpans;
    hsTArray<plSpan*> fSpans;
    hsTArray<unsigned int> fSpanSourceIndices;
    hsTArray<plGBufferGroup*> fGroups;
    hsTArray<plDISpanIndex> fDIIndices;
    unsigned int fProps, fCriteria;
    plRenderLevel fRenderLevel;
    plWeakKey fSceneNode;
    hsTArray<plGeometrySpan*> fSourceSpans;

public:
    plDrawableSpans();
    virtual ~plDrawableSpans();

    DECLARE_CREATABLE(plDrawableSpans)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumSpans() const;
    plSpan* getSpan(size_t idx) const;
    void clearSpans();
    size_t addIcicle(const plIcicle& span);

    size_t getNumBufferGroups() const;
    plGBufferGroup* getBuffer(size_t group) const;
    size_t createBufferGroup(unsigned char format);
    void deleteBufferGroup(size_t group);
    hsTArray<plGBufferVertex> getVerts(const plIcicle* span) const;
    hsTArray<unsigned short> getIndices(const plIcicle* span) const;
    hsTArray<plGBufferCell> getCells(size_t group, size_t buffer) const;
    void addVerts(size_t group, const hsTArray<plGBufferVertex>& verts);
    void addIndices(size_t group, const hsTArray<unsigned short>& indices);
    void addCells(size_t group, const hsTArray<plGBufferCell>& cells);

    size_t getNumDIIndices() const;
    const plDISpanIndex& getDIIndex(size_t idx) const;
    void clearDIIndices();
    void addDIIndex(const plDISpanIndex& idx);

    size_t getNumTransforms() const;
    hsMatrix44 getLocalToWorld(size_t idx) const;
    hsMatrix44 getWorldToLocal(size_t idx) const;
    hsMatrix44 getLocalToBone(size_t idx) const;
    hsMatrix44 getBoneToLocal(size_t idx) const;
    void clearTransforms();
    void addTransform(const hsMatrix44& l2w, const hsMatrix44& w2l,
                      const hsMatrix44& l2b, const hsMatrix44& b2l);

    const hsBounds3Ext& getLocalBounds();
    const hsBounds3Ext& getWorldBounds();
    const hsBounds3Ext& getMaxWorldBounds();
    void setLocalBounds(const hsBounds3Ext& bounds);
    void setWorldBounds(const hsBounds3Ext& bounds);
    void setMaxWorldBounds(const hsBounds3Ext& bounds);

    size_t getNumMaterials() const;
    plKey getMaterial(size_t idx) const;
    void clearMaterials();
    void addMaterial(plKey mat);

    plSpaceTree* getSpaceTree() const;
    void setSpaceTree(plSpaceTree* tree);

    unsigned int getProps() const;
    unsigned int getCriteria() const;
    plRenderLevel getRenderLevel() const;
    plWeakKey getSceneNode() const;
    void setProps(unsigned int props);
    void setCriteria(unsigned int crit);
    void setRenderLevel(plRenderLevel level);
    void setSceneNode(plWeakKey node);
};

#endif
