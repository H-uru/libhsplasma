#ifndef PLSDL_H
#define PLSDL_H

#include "../../NucleusLib/pnKeyedObject/plUoid.h"
#include "plSDLDescriptor.h"
//#include <vector>

class plStateVarNotificationInfo {
  std::basic_string<char,std::char_traits<char>,std::allocator<char> > fHintString; //this+0x0

public:
  void plStateVarNotificationInfo::SetHintString(const char *){}
  const char * plStateVarNotificationInfo::GetHintString(){}
  void plStateVarNotificationInfo::Read(class hsStream *, unsigned long){}
  void plStateVarNotificationInfo::Write(class hsStream *, unsigned long){}
  plStateVarNotificationInfo(const class plStateVarNotificationInfo &){}
  plStateVarNotificationInfo::plStateVarNotificationInfo(){}
  plStateVarNotificationInfo::~plStateVarNotificationInfo(){}
};

class plStateVariable {
  unsigned long fFlags; //this+0x4
  class plStateVarNotificationInfo fNotificationInfo; //this+0x8

public:
  plStateVariable(const class plStateVariable &){}
  plStateVariable::plStateVariable(){}
  plStateVariable::~plStateVariable(){}
  const char * plStateVariable::GetName(){}
  bool plStateVariable::IsNamed(const char *){}
  int GetCount(){}
  class plSimpleStateVariable * GetAsSimpleStateVar(){}
  class plSDStateVariable * GetAsSDStateVar(){}
  const plVarDescriptor * GetVarDescriptor(){}
  void Alloc(int){}
  bool plStateVariable::IsDirty(){}
  bool plStateVariable::IsUsed(){}
  void plStateVariable::SetDirty(bool){}
  void plStateVariable::SetUsed(bool){}
  void SetFromDefaults(bool){}
  void TimeStamp(const class plUnifiedTime &){}
  const plUnifiedTime & GetTimeStamp(){}
  const plStateVarNotificationInfo & plStateVariable::GetNotificationInfo(){}
  void plStateVariable::DumpToObjectDebugger(bool, int){}
  void plStateVariable::DumpToStream(class hsStream *, bool, int){}
  bool plStateVariable::ReadData(class hsStream *, float, unsigned long){}
  bool plStateVariable::WriteData(class hsStream *, float, unsigned long){}
};

