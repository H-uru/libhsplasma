#ifndef PLSPACETREEMAKER_H
#define PLSPACETREEMAKER_H

#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsBitVector.h"
#include "plSpacePrepNode.h"

class plSpaceTreeMaker {
  hsTArray<plSpacePrepNode *> fLeaves; //this+0x0
  class hsRadixSortElem * fSortScratch; //this+0x8
  class hsBitVector fDisabled; //this+0xc
  class plSpacePrepNode * fPrepTree; //this+0x18
  short fTreeSize; //this+0x1c

public:
  void plSpaceTreeMaker::Cleanup();
  void plSpaceTreeMaker::Reset(){}
  long plSpaceTreeMaker::AddLeaf(const class hsBounds3Ext &, int){return 0;}
  class plSpaceTree * plSpaceTreeMaker::MakeTree(){return 0;}
  void plSpaceTreeMaker::TestTree();
  plSpaceTreeMaker(const class plSpaceTreeMaker &);
  plSpaceTreeMaker::plSpaceTreeMaker(){}
  plSpaceTreeMaker::~plSpaceTreeMaker(){}

private:

protected:
  class plSpacePrepNode * plSpaceTreeMaker::INewSubRoot(const class hsBounds3Ext &);
  void plSpaceTreeMaker::IFindBigList(hsTArray<plSpacePrepNode *> &, float, const struct hsVector3 &, hsTArray<plSpacePrepNode *> &, hsTArray<plSpacePrepNode *> &);
  void plSpaceTreeMaker::ISortList(hsTArray<plSpacePrepNode *> &, const struct hsVector3 &);
  void plSpaceTreeMaker::ISplitList(hsTArray<plSpacePrepNode *> &, const struct hsVector3 &, hsTArray<plSpacePrepNode *> &, hsTArray<plSpacePrepNode *> &);
  class hsBounds3Ext plSpaceTreeMaker::IFindDistToCenterAxis(hsTArray<plSpacePrepNode *> &, float &, struct hsVector3 &);
  class plSpacePrepNode * plSpaceTreeMaker::IMakeFatTreeRecur(hsTArray<plSpacePrepNode *> &);
  class hsBounds3Ext plSpaceTreeMaker::IFindSplitAxis(hsTArray<plSpacePrepNode *> &, float &, struct hsVector3 &);
  class plSpacePrepNode * plSpaceTreeMaker::IMakeTreeRecur(hsTArray<plSpacePrepNode *> &);
  void plSpaceTreeMaker::IMakeTree();
  class plSpaceTree * plSpaceTreeMaker::IMakeEmptyTree();
  class plSpaceTree * plSpaceTreeMaker::IMakeDegenerateTree();
  void plSpaceTreeMaker::IGatherLeavesRecur(class plSpacePrepNode *, class plSpaceTree *);
  void plSpaceTreeMaker::IMakeSpaceTreeRecur(class plSpacePrepNode *, class plSpaceTree *, const int, int);
  class plSpaceTree * plSpaceTreeMaker::IMakeSpaceTree();
  int plSpaceTreeMaker::ITreeDepth(class plSpacePrepNode *);
  void plSpaceTreeMaker::IDeleteTreeRecur(class plSpacePrepNode *);
};

#endif
