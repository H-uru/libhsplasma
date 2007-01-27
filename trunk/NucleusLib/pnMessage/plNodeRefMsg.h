#ifndef PLNODEREFMSG_H
#define PLNODEREFMSG_H

#include "plRefMsg.h"

class plNodeRefMsg : public plGenRefMsg {

public:
  plNodeRefMsg(const class plNodeRefMsg &);
  plNodeRefMsg::plNodeRefMsg(const class plKey &, unsigned char, signed char, signed char){}
  plNodeRefMsg(){}
  const char * plNodeRefMsg::ClassName();
  unsigned short plNodeRefMsg::ClassIndex(){return 0;}
  static unsigned short Index();
  static class plNodeRefMsg * Create();
  static const class plNodeRefMsg * ConvertNoRef(const class plCreatable *);
  static class plNodeRefMsg * plNodeRefMsg::ConvertNoRef(class plCreatable *);
  static class plNodeRefMsg * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plNodeRefMsg::GetInterface(unsigned short);
  const class plCreatable * plNodeRefMsg::GetConstInterface(unsigned short);
  plNodeRefMsg::~plNodeRefMsg(){}

private:
  static void plNodeRefMsg::SetClassIndex(unsigned short);

protected:
};

#endif
