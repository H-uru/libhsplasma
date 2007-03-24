#ifndef _PLSPACETREE_H
#define _PLSPACETREE_H

#include "../../NucleusLib/pnFactory/plCreatable.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsBitVector.h"

class plSpaceTreeNode {
protected:
    hsBounds3Ext fWorldBounds;
    unsigned short fFlags;
    short fParent;
    
    union {
        short fChildren[2];
        short fLeafIndex;
    };
    
public:
    plSpaceTreeNode();
    ~plSpaceTreeNode();
    
    void read(hsStream* S);
    void write(hsStream* S);
};

class plSpaceTree : public plCreatable {
protected:
    enum plHarvestFlags {
        kNone,
        kSortBackToFront,
        kSortFrontToBack
    };
    
    hsTArray<plSpaceTreeNode> fTree;
    const hsBitVector* fCache;
    short fRoot;
    short fNumLeaves;
    unsigned short fHarvestFlags;
    //plVolumeIsect* fCullFunc;
    hsPoint3 fViewPos;

public:
    plSpaceTree(PlasmaVer pv = pvUnknown);
    virtual ~plSpaceTree();
    
    virtual short ClassIndex();
    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
