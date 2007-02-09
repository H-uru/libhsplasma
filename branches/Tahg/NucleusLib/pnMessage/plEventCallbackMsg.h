#ifndef PLEVENTCALLBACKMSG_H
#define PLEVENTCALLBACKMSG_H

#include "plMessage.h"

class plEventCallbackMsg : plMessage {
  float fEventTime; //this+0x28
  enum CallbackEvent fEvent; //this+0x2c
  short fIndex; //this+0x30
  short fRepeats; //this+0x32
  short fUser; //this+0x34

public:
  plEventCallbackMsg(const class plEventCallbackMsg &);
  plEventCallbackMsg::plEventCallbackMsg(const class plKey &, enum CallbackEvent, int, float, short, unsigned short);
  plEventCallbackMsg::plEventCallbackMsg(const class plKey &, const class plKey &, const double *);
  plEventCallbackMsg::plEventCallbackMsg();
  plEventCallbackMsg::~plEventCallbackMsg();
  const char * plEventCallbackMsg::ClassName();
  unsigned short plEventCallbackMsg::ClassIndex();
  static unsigned short Index();
  static class plEventCallbackMsg * Create();
  static const class plEventCallbackMsg * ConvertNoRef(const class plCreatable *);
  static class plEventCallbackMsg * plEventCallbackMsg::ConvertNoRef(class plCreatable *);
  static class plEventCallbackMsg * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plEventCallbackMsg::GetInterface(unsigned short);
  const class plCreatable * plEventCallbackMsg::GetConstInterface(unsigned short);
  void plEventCallbackMsg::Read(class hsStream *, class hsResMgr *);
  void plEventCallbackMsg::Write(class hsStream *, class hsResMgr *);

private:
  static void plEventCallbackMsg::SetClassIndex(unsigned short);

protected:
};

#endif
