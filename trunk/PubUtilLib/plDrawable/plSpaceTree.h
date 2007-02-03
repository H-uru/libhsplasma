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

#ifdef Tahg
    short GetChild(int);
    short GetParent();
    short GetLeaf();
    int plSpaceTreeNode::IsLeaf();
    const hsBounds3Ext & GetWorldBounds();
    friend class plSpaceTree;
#endif
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
    plSpaceTree();
    virtual ~plSpaceTree();
    
    virtual short ClassIndex();
    
    void read(hsStream* S);
    void write(hsStream* S);

#ifdef Tahg
    static unsigned short Index();
    static class plSpaceTree * Create();
    static const class plSpaceTree * ConvertNoRef(const class plCreatable *);
    static class plSpaceTree * plSpaceTree::ConvertNoRef(class plCreatable *);
    static class plSpaceTree * Convert(class plCreatable *);
    static int HasDerivedClass(unsigned short);
    static int HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
    void SetViewPos(const struct hsPoint3 &);
    const struct hsPoint3 & GetViewPos();
    const class plSpaceTreeNode & GetNode(short);
    short GetRoot(){return 0;}
    int IsRoot(short);
    int plSpaceTree::IsLeaf(short);
    void HarvestLeaves(short, class hsTArray<short> &);
    void HarvestLeaves(class plVolumeIsect *, class hsTArray<short> &);
    void HarvestLeaves(class hsTArray<short> &);
    void HarvestLeaves(short, class hsBitVector &, class hsBitVector &);
    void HarvestLeaves(short, class hsBitVector &);
    void HarvestLeaves(class plVolumeIsect *, class hsBitVector &);
    void HarvestLeaves(class hsBitVector &);
    void HarvestLeaves(class hsBitVector &, class hsBitVector &);
    void EnableLeaf(short, class hsBitVector &);
    void EnableLeaves(const class hsTArray<short> &, class hsBitVector &);
    void HarvestEnabledLeaves(plVolumeIsect *, const hsBitVector &, hsTArray<short> &);
    void SetCache(const class hsBitVector *);
    void BitVectorToList(hsTArray<short> &, const hsBitVector &);
    void SetHarvestFlags(enum plSpaceTree::plHarvestFlags);
    unsigned short GetHarvestFlags();
    unsigned short HasLeafFlag(short w, unsigned short f) { return fTree[w].fFlags & f; }
    void SetLeafFlag(short, unsigned short, int);
    void ClearLeafFlag(short, unsigned short);
    void ClearTreeFlag(unsigned short);
    void SetTreeFlag(unsigned short, int);
    int IsDisabled(unsigned short);
    const class hsBounds3Ext & GetWorldBounds() { return fTree[fRoot].fWorldBounds; }
    void MoveLeaf(short, const class hsBounds3Ext &){}
    void Refresh(){}
    int IsEmpty();
    int IsDirty();
    void MakeDirty() { fTree[fRoot].fFlags |= 2; }
    short GetNumLeaves();
    void HarvestLevel(int, class hsTArray<short> &);

private:
    void IRefreshRecur(short);
    void IHarvestAndCullLeaves(const plSpaceTreeNode &, hsBitVector &, hsBitVector &);
    void IHarvestAndCullLeaves(const plSpaceTreeNode &, hsTArray<short> &);
    void IHarvestLeaves(const plSpaceTreeNode &, hsBitVector &, hsBitVector &);
    void IHarvestLeaves(const plSpaceTreeNode &, hsTArray<short> &);
    void IHarvestLevel(short, int, int, hsTArray<short> &);
    void IHarvestAndCullEnabledLeaves(short, const hsBitVector &, hsTArray<short> &);
    void IHarvestEnabledLeaves(short, const hsBitVector &, hsBitVector &, hsBitVector &);
    void IHarvestEnabledLeaves(short, const hsBitVector &, hsTArray<short> &);
    void IEnableLeaf(short, class hsBitVector &);
#endif
};

#endif
