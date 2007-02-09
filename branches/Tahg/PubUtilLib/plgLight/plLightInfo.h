#ifndef PLLIGHTINFO_H
#define PLLIGHTINFO_H

#include "../../NucleusLib/pnSceneObject/plObjInterface.h"
#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/hsColorRGBA.h"
#include "../plScene/plVisRegion.h"

class plLightInfo : public plObjInterface {
  unsigned char fVolFlags; //this+0x6c
  class hsBitVector fVisSet; //this+0x70
  class hsBitVector fVisNot; //this+0x7c
  hsTArray<plVisRegion *> fVisRegions; //this+0x88
  class plLightInfo * * fPrevDevPtr; //this+0x90
  class plLightInfo * fNextDevPtr; //this+0x94
  class hsGDeviceRef * fDeviceRef; //this+0x98
  class plLayerInterface * fProjection; //this+0x9c
  struct hsMatrix44 fWorldToProj; //this+0xa0
  struct hsColorRGBA fAmbient; //this+0xe4
  struct hsColorRGBA fDiffuse; //this+0xf4
  struct hsColorRGBA fSpecular; //this+0x104
  struct hsMatrix44 fLightToLocal; //this+0x114
  struct hsMatrix44 fLocalToLight; //this+0x158
  struct hsMatrix44 fLocalToWorld; //this+0x19c
  struct hsMatrix44 fWorldToLocal; //this+0x1e0
  struct hsMatrix44 fLightToWorld; //this+0x224
  struct hsMatrix44 fWorldToLight; //this+0x268
  class plKey fSceneNode; //this+0x2ac
  class plLightProxy * fProxyGen; //this+0x2b0
  class plSoftVolume * fSoftVolume; //this+0x2b4
  float fMaxStrength; //this+0x2b8
  int fRegisteredForRenderMsg; //this+0x2bc
  class hsBitVector fSlaveBits; //this+0x2c0

public:
  plLightInfo(const class plLightInfo &){}
  plLightInfo::plLightInfo(){}
  plLightInfo::~plLightInfo(){}
  const char * plLightInfo::ClassName(){}
  unsigned short plLightInfo::ClassIndex(){}
  static unsigned short plLightInfo::Index(){}
  static class plLightInfo * Create(){}
  static const class plLightInfo * ConvertNoRef(const class plCreatable *){}
  static class plLightInfo * plLightInfo::ConvertNoRef(class plCreatable *){}
  static class plLightInfo * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plLightInfo::GetInterface(unsigned short){}
  const class plCreatable * plLightInfo::GetConstInterface(unsigned short){}
  void plLightInfo::SetDeviceRef(class hsGDeviceRef *){}
  class hsGDeviceRef * plLightInfo::GetDeviceRef(){}
  int plLightInfo::IsDirty(){}
  void plLightInfo::SetDirty(int){}
  int plLightInfo::IsEmpty(){}
  void SetEmpty(int){}
  int plLightInfo::IsZero(){}
  void plLightInfo::SetZero(int){}
  int plLightInfo::IsIdle(){}
  int plLightInfo::OverAll(){}
  int IsShadowCaster(){}
  void SetShadowCaster(int){}
  void plLightInfo::Refresh(){}
  void plLightInfo::GetStrengthAndScale(const class hsBounds3Ext &, float &, float &){}
  int plLightInfo::AffectsBound(const class hsBounds3Ext &){}
  void plLightInfo::GetAffectedForced(const class plSpaceTree *, class hsBitVector &, int){}
  const class hsTArray<short> & plLightInfo::GetAffected(class plSpaceTree *, const class hsTArray<short> &, class hsTArray<short> &, int){}
  void plLightInfo::GetAffected(const class plSpaceTree *, class hsBitVector &, int){}
  int plLightInfo::InVisSet(const class hsBitVector &){}
  int plLightInfo::InVisNot(const class hsBitVector &){}
  void plLightInfo::SetAmbient(const struct hsColorRGBA &){}
  void plLightInfo::SetDiffuse(const struct hsColorRGBA &){}
  void plLightInfo::SetSpecular(const struct hsColorRGBA &){}
  const struct hsColorRGBA & plLightInfo::GetAmbient(){}
  const struct hsColorRGBA & plLightInfo::GetDiffuse(){}
  const struct hsColorRGBA & plLightInfo::GetSpecular(){}
  class plLayerInterface * plLightInfo::GetProjection(){}
  void plLightInfo::SetProperty(int, int){}
  void plLightInfo::SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  const struct hsMatrix44 & plLightInfo::GetLocalToWorld(){}
  const struct hsMatrix44 & plLightInfo::GetWorldToLocal(){}
  const struct hsMatrix44 & plLightInfo::GetLightToWorld(){}
  const struct hsMatrix44 & plLightInfo::GetWorldToLight(){}
  long plLightInfo::GetNumProperties(){}
  const class plSoftVolume * GetSoftVolume(){}
  struct hsVector3 GetNegativeWorldDirection(const struct hsPoint3 &){}
  void plLightInfo::Read(class hsStream *, class hsResMgr *){}
  void plLightInfo::Write(class hsStream *, class hsResMgr *){}
  int plLightInfo::MsgReceive(class plMessage *){}
  void plLightInfo::Unlink(){}
  void plLightInfo::Link(class plLightInfo * *){}
  class plLightInfo * plLightInfo::GetNext(){}
  int plLightInfo::IsLinked(){}
  void plLightInfo::ClearSlaveBits(){}
  void plLightInfo::SetSlaveBit(int){}
  const class hsBitVector & plLightInfo::GetSlaveBits(){}
  class plKey plLightInfo::GetSceneNode(){}
  void plLightInfo::SetLocalToLight(const struct hsMatrix44 &, const struct hsMatrix44 &){}
  class plDrawableSpans * plLightInfo::CreateProxy(class hsGMaterial *, hsTArray<unsigned long> &, class plDrawableSpans *){}

private:
  static void plLightInfo::SetClassIndex(unsigned short){}

protected:
  void IMakeIsect(){}
  class plVolumeIsect * IGetIsect(){}
  void plLightInfo::IRefresh(){}
  const struct hsMatrix44 & plLightInfo::IGetWorldToProj(){}
  void plLightInfo::IAddVisRegion(class plVisRegion *){}
  void plLightInfo::IRemoveVisRegion(class plVisRegion *){}
  void plLightInfo::ISetSceneNode(class plKey){}
  void plLightInfo::ICheckMaxStrength(){}
};

#endif
