#ifndef PLOCCLUDER_H
#define PLOCCLUDER_H

#include "../../NucleusLib/pnSceneObject/plObjInterface.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/hsBounds.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "plCullPoly.h"
#include "plVisRegion.h"

class plOccluder : public plObjInterface {
  hsTArray<plCullPoly> fPolys; //this+0x6c
  class plOccluderProxy * fProxyGen; //this+0x74
  class hsBitVector fVisSet; //this+0x78
  hsTArray<plVisRegion *> fVisRegions; //this+0x84
  class hsBitVector fVisNot; //this+0x8c
  float fPriority; //this+0x98
  class hsBounds3Ext fWorldBounds; //this+0x9c
  class plKey fSceneNode; //this+0x11c

public:
  plOccluder(const class plOccluder &);
  plOccluder::plOccluder();
  plOccluder::~plOccluder();
  const char * plOccluder::ClassName();
  unsigned short plOccluder::ClassIndex();
  static unsigned short Index();
  static class plOccluder * Create();
  static const class plOccluder * ConvertNoRef(const class plCreatable *);
  static class plOccluder * plOccluder::ConvertNoRef(class plCreatable *);
  static class plOccluder * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plOccluder::GetInterface(unsigned short);
  const class plCreatable * plOccluder::GetConstInterface(unsigned short);
  int plOccluder::MsgReceive(class plMessage *);
  float plOccluder::GetPriority();
  int plOccluder::InVisSet(const class hsBitVector &);
  int plOccluder::InVisNot(const class hsBitVector &);
  const class hsBounds3Ext & plOccluder::GetWorldBounds();
  void plOccluder::SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
  const struct hsMatrix44 & plOccluder::GetLocalToWorld();
  const struct hsMatrix44 & plOccluder::GetWorldToLocal();
  void plOccluder::SetPolyList(const hsTArray<plCullPoly> &);
  const hsTArray<plCullPoly> & plOccluder::GetWorldPolyList();
  const hsTArray<plCullPoly> & plOccluder::GetLocalPolyList();
  long plOccluder::GetNumProperties();
  void plOccluder::Read(class hsStream *, class hsResMgr *);
  void plOccluder::Write(class hsStream *, class hsResMgr *);
  class plDrawableSpans * plOccluder::CreateProxy(class hsGMaterial *, class hsTArray<unsigned long> &, class plDrawableSpans *);
  void plOccluder::ComputeFromPolys();
  class plKey plOccluder::GetSceneNode();

private:
  static void plOccluder::SetClassIndex(unsigned short);

protected:
  float plOccluder::IComputeSurfaceArea();
  void plOccluder::IComputeBounds();
  hsTArray<plCullPoly> & plOccluder::IGetLocalPolyList();
  void plOccluder::ISetSceneNode(class plKey);
  void plOccluder::IAddVisRegion(class plVisRegion *);
  void plOccluder::IRemoveVisRegion(class plVisRegion *);
};

#endif
