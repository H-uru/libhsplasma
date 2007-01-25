#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsTArray.hpp"

class plSceneNode : public hsKeyedObject {
public:
    hsTArray<plKey*> SceneObjects;
    hsTArray<plKey*> OtherObjects;

public:
    plSceneNode(PlasmaVer pv = pvUnknown);
    virtual ~plSceneNode();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

#ifdef Tahg
protected: static unsigned short plSceneNode::plSceneNodeClassIndex;
  int fFilterGenerics; //this+0x10
  short fDepth; //this+0x14
  hsTArray<plSceneObject *> fSceneObjects; //this+0x18
//  class hsTArray<plDrawable *> fDrawPool; //this+0x20
//  class hsTArray<plPhysical *> fSimulationPool; //this+0x28
//  class hsTArray<plAudible *> fAudioPool; //this+0x30
//  class hsTArray<plOccluder *> fOccluders; //this+0x38
//  class hsTArray<plLightInfo *> fLightPool; //this+0x40
  hsTArray<hsKeyedObject *> fGenericPool; //this+0x48
//  class plSpaceTree * fSpaceTree; //this+0x50

public:
  plSceneNode(const class plSceneNode &);
  plSceneNode::plSceneNode();
  //plSceneNode::~plSceneNode();
  const char * plSceneNode::ClassName();
  virtual unsigned short plSceneNode::ClassIndex() { return plSceneNodeClassIndex; }
  static unsigned short plSceneNode::Index() { return plSceneNodeClassIndex; }
  static class plSceneNode * Create();
  static const class plSceneNode * ConvertNoRef(const class plCreatable *);
  static class plSceneNode * plSceneNode::ConvertNoRef(class plCreatable *);
  static class plSceneNode * plSceneNode::Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int plSceneNode::HasBaseClass(unsigned short);
  class plCreatable * plSceneNode::GetInterface(unsigned short);
  const class plCreatable * plSceneNode::GetConstInterface(unsigned short);
  void plSceneNode::Read(class hsStream *, class hsResMgr *);
  void plSceneNode::Write(class hsStream *, class hsResMgr *);
//  void plSceneNode::Harvest(class plVolumeIsect *, class hsTArray<plDrawVisList> &);
//  void plSceneNode::CollectForRender(class plPipeline *, class hsTArray<plDrawVisList> &, class plVisMgr *);
  void plSceneNode::SubmitOccluders(class plPageTreeMgr *);
  int plSceneNode::MsgReceive(class plMessage *);
  short GetDepth();
  short IncDepth();
  short DecDepth();
  void plSceneNode::Init();
  class plSpaceTree * plSceneNode::GetSpaceTree();
  class plDrawable * plSceneNode::GetMatchingDrawable(const class plDrawableCriteria &);
  void plSceneNode::OptimizeDrawables();
  void SetFilterGenericsOnly(int);
  const class hsTArray<plDrawable *> & plSceneNode::GetDrawPool();
//  void __local_vftable_ctor_closure();
//  void * __vecDelDtor(unsigned int);

private:
  static void plSceneNode::SetClassIndex(unsigned short);

protected:
  void plSceneNode::IDirtySpaceTree();
  class plSpaceTree * plSceneNode::ITrashSpaceTree();
  class plSpaceTree * plSceneNode::IBuildSpaceTree();
  void plSceneNode::IRemoveDrawable(class plDrawable *);
  void plSceneNode::IRemoveAudible(class plAudible *);
  void plSceneNode::IRemovePhysical(class plPhysical *);
  void plSceneNode::IRemoveObject(class plSceneObject *);
  void plSceneNode::IRemoveLight(class plLightInfo *);
  void plSceneNode::IRemoveOccluder(class plOccluder *);
  void plSceneNode::IRemoveGeneric(class hsKeyedObject *);
  void plSceneNode::ISetObject(class plSceneObject *);
  void plSceneNode::ISetPhysical(class plPhysical *);
  void plSceneNode::ISetAudible(class plAudible *);
  void plSceneNode::ISetDrawable(class plDrawable *);
  void plSceneNode::ISetLight(class plLightInfo *);
  void plSceneNode::ISetOccluder(class plOccluder *);
  void plSceneNode::ISetGeneric(class hsKeyedObject *);
  int plSceneNode::IOnRemove(class plNodeRefMsg *);
  int plSceneNode::IOnAdd(class plNodeRefMsg *);
  void plSceneNode::ICleanUp();
#endif
};

#endif

