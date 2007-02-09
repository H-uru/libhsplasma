#ifndef PLCULLTREE_H
#define PLCULLTREE_H

#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsTemplates.h"
#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/hsGeometry3.h"
#include "../plScene/plCullPoly.h"
#include "plCuller.h"

class plCullNode {

	enum plCullStatus
	{
		kClear = 0x0,
		kCulled = 0x1,
		kSplit = 0x2,
		kPureSplit = 0x3,
	};
	
	struct hsVector3 fNorm; //this+0x0
  float fDist; //this+0xc
  int fIsFace; //this+0x10
  short fInnerChild; //this+0x14
  short fOuterChild; //this+0x16
  const class plCullTree * fTree; //this+0x18

public:
  void Init(const class plCullTree *, const class plCullPoly &){}
  void plCullNode::Init(const class plCullTree *, const struct hsVector3 &, float){}
  void plCullNode::SetPlane(const struct hsVector3 &, float){}
  const struct hsVector3 & GetNormal(){}
  const float GetDist(){}
  enum plCullNode::plCullStatus plCullNode::TestBounds(const hsBounds3Ext &){}
  enum plCullStatus TestSphere(const struct hsPoint3 &, float){}
  plCullNode::plCullNode(){}

protected:
  class plCullNode * plCullNode::IGetNode(short){}
  void ISetPointersRecur(){}
  enum plCullNode::plCullStatus plCullNode::ITestBoundsRecur(const hsBounds3Ext &){}
  enum plCullNode::plCullStatus plCullNode::ITestSphereRecur(const struct hsPoint3 &, float){}
  void plCullNode::ITestNode(const class plSpaceTree *, short, hsBitVector &, hsBitVector &){}
  enum plCullNode::plCullStatus plCullNode::ITestNode(const class plSpaceTree *, short, hsLargeArray<short> &, hsLargeArray<short> &, hsLargeArray<short> &){}
  void plCullNode::IHarvest(const class plSpaceTree *, hsTArray<short> &){}
  float plCullNode::IInterpVert(const struct hsPoint3 &, const struct hsPoint3 &, struct hsPoint3 &){}
  enum plCullNode::plCullStatus plCullNode::ISplitPoly(const class plCullPoly &, class plCullPoly * &, class plCullPoly * &){}
  void plCullNode::IMarkClipped(const plCullPoly &, const hsBitVector &){}
  void plCullNode::ITakeHalfPoly(const plCullPoly &, const hsTArray<int> &, const hsBitVector &, class plCullPoly &){}
  void plCullNode::IBreakPoly(const plCullPoly &, const hsTArray<float> &, hsBitVector &, hsBitVector &, hsBitVector &, class plCullPoly &){}
  hsTArray<plCullPoly> & plCullNode::ScratchPolys(){}
  hsLargeArray<short> & plCullNode::ScratchClear(){}
  hsLargeArray<short> & plCullNode::ScratchSplit(){}
  hsLargeArray<short> & plCullNode::ScratchCulled(){}
  hsBitVector & plCullNode::ScratchBitVec(){}
  hsBitVector & plCullNode::ScratchTotVec(){}
};

class plCullTree : public plCuller {
  int fCapturePolys; //this+0x4
  hsTArray<hsPoint3> fVisVerts; //this+0x8
  hsTArray<hsVector3> fVisNorms; //this+0x10
  hsTArray<hsColorRGBA> fVisColors; //this+0x18
  hsTArray<unsigned short> fVisTris; //this+0x20
  float fVisYon; //this+0x28
  hsTArray<plCullPoly> fScratchPolys; //this+0x2c
  hsLargeArray<short> fScratchClear; //this+0x34
  hsLargeArray<short> fScratchSplit; //this+0x40
  hsLargeArray<short> fScratchCulled; //this+0x4c
  hsBitVector fScratchBitVec; //this+0x58
  hsBitVector fScratchTotVec; //this+0x64
  struct hsPoint3 fViewPos; //this+0x70
  short fRoot; //this+0x7c
  hsTArray<plCullNode> fNodeList; //this+0x80

public:
  plCullTree::plCullTree(const class plCullTree &){}
  plCullTree::plCullTree(){}
  plCullTree::~plCullTree(){}
  void plCullTree::Reset(){}
  void plCullTree::InitFrustum(const struct hsMatrix44 &){}
  void plCullTree::SetViewPos(const struct hsPoint3 &){}
  void plCullTree::AddPoly(const class plCullPoly &){}
  unsigned long plCullTree::GetNumNodes(){}
  void plCullTree::Harvest(const class plSpaceTree *, hsTArray<short> &){}
  int plCullTree::BoundsVisible(const hsBounds3Ext &){}
  int plCullTree::SphereVisible(const struct hsPoint3 &, float){}
  void plCullTree::SetVisualizationYon(float){}
  void plCullTree::BeginCapturePolys(){}
  void plCullTree::EndCapturePolys(){}
  hsTArray<hsPoint3> & plCullTree::GetCaptureVerts(){}
  hsTArray<hsVector3> & plCullTree::GetCaptureNorms(){}
  hsTArray<hsColorRGBA> & plCullTree::GetCaptureColors(){}
  hsTArray<unsigned short> & plCullTree::GetCaptureTris(){}
  void plCullTree::ReleaseCapture(){}

protected:
  void plCullTree::IVisPolyShape(const class plCullPoly &, int){}
  void plCullTree::IVisPolyEdge(const struct hsPoint3 &, const struct hsPoint3 &, int){}
  void plCullTree::IVisPoly(const class plCullPoly &, int){}
  class plCullNode * plCullTree::IGetRoot(){}
  class plCullNode * plCullTree::IGetNode(short){}
  void ITestNode(const class plSpaceTree *, short, hsTArray<short> &){}
  void ITestList(const class plSpaceTree *, const hsTArray<short> &, hsTArray<short> &){}
  short plCullTree::IAddPolyRecur(const class plCullPoly &, short){}
  short plCullTree::IMakeHoleSubTree(const class plCullPoly &){}
  short plCullTree::IMakePolySubTree(const class plCullPoly &){}
  short plCullTree::IMakePolyNode(const class plCullPoly &, int, int){}
  hsTArray<plCullPoly> & plCullTree::ScratchPolys(){}
  hsLargeArray<short> & plCullTree::ScratchClear(){}
  hsLargeArray<short> & plCullTree::ScratchSplit(){}
  hsLargeArray<short> & plCullTree::ScratchCulled(){}
  hsBitVector & plCullTree::ScratchBitVec(){}
  hsBitVector & plCullTree::ScratchTotVec(){}
  void plCullTree::ISetupScratch(unsigned short){}
};

#endif
