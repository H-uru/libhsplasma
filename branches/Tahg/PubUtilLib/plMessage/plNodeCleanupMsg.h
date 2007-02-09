#ifndef PLNODECLEANUPMSG_H
#define PLNODECLEANUPMSG_H

#include "../../NucleusLib/pnMessage/plMessage.h"

class plNodeCleanupMsg : plMessage {

public:
  static unsigned short plNodeCleanupMsgClassIndex;
  plNodeCleanupMsg(const class plNodeCleanupMsg &);
  plNodeCleanupMsg::plNodeCleanupMsg();
  plNodeCleanupMsg::~plNodeCleanupMsg();
  const char * plNodeCleanupMsg::ClassName();
  unsigned short plNodeCleanupMsg::ClassIndex();
  static unsigned short plNodeCleanupMsg::Index();
  static class plNodeCleanupMsg * Create();
  static const class plNodeCleanupMsg * ConvertNoRef(const class plCreatable *);
  static class plNodeCleanupMsg * plNodeCleanupMsg::ConvertNoRef(class plCreatable *);
  static class plNodeCleanupMsg * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * plNodeCleanupMsg::GetInterface(unsigned short);
  const class plCreatable * plNodeCleanupMsg::GetConstInterface(unsigned short);
  void plNodeCleanupMsg::Read(class hsStream *, class hsResMgr *);
  void plNodeCleanupMsg::Write(class hsStream *, class hsResMgr *);

private:
  static void plNodeCleanupMsg::SetClassIndex(unsigned short);

};

#endif
