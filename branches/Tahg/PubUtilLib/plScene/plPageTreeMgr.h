#ifndef PLPAGETREEMGR_H
#define PLPAGETREEMGR_H

#include "../../CoreLib/hsTArray.hpp" 
class plPageTreeMgr {
  hsTArray<class plSceneNode *> fNodes; //this+0x4
  class plSpaceTree * fSpaceTree; //this+0xc
  class plVisMgr * fVisMgr; //this+0x10
  hsTArray<class plOccluder const *> fOccluders; //this+0x14
  hsTArray<class plCullPoly const *> fCullPolys; //this+0x1c
  hsTArray<plCullPoly const *> fSortedCullPolys; //this+0x24

public:
  plPageTreeMgr(const class plPageTreeMgr &);
  plPageTreeMgr::plPageTreeMgr();
  plPageTreeMgr::~plPageTreeMgr();
  const hsTArray<plSceneNode *> & plPageTreeMgr::GetNodes();
  void plPageTreeMgr::AddNode(class plSceneNode *);
  void plPageTreeMgr::RemoveNode(class plSceneNode *);
  void plPageTreeMgr::Reset();
  int plPageTreeMgr::Empty();
  int plPageTreeMgr::Render(class plPipeline *);
  int plPageTreeMgr::Harvest(class plVolumeIsect *, class hsTArray<class plDrawVisList> &);
  void plPageTreeMgr::AddOccluderList(const hsTArray<plOccluder *>){}
  class plSpaceTree * plPageTreeMgr::GetSpaceTree();
  void SetVisMgr(class plVisMgr *);
  class plVisMgr * GetVisMgr();
  static void EnableVisMgr(int);
  static int VisMgrEnabled();

private:

protected:
  void plPageTreeMgr::ITrashSpaceTree();
  int plPageTreeMgr::IBuildSpaceTree();
  int plPageTreeMgr::IRefreshTree(class plPipeline *);
  void plPageTreeMgr::ISortCullPolys(class plPipeline *);
  int plPageTreeMgr::IGetOcclusion(class plPipeline *, class hsTArray<short> &);
  int plPageTreeMgr::IGetCullPolys(class plPipeline *);
  void plPageTreeMgr::IResetOcclusion(class plPipeline *);
  void plPageTreeMgr::IAddCullPolyList(const hsTArray<plCullPoly> &);
  int plPageTreeMgr::ISortByLevel(class plPipeline *, hsTArray<plDrawVisList> &, class hsTArray<plDrawVisList> &);
  int plPageTreeMgr::IPrepForRenderSortingSpans(class plPipeline *, hsTArray<plDrawVisList> &, int &);
  int plPageTreeMgr::IRenderSortingSpans(class plPipeline *, hsTArray<plDrawVisList *> &, class hsTArray<class plDrawSpanPair> &);
  int plPageTreeMgr::IRenderVisList(class plPipeline *, hsTArray<plDrawVisList> &);
};

#endif
