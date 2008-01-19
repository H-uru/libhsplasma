#ifndef _PLSPACETREE_H
#define _PLSPACETREE_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "CoreLib/hsTArray.hpp"
#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsBounds.h"
#include "CoreLib/hsBitVector.h"

DllClass plSpaceTreeNode {
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
};

DllClass plSpaceTree : public plCreatable {
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
    plSpaceTree();
    virtual ~plSpaceTree();
    
    DECLARE_CREATABLE(plSpaceTree);
    
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
