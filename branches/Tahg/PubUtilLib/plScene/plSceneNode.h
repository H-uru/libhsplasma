#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H


#include "../../CoreLib/hsmalloc.h"
#include "../../NucleusLib/inc/plDrawable.h"
#include "../../NucleusLib/inc/plgDispatch.h"
#include "../../NucleusLib/pnMessage/plNodeRefMsg.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../plDrawable/plSpaceTree.h"
#include "../plDrawable/plSpaceTreeMaker.h"
#include "../plMessage/plNodeCleanupMsg.h"
#include "plOccluder.h"
#include "plPageTreeMgr.h"

class plSceneNode : public hsKeyedObject {

public:
    plSceneNode(PlasmaVer pv = pvUnknown);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

protected: static unsigned short plSceneNode::plSceneNodeClassIndex;
  int fFilterGenerics; //this+0x10
  short fDepth; //this+0x14
  hsTArray<plSceneObject *> fSceneObjects; //this+0x18
  hsTArray<plDrawable *> fDrawPool; //this+0x20
//  class hsTArray<plPhysical *> fSimulationPool; //this+0x28
//  hsTArray<plAudible *> fAudioPool; //this+0x30
  hsTArray<plOccluder *> fOccluders; //this+0x38
//  class hsTArray<plLightInfo *> fLightPool; //this+0x40
  hsTArray<hsKeyedObject *> fGenericPool; //this+0x48
  plSpaceTree * fSpaceTree; //this+0x50

public:
  plSceneNode(const class plSceneNode &);
  plSceneNode::plSceneNode();
  virtual plSceneNode::~plSceneNode();
  const char * plSceneNode::ClassName();
  virtual unsigned short plSceneNode::ClassIndex();
  static unsigned short plSceneNode::Index() { return plSceneNodeClassIndex; }
  static class plSceneNode * Create();
  static const class plSceneNode * ConvertNoRef(const class plCreatable *);
  static class plSceneNode * plSceneNode::ConvertNoRef(class plCreatable *);
  static class plSceneNode * plSceneNode::Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int plSceneNode::HasBaseClass(unsigned short);
  class plCreatable * plSceneNode::GetInterface(unsigned short);
  const class plCreatable * plSceneNode::GetConstInterface(unsigned short);
  virtual void plSceneNode::Read(class hsStream *, class hsResMgr *);
  virtual void plSceneNode::Write(class hsStream *, class hsResMgr *);
//  void plSceneNode::Harvest(class plVolumeIsect *, class hsTArray<plDrawVisList> &);
//  void plSceneNode::CollectForRender(class plPipeline *, class hsTArray<plDrawVisList> &, class plVisMgr *);
  virtual void plSceneNode::SubmitOccluders(class plPageTreeMgr *) const;
  int plSceneNode::MsgReceive(class plMessage *);
  short GetDepth();
  short IncDepth();
  short DecDepth();
  void plSceneNode::Init();
  class plSpaceTree * plSceneNode::GetSpaceTree();
  class plDrawable * plSceneNode::GetMatchingDrawable(const class plDrawableCriteria &);
  void plSceneNode::OptimizeDrawables();
  void SetFilterGenericsOnly(int);
  const hsTArray<plDrawable *> & plSceneNode::GetDrawPool();

protected:
    void IDirtySpaceTree();
    class plSpaceTree * ITrashSpaceTree();
    class plSpaceTree * IBuildSpaceTree();
    void IRemoveDrawable(class plDrawable *);
    void IRemoveAudible(class plAudible *);
    void IRemovePhysical(class plPhysical *);
    void IRemoveObject(class plSceneObject *);
    void IRemoveLight(class plLightInfo *);
    void IRemoveOccluder(class plOccluder *);
    void IRemoveGeneric(class hsKeyedObject *);
    void ISetObject(class plSceneObject *);
    void ISetPhysical(class plPhysical *);
    void ISetAudible(class plAudible *);
    void ISetDrawable(class plDrawable *);
    void ISetLight(class plLightInfo *);
    void ISetOccluder(class plOccluder *);
    void ISetGeneric(class hsKeyedObject *);
    int IOnRemove(class plNodeRefMsg *);
    int IOnAdd(class plNodeRefMsg *);
    void ICleanUp();
};

#endif

