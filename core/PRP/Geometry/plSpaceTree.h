#ifndef _PLSPACETREE_H
#define _PLSPACETREE_H

#include "PRP/plCreatable.h"
#include "Util/hsTArray.hpp"
#include "Math/hsGeometry3.h"
#include "PRP/Region/hsBounds.h"
#include "Util/hsBitVector.h"

DllClass plSpaceTreeNode {
public:
    enum {
        kNone = 0,
        kIsLeaf = 0x1,
        kDirty = 0x2,
        kDisabled = 0x4,
        kEmpty = 0x8,
        kEnabledTemp = 0x10
    };

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
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plSpaceTree : public plCreatable {
protected:
    enum plHarvestFlags {
        kNone,
        kSortBackToFront,
        kSortFrontToBack
    };
    
    hsTArray<plSpaceTreeNode> fTree;
    short fRoot, fNumLeaves;

public:
    plSpaceTree();
    virtual ~plSpaceTree();
    
    DECLARE_CREATABLE(plSpaceTree);
    
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
