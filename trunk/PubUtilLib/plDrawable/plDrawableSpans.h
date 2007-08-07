#ifndef _PLDRAWABLESPANS_H
#define _PLDRAWABLESPANS_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/plRenderLevel.h"
#include "../plSurface/hsGMaterial.h"
#include "../plPipeline/plGBufferGroup.h"
#include "plSpaceTree.h"
#include "plIcicle.h"
#include "plGeometrySpan.h"

class plDISpanIndex {
public:
    enum {
        kNone = 0x0,
        kMatrixOnly = 0x1,
        kDontTransformSpans = 0x2
    };

    unsigned char flags;
    hsTArray<unsigned int> indices;
};

class plDrawable : public hsKeyedObject {
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


class plDrawableSpans : public plDrawable {
protected:
    unsigned int type;
    bool readyToRender;
    hsBounds3Ext localBounds, worldBounds, maxWorldBounds;
    hsMatrix44 localToWorld, worldToLocal;
    hsTArray<hsMatrix44> localToWorlds, worldToLocals;
    hsTArray<hsMatrix44> localToBones, boneToLocals;
    hsTArray<plKey*> materials;
    plSpaceTree* spaceTree;
    hsBitVector fVisSet, fVisNot, fLastVisSet, fLastVisNot, fVisCache;
    hsTArray<plIcicle> icicles;
    hsTArray<plParticleSpan> particleSpans;
    hsTArray<plSpan*> spans;
    hsTArray<unsigned int> spanSourceIndices;
    hsTArray<plGBufferGroup*> groups;
    hsTArray<plDISpanIndex*> DIIndices;
    unsigned int props, criteria;
    plRenderLevel renderLevel;
    //plLoadMask loadMask;
    bool registeredForRecreate, needCleanup, registeredForRender;
    hsBitVector particleSpanVector, blendingSpanVector, fakeBlendingSpanVector;
    plKey* sceneNode;
    bool settingMatIdxLock;
    unsigned int skinTime;
    hsTArray<plGeometrySpan*> sourceSpans;
    bool optimized;

public:
    plDrawableSpans();
    virtual ~plDrawableSpans();

    DECLARE_CREATABLE(plDrawableSpans)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
