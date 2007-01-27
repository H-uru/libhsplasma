#ifndef PLSPACETREE_H
#define PLSPACETREE_H

#include "../../NucleusLib/pnFactory/plCreatable.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsbounds.h"

class plSpaceTreeNode {
  class hsBounds3Ext fWorldBounds; //this+0x0
  unsigned short fFlags; //this+0x80
  short fParent; //this+0x82
  union {
	short fChildren[2]; //this+0x84
	short fLeafIndex; //this+0x84
  };
public:
  short GetChild(int);
  short GetParent();
  short GetLeaf();
  int plSpaceTreeNode::IsLeaf();
  const hsBounds3Ext & plSpaceTreeNode::GetWorldBounds();
  void Read(class hsStream *);
  void Write(class hsStream *);
  plSpaceTreeNode(const plSpaceTreeNode &);
  plSpaceTreeNode();
  friend plSpaceTree;
private:

protected:
};








































class plSpaceTree : plCreatable {
	enum plHarvestFlags
	{
		kNone,
		kSortBackToFront,
		kSortFrontToBack
	};
  hsTArray<plSpaceTreeNode> fTree; //this+0x8
  const class hsBitVector * fCache; //this+0x10
  short fRoot; //this+0x14
  short fNumLeaves; //this+0x16
  unsigned short fHarvestFlags; //this+0x18
  class plVolumeIsect * fCullFunc; //this+0x1c
  struct hsPoint3 fViewPos; //this+0x20

public:
  plSpaceTree(const class plSpaceTree &);
  plSpaceTree();
  ~plSpaceTree();
  const char * plSpaceTree::ClassName();
  unsigned short plSpaceTree::ClassIndex();
  static unsigned short Index();
  static class plSpaceTree * Create();
  static const class plSpaceTree * ConvertNoRef(const class plCreatable *);
  static class plSpaceTree * plSpaceTree::ConvertNoRef(class plCreatable *);
  static class plSpaceTree * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plSpaceTree::GetInterface(unsigned short);
  const class plCreatable * plSpaceTree::GetConstInterface(unsigned short);
  void plSpaceTree::SetViewPos(const struct hsPoint3 &);
  const struct hsPoint3 & GetViewPos();
  const class plSpaceTreeNode & plSpaceTree::GetNode(short);
  short plSpaceTree::GetRoot(){return 0;}
  int IsRoot(short);
  int plSpaceTree::IsLeaf(short);
  void plSpaceTree::HarvestLeaves(short, class hsTArray<short> &);
  void plSpaceTree::HarvestLeaves(class plVolumeIsect *, class hsTArray<short> &);
  void plSpaceTree::HarvestLeaves(class hsTArray<short> &);
  void plSpaceTree::HarvestLeaves(short, class hsBitVector &, class hsBitVector &);
  void plSpaceTree::HarvestLeaves(short, class hsBitVector &);
  void plSpaceTree::HarvestLeaves(class plVolumeIsect *, class hsBitVector &);
  void plSpaceTree::HarvestLeaves(class hsBitVector &);
  void plSpaceTree::HarvestLeaves(class hsBitVector &, class hsBitVector &);
  void plSpaceTree::EnableLeaf(short, class hsBitVector &);
  void plSpaceTree::EnableLeaves(const class hsTArray<short> &, class hsBitVector &);
  void plSpaceTree::HarvestEnabledLeaves(class plVolumeIsect *, const class hsBitVector &, class hsTArray<short> &);
  void plSpaceTree::SetCache(const class hsBitVector *);
  void plSpaceTree::BitVectorToList(class hsTArray<short> &, const class hsBitVector &);
  void SetHarvestFlags(enum plSpaceTree::plHarvestFlags);
  unsigned short GetHarvestFlags();
  unsigned short plSpaceTree::HasLeafFlag(short w, unsigned short f) { return fTree[w].fFlags & f; }
  void plSpaceTree::SetLeafFlag(short, unsigned short, int);
  void plSpaceTree::ClearLeafFlag(short, unsigned short);
  void plSpaceTree::ClearTreeFlag(unsigned short);
  void plSpaceTree::SetTreeFlag(unsigned short, int);
  int plSpaceTree::IsDisabled(unsigned short);
  const class hsBounds3Ext & plSpaceTree::GetWorldBounds() { return fTree[fRoot].fWorldBounds; }
  void plSpaceTree::MoveLeaf(short, const class hsBounds3Ext &){}
  void plSpaceTree::Refresh(){}
  int plSpaceTree::IsEmpty();
  int plSpaceTree::IsDirty();
  void plSpaceTree::MakeDirty() { fTree[fRoot].fFlags |= 2; }
  short plSpaceTree::GetNumLeaves();
  void plSpaceTree::Read(class hsStream *, class hsResMgr *);
  void plSpaceTree::Write(class hsStream *, class hsResMgr *);
  void plSpaceTree::HarvestLevel(int, class hsTArray<short> &);

private:
  void plSpaceTree::IRefreshRecur(short);
  void plSpaceTree::IHarvestAndCullLeaves(const class plSpaceTreeNode &, class hsBitVector &, class hsBitVector &);
  void plSpaceTree::IHarvestAndCullLeaves(const class plSpaceTreeNode &, class hsTArray<short> &);
  void plSpaceTree::IHarvestLeaves(const class plSpaceTreeNode &, class hsBitVector &, class hsBitVector &);
  void plSpaceTree::IHarvestLeaves(const class plSpaceTreeNode &, class hsTArray<short> &);
  void plSpaceTree::IHarvestLevel(short, int, int, class hsTArray<short> &);
  void plSpaceTree::IHarvestAndCullEnabledLeaves(short, const class hsBitVector &, class hsTArray<short> &);
  void plSpaceTree::IHarvestEnabledLeaves(short, const class hsBitVector &, class hsBitVector &, class hsBitVector &);
  void plSpaceTree::IHarvestEnabledLeaves(short, const class hsBitVector &, class hsTArray<short> &);
  void plSpaceTree::IEnableLeaf(short, class hsBitVector &);
  static void plSpaceTree::SetClassIndex(unsigned short);

protected:
};

#endif
