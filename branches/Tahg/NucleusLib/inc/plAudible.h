#ifndef PLAUDIBLE_H
#define PLAUDIBLE_H

#include "../../CoreLib/hsTArray.hpp"
#include "../pnKeyedObject/hsKeyedObject.h"
#include "../pnMessage/plEventCallbackMsg.h"

class plAudible : hsKeyedObject {
  hsTArray<plEventCallbackMsg *> fCallbacks; //this+0x10

public:
  const char * plAudible::ClassName();
  unsigned short plAudible::ClassIndex();
  static unsigned short Index();
  static class plAudible * Create();
  static const class plAudible * ConvertNoRef(const class plCreatable *);
  static class plAudible * plAudible::ConvertNoRef(class plCreatable *);
  static class plAudible * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int plAudible::HasBaseClass(unsigned short);
  class plCreatable * plAudible::GetInterface(unsigned short);
  const class plCreatable * plAudible::GetConstInterface(unsigned short);
  class plAudible & SetProperty(int, int);
  int GetProperty(int);
  class plAudible & plAudible::SetTransform(const struct hsMatrix44 &, const struct hsMatrix44 &, int);
  void plAudible::Read(class hsStream *, class hsResMgr *);
  void plAudible::Write(class hsStream *, class hsResMgr *);
  void SetSceneObject(class plKey);
  class plKey GetSceneObject();
  void SetSceneNode(class plKey);
  class plKey GetSceneNode();
  void Play(int);
  void Stop(int);
  void FastForwardPlay(int);
  void FastForwardToggle(int);
  void SetMin(const float, int);
  void SetMax(const float, int);
  float GetMin(int);
  float GetMax(int);
  void SetVelocity(const struct hsVector3, int);
  struct hsVector3 GetVelocity(int);
  struct hsPoint3 GetPosition(int);
  void SetLooping(int, int);
  int IsPlaying(int);
  void SetTime(double, int);
  void Activate();
  void DeActivate();
  void RemoveCallbacks(class plSoundMsg *);
  void AddCallbacks(class plSoundMsg *);
  void GetStatus(class plSoundMsg *);
  int GetNumSounds();
  class plSound * GetSound(int);
  int GetSoundIndex(const char *);
  void plAudible::Init(int);
  void SetVolume(const float, int);
  void SetMuted(int, int);
  void ToggleMuted(int);
  void SetTalkIcon(int, unsigned long);
  void ClearTalkIcon();
  void SetFilename(int, const char *, bool);
  void SetFadeIn(const int, const float, int);
  void SetFadeOut(const int, const float, int);
  plAudible(const class plAudible &);
  plAudible::plAudible();
  plAudible::~plAudible();

private:
  static void plAudible::SetClassIndex(unsigned short);

protected:
};

#endif
