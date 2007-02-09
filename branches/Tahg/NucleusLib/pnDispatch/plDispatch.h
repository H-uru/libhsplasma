#ifndef PLDISPATCH_H
#define PLDISPATCH_H

#include "../inc/plgDispatch.h"
#include "../../CoreLib/hsthread_win.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../pnMessage/plMessage.h"
#include <list>

class plDispatch : public plDispatchBase {
  class hsKeyedObject * fOwner; //this+0x8
  class plMsgWrap * fFutureMsgQueue; //this+0xc
//  class hsTArray<plTypeFilter *> fRegisteredExactTypes; //this+0x10
//  class std::list<plMessage *,std::allocator<plMessage *> > fQueuedMsgList; //this+0x18
  class hsMutex fQueuedMsgListMutex; //this+0x24
  int fQueuedMsgOn; //this+0x2c

public:
  plDispatch(const class plDispatch &);
  plDispatch::plDispatch();
  plDispatch::~plDispatch();
  const char * plDispatch::ClassName();
  unsigned short plDispatch::ClassIndex();
  static unsigned short Index();
  static class plDispatch * Create();
  static const class plDispatch * ConvertNoRef(const class plCreatable *);
  static class plDispatch * ConvertNoRef(class plCreatable *);
  static class plDispatch * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plDispatch::GetInterface(unsigned short);
  const class plCreatable * plDispatch::GetConstInterface(unsigned short);
  void plDispatch::RegisterForType(unsigned short, const class plKey &);
  void plDispatch::RegisterForExactType(unsigned short, const class plKey &);
  void plDispatch::UnRegisterForType(unsigned short, const class plKey &);
  void plDispatch::UnRegisterForExactType(unsigned short, const class plKey &);
  void plDispatch::UnRegisterAll(const class plKey &);
  int plDispatch::MsgSend(class plMessage *, int);
  void plDispatch::MsgQueue(class plMessage *);
  void plDispatch::MsgQueueProcess();
  void plDispatch::MsgQueueOnOff(int);
  int plDispatch::SetMsgBuffering(int);
//  static void plDispatch::SetMsgRecieveCallback(function  *);

private:
  static void plDispatch::SetClassIndex(unsigned short);

protected:
  class hsKeyedObject * plDispatch::IGetOwner();
  class plKey plDispatch::IGetOwnerKey();
  int IFindType(unsigned short);
  int IFindSender(const class plKey &);
  int plDispatch::IUnRegisterForExactType(int, const class plKey &);
  static class plMsgWrap * plDispatch::IInsertToQueue(class plMsgWrap * *, class plMsgWrap *);
  static class plMsgWrap * plDispatch::IDequeue(class plMsgWrap * *, class plMsgWrap * *);
  int plDispatch::IMsgNetPropagate(class plMessage *);
  static void plDispatch::IMsgDispatch();
  static void plDispatch::IMsgEnqueue(class plMsgWrap *, int);
  int plDispatch::ISortToDeferred(class plMessage *);
  void plDispatch::ICheckDeferred(double);
  int plDispatch::IListeningForExactType(unsigned short);
  void plDispatch::ITrashUndelivered();
};

#endif
