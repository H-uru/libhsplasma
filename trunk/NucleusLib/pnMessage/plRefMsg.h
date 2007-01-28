#ifndef PLREFMSG_H
#define PLREFMSG_H

#include "plMessage.h"

class plRefMsg : public plMessage {
  class hsKeyedObject * fRef; //this+0x28
  class hsKeyedObject * fOldRef; //this+0x2c
  unsigned char fContext; //this+0x30

public:
  plRefMsg(const class plRefMsg &);
  plRefMsg::plRefMsg(const class plKey &, unsigned char);
  plRefMsg::plRefMsg(){}
  plRefMsg::~plRefMsg(){}
  const char * plRefMsg::ClassName();
  virtual unsigned short plRefMsg::ClassIndex(){return 0;}
  static unsigned short Index();
  static class plRefMsg * Create();
  static const class plRefMsg * ConvertNoRef(const class plCreatable *);
  static class plRefMsg * plRefMsg::ConvertNoRef(class plCreatable *);
  static class plRefMsg * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plRefMsg::GetInterface(unsigned short);
  const class plCreatable * plRefMsg::GetConstInterface(unsigned short);
  class plRefMsg & plRefMsg::SetRef(class hsKeyedObject *);
  class hsKeyedObject * plRefMsg::GetRef();
  class plRefMsg & plRefMsg::SetOldRef(class hsKeyedObject *);
  class hsKeyedObject * plRefMsg::GetOldRef();
  class plRefMsg & plRefMsg::SetContext(unsigned char);
  unsigned char plRefMsg::GetContext();
  void plRefMsg::Read(class hsStream *, class hsResMgr *);
  void plRefMsg::Write(class hsStream *, class hsResMgr *);

private:
  static void plRefMsg::SetClassIndex(unsigned short);

protected:
};

class plGenRefMsg : public plRefMsg {
  signed char fType; //this+0x38
  long fWhich; //this+0x3c

public:
  plGenRefMsg(const class plGenRefMsg &);
  plGenRefMsg::plGenRefMsg(const class plKey &, unsigned char, long, signed char);
  plGenRefMsg(){}
  const char * plGenRefMsg::ClassName();
  unsigned short plGenRefMsg::ClassIndex(){return 0;}
  static unsigned short Index();
  static class plGenRefMsg * Create();
  static const class plGenRefMsg * ConvertNoRef(const class plCreatable *);
  static class plGenRefMsg * plGenRefMsg::ConvertNoRef(class plCreatable *);
  static class plGenRefMsg * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int plGenRefMsg::HasBaseClass(unsigned short);
  class plCreatable * plGenRefMsg::GetInterface(unsigned short);
  const class plCreatable * plGenRefMsg::GetConstInterface(unsigned short);
  void plGenRefMsg::Read(class hsStream *, class hsResMgr *);
  void plGenRefMsg::Write(class hsStream *, class hsResMgr *);
  plGenRefMsg::~plGenRefMsg(){}

private:
  static void plGenRefMsg::SetClassIndex(unsigned short);

protected:
};

#endif