class plStateDataRecord : public plCreatable {
  const class plStateDescriptor * fDescriptor; //this+0x8
  class plUoid fAssocObject; //this+0xc
  std::vector<plStateVariable *,std::allocator<plStateVariable *> > fVarslist; //this+0x28
  std::vector<plStateVariable *,std::allocator<plStateVariable *> > fSDVarsList; //this+0x38
  unsigned long fFlags; //this+0x48

public:
  const char * plStateDataRecord::ClassName(){}
  unsigned short plStateDataRecord::ClassIndex(){}
  static unsigned short Index(){}
  static class plStateDataRecord * Create(){}
  static const class plStateDataRecord * ConvertNoRef(const class plCreatable *){}
  static class plStateDataRecord * ConvertNoRef(class plCreatable *){}
  static class plStateDataRecord * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plStateDataRecord::GetInterface(unsigned short){}
  const class plCreatable * plStateDataRecord::GetConstInterface(unsigned short){}
  plStateDataRecord::plStateDataRecord(){}
  plStateDataRecord::plStateDataRecord(const class plStateDataRecord &, unsigned long){}
  plStateDataRecord::plStateDataRecord(class plStateDescriptor *){}
  plStateDataRecord::plStateDataRecord(const char *, int){}
  plStateDataRecord::~plStateDataRecord(){}
  bool plStateDataRecord::ConvertTo(class plStateDescriptor *, bool){}
  bool plStateDataRecord::operator==(const class plStateDataRecord &){}
  unsigned long plStateDataRecord::GetFlags(){}
  void plStateDataRecord::SetFlags(unsigned long){}
  class plSimpleStateVariable * plStateDataRecord::FindVar(const char *){}
  class plSDStateVariable * plStateDataRecord::FindSDVar(const char *){}
  void plStateDataRecord::CopyFrom(const class plStateDataRecord &, unsigned long){}
  void plStateDataRecord::UpdateFrom(const class plStateDataRecord &, unsigned long){}
  void plStateDataRecord::SetFromDefaults(bool){}
  void plStateDataRecord::TimeStampDirtyVars(){}
  int plStateDataRecord::GetNumVars(){}
  class plSimpleStateVariable * plStateDataRecord::GetVar(int){}
  int plStateDataRecord::GetNumSDVars(){}
  class plSDStateVariable * plStateDataRecord::GetSDVar(int){}
  bool plStateDataRecord::IsUsed(){}
  int plStateDataRecord::GetNumUsedVars(){}
  int plStateDataRecord::GetUsedVars(class std::vector<plSimpleStateVariable *,std::allocator<plSimpleStateVariable *> > *){}
  bool plStateDataRecord::HasUsedVars(){}
  int plStateDataRecord::GetNumUsedSDVars(){}
  int GetUsedSDVars(class std::vector<plSDStateVariable *,std::allocator<plSDStateVariable *> > *){}
  bool plStateDataRecord::HasUsedSDVars(){}
  bool plStateDataRecord::IsDirty(){}
  int plStateDataRecord::GetNumDirtyVars(){}
  int plStateDataRecord::GetDirtyVars(class std::vector<plSimpleStateVariable *,std::allocator<plSimpleStateVariable *> > *){}
  bool plStateDataRecord::HasDirtyVars(){}
  int plStateDataRecord::GetNumDirtySDVars(){}
  int plStateDataRecord::GetDirtySDVars(class std::vector<plSDStateVariable *,std::allocator<plSDStateVariable *> > *){}
  bool plStateDataRecord::HasDirtySDVars(){}
  const class plStateDescriptor * plStateDataRecord::GetDescriptor(){}
  void plStateDataRecord::SetDescriptor(const char *, int){}
  class plNetMsgSDLState * plStateDataRecord::PrepNetMsg(float, unsigned long){}
  void plStateDataRecord::SetAssocObject(const class plUoid &){}
  const plUoid * GetAssocObject(){}
  void plStateDataRecord::FlagDifferentState(const class plStateDataRecord &){}
  void plStateDataRecord::FlagNewerState(const class plStateDataRecord &, bool){}
  void plStateDataRecord::FlagAlwaysNewState(){}
  void plStateDataRecord::DumpToObjectDebugger(const char *, bool, int){}
  void plStateDataRecord::DumpToStream(class hsStream *, const char *, bool, int){}
  bool plStateDataRecord::Read(class hsStream *, float, unsigned long){}
  void plStateDataRecord::Write(class hsStream *, float, unsigned long){}
  static bool plStateDataRecord::ReadStreamHeader(class hsStream *, char * *, int *, class plUoid *){}
  void plStateDataRecord::WriteStreamHeader(class hsStream *, class plUoid *){}

private:
  static void plStateDataRecord::SetClassIndex(unsigned short){}

protected:
  void plStateDataRecord::IDeleteVarsList(std::vector<plStateVariable *,std::allocator<plStateVariable *> > &){}
  void plStateDataRecord::IInitDescriptor(const plStateDescriptor *){}
  void plStateDataRecord::IInitDescriptor(const char *, int){}
  void IReadHeader(class hsStream *){}
  void IWriteHeader(class hsStream *){}
  bool plStateDataRecord::IConvertVar(class plSimpleStateVariable *, class plSimpleStateVariable *, bool){}
  class plStateVariable * plStateDataRecord::IFindVar(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &, const char *){}
  int plStateDataRecord::IGetNumUsedVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &){}
  int plStateDataRecord::IGetUsedVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &, std::vector<plStateVariable *,std::allocator<plStateVariable *> > *){}
  bool plStateDataRecord::IHasUsedVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &){}
  int plStateDataRecord::IGetNumDirtyVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &){}
  int plStateDataRecord::IGetDirtyVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &, std::vector<plStateVariable *,std::allocator<plStateVariable *> > *){}
  bool plStateDataRecord::IHasDirtyVars(const std::vector<plStateVariable *,std::allocator<plStateVariable *> > &){}
};

#endif