#ifndef PLVISREGION_H
#define PLVISREGION_H

#include "../../NucleusLib/pnSceneObject/plObjInterface.h"

class plVisRegion : plObjInterface {
  class plRegionBase * fRegion; //this+0x6c
  class plVisMgr * fMgr; //this+0x70
  long fIndex; //this+0x74

public:
  plVisRegion(const class plVisRegion &);
  plVisRegion::plVisRegion();
  plVisRegion::~plVisRegion();
  const char * plVisRegion::ClassName();
  unsigned short plVisRegion::ClassIndex();
  static unsigned short plVisRegion::Index();
  static class plVisRegion * Create();
  static const class plVisRegion * ConvertNoRef(const class plCreatable *);
  static class plVisRegion * plVisRegion::ConvertNoRef(class plCreatable *);
  static class plVisRegion * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plVisRegion::GetInterface(unsigned short);
  const class plCreatable * plVisRegion::GetConstInterface(unsigned short);
  long plVisRegion::GetNumProperties();
  int plVisRegion::MsgReceive(class plMessage *);
  void plVisRegion::SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &);
  void plVisRegion::Read(class hsStream *, class hsResMgr *);
  void plVisRegion::Write(class hsStream *, class hsResMgr *);
  int plVisRegion::Eval(const struct hsPoint3 &);
  long plVisRegion::GetIndex();
  int Registered();
  int IsNot();
  int plVisRegion::ReplaceNormal();
  int plVisRegion::DisableNormal();

private:
  static void plVisRegion::SetClassIndex(unsigned short);

protected:
  void plVisRegion::SetIndex(long);
};

#endif
