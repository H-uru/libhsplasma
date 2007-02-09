#ifndef HSRESMGR_H
#define HSRESMGR_H

#include "plgDispatch.h"
#include "../../CoreLib/hsRefCnt.h"
#include "../pnKeyedObject/plKey.h"

class hsResMgr : hsRefCnt {

public:
  void DoneLoading();
  class plKey CloneKey(const class plKey &);
  class plKey NetClone(const class plUoid &);
  class plKey FindKey(const class plUoid &);
  class plKeyFinder * GetKeyFinder();
  int AddViaNotify(class plRefMsg *, enum plRefFlags::Type);
  int AddViaNotify(const class plKey &, class plRefMsg *, enum plRefFlags::Type);
  class plKey ReadKeyNotifyMe(class hsStream *, class plRefMsg *, enum plRefFlags::Type){return plKey(); }
  class plKey ReadKey(class hsStream *);
  void WriteKey(class hsStream *, const class plKey &, unsigned char);
  void WriteKey(class hsStream *, class hsKeyedObject *, unsigned char){}
  int SendRef(class hsKeyedObject *, class plRefMsg *, enum plRefFlags::Type);
  int SendRef(const class plKey &, class plRefMsg *, enum plRefFlags::Type);
  class plCreatable * ReadCreatable(class hsStream *);
  void WriteCreatable(class hsStream *, class plCreatable *);
  class plCreatable * ReadCreatableVersion(class hsStream *);
  void WriteCreatableVersion(class hsStream *, class plCreatable *);
  class plKey NewKey(class plUoid &, class hsKeyedObject *);
  class plKey NewKey(const char *, class hsKeyedObject *, const class plLocation &, const class plLoadMask &);
  class plUoid * FindAlias(const char *, unsigned short);
  void AddAlias(const char *, unsigned short, const class plUoid &);
  void RemoveAlias(const char *, unsigned short);
  void hsResMgr::Update();
  void SaveState(class hsStream *);
  void LoadState(class hsStream *);
  void SaveResetState();
  void LoadResetState();
  virtual class plDispatchBase * Dispatch() = 0;
  unsigned long GetNumKeysInLoc(const class plLocation &);
  unsigned long GetTotalLocSize(const class plLocation &);
//  void SetProgressBarProc(function  *);
  void IncProgressBar(float, const char *);
  void PageInHoldList(char *);
  void PageInHold(char *);
  void GetPageVersion(unsigned short *, unsigned short *);
  void hsResMgr::VerifyAgeUnloaded(const char *, const char *);
  void hsResMgr::BeginShutdown();
  hsResMgr(const class hsResMgr &);
  hsResMgr::hsResMgr(){}
  hsResMgr::~hsResMgr(){}

private:

protected:
  void Load(const class plKey &);
  int Unload(const class plKey &);
  class plKey ReadKeyAndReg(class hsStream *);
  class plKey ReRegister(const char *, const class plUoid &);
  bool ReadObject(class plKeyImp *);
  void IUnregistered(class plKey &);
  void IRemoveKeyFromReg(class plKeyImp *);
  int IReset();
  int IInit();
  void IShutdown();
};

#endif
