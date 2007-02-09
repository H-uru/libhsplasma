#ifndef PLDRAWABLE_H
#define PLDRAWABLE_H

#include "../pnKeyedObject/hsKeyedObject.h"

class plDrawable : hsKeyedObject {

public:
	enum plSubDrawableType
	{
		kSubNormal = 1,
		kSubNonDrawable = 2,
		kSubEnviron = 4,
		kSubAllTypes = 0xFF
	};

  const char * plDrawable::ClassName();
  virtual unsigned short plDrawable::ClassIndex();
  static unsigned short Index();
  static class plDrawable * Create();
  static const class plDrawable * ConvertNoRef(const class plCreatable *);
  static class plDrawable * plDrawable::ConvertNoRef(class plCreatable *);
  static class plDrawable * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int plDrawable::HasBaseClass(unsigned short);
  class plCreatable * plDrawable::GetInterface(unsigned short);
  const class plCreatable * plDrawable::GetConstInterface(unsigned short);
  class plDrawable & SetProperty(unsigned long, int, int);
  class plDrawable & SetProperty(int, int);
  int GetProperty(unsigned long, int);
  int GetProperty(int);
  class plDrawable & SetNativeProperty(unsigned long, int, int);
  class plDrawable & SetNativeProperty(int, int);
  int GetNativeProperty(unsigned long, int);
  int GetNativeProperty(int);
  plDrawable & SetSubType(unsigned long, enum plDrawable::plSubDrawableType, int);
  unsigned long GetSubType(unsigned long);
  unsigned long GetType();
  void SetType(unsigned long);
  void SetRenderLevel(const class plRenderLevel &);
  const class plRenderLevel & GetRenderLevel();
  class plDrawable & SetTransform(unsigned long, const struct hsMatrix44 &, const struct hsMatrix44 &);
  const struct hsMatrix44 & GetLocalToWorld(unsigned long);
  const struct hsMatrix44 & GetWorldToLocal(unsigned long);
  const class hsBounds3Ext & GetLocalBounds(unsigned long);
  const class hsBounds3Ext & GetWorldBounds(unsigned long);
  const class hsBounds3Ext & GetMaxWorldBounds(unsigned long);
  class plSpaceTree * GetSpaceTree(){return 0;}
  void SetDISpanVisSet(unsigned long, class hsKeyedObject *, int);
  class hsGMaterial * GetSubMaterial(int);
  int GetSubVisDists(int, float &, float &);
  void SetSceneNode(class plKey);
  class plKey GetSceneNode();
  unsigned long CreateParticleSystem(unsigned long, unsigned long, class hsGMaterial *);
  void ResetParticleSystem(unsigned long);
  void AssignEmitterToParticleSystem(unsigned long, class plParticleEmitter *);
  int DoIMatch(const class plDrawableCriteria &);
  void Optimize();
  plDrawable(const class plDrawable &);
  plDrawable::plDrawable();
  plDrawable::~plDrawable();

private:
  static void plDrawable::SetClassIndex(unsigned short);

protected:
};

#endif
