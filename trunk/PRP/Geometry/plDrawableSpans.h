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
    
    enum plAccessFlags {
        kReadSrc = 0x1,
        kWriteDst = 0x2,
        kWriteSrc = 0x4
    };
    
    enum MsgTypes { kMsgMaterial, kMsgDISpans, kMsgFogEnviron, kMsgPermaLight,
                    kMsgPermaProj, kMsgPermaLightDI, kMsgPermaProjDI };
    
    static const unsigned int kSpanTypeMask = 0xC0000000;
    static const unsigned int kSpanIDMask = 0x3FFFFFFF;
    static const unsigned int kSpanTypeIcicle = 0x00000000;
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
    hsTArray<plDISpanIndex*> fDIIndices;
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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    void VertexWrite(hsStream* S, int index);
};

#endif
