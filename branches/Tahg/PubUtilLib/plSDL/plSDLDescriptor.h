#ifndef PLSDLDESCRIPTOR_H
#define PLSDLDESCRIPTOR_H

class plSimpleVarDescriptor;
class plSDVarDescriptor;
class plVarDescriptor {
	enum Type
	{
	};
  char * fDefault; //this+0x4
  char * fName; //this+0x8
  int fCount; //this+0xc
  enum plVarDescriptor::Type fType; //this+0x10
  char * fTypeString; //this+0x14
  unsigned long fFlags; //this+0x18
  std::basic_string<char,std::char_traits<char>,std::allocator<char> > fDisplayOptions; //this+0x1c

public:
  plVarDescriptor(const plVarDescriptor &){}
  plVarDescriptor::plVarDescriptor(){}
  plVarDescriptor::~plVarDescriptor(){}
  void plVarDescriptor::CopyFrom(const plVarDescriptor *){}
  const plSimpleVarDescriptor * GetAsSimpleVarDescriptor(){}
  const plSDVarDescriptor * GetAsSDVarDescriptor(){}
  const char * plVarDescriptor::GetDefault(){}
  const char * plVarDescriptor::GetName(){}
  enum plVarDescriptor::Type plVarDescriptor::GetType(){}
  const char * plVarDescriptor::GetTypeString(){}
  int plVarDescriptor::GetCount(){}
  bool plVarDescriptor::IsInternal(){}
  bool plVarDescriptor::IsAlwaysNew(){}
  bool plVarDescriptor::IsVariableLength(){}
  const char * plVarDescriptor::GetDisplayOptions(){}
  void plVarDescriptor::SetDefault(const char *){}
  void plVarDescriptor::SetName(const char *){}
  void plVarDescriptor::SetCount(int){}
  void plVarDescriptor::SetType(enum plVarDescriptor::Type){}
  bool plVarDescriptor::SetType(const char *){}
  void plVarDescriptor::SetInternal(bool){}
  void plVarDescriptor::SetAlwaysNew(bool){}
  void plVarDescriptor::SetVariableLength(bool){}
  void plVarDescriptor::SetDisplayOptions(const char *){}
  bool plVarDescriptor::Read(class hsStream *){}
  void plVarDescriptor::Write(class hsStream *){}
};

class plSimpleVarDescriptor : public plVarDescriptor {
  enum plVarDescriptor::Type fAtomicType; //this+0x38
  int fAtomicCount; //this+0x3c

public:
  plSimpleVarDescriptor(const class plSimpleVarDescriptor &){}
  plSimpleVarDescriptor::plSimpleVarDescriptor(){}
  plSimpleVarDescriptor::~plSimpleVarDescriptor(){}
  const plSimpleVarDescriptor * plSimpleVarDescriptor::GetAsSimpleVarDescriptor(){}
  const plSDVarDescriptor * plSimpleVarDescriptor::GetAsSDVarDescriptor(){}
  void plSimpleVarDescriptor::CopyFrom(const class plVarDescriptor *){}
  void plSimpleVarDescriptor::CopyFrom(const class plSimpleVarDescriptor *){}
  int plSimpleVarDescriptor::GetSize(){}
  int plSimpleVarDescriptor::GetAtomicSize(){}
  enum plVarDescriptor::Type plSimpleVarDescriptor::GetAtomicType(){}
  int plSimpleVarDescriptor::GetAtomicCount(){}
  void plSimpleVarDescriptor::SetType(enum plVarDescriptor::Type){}
  bool plSimpleVarDescriptor::SetType(const char *){}
  void plSimpleVarDescriptor::SetAtomicType(enum plVarDescriptor::Type){}
  bool plSimpleVarDescriptor::Read(class hsStream *){}
  void plSimpleVarDescriptor::Write(class hsStream *){}
};

class plSDVarDescriptor : public plVarDescriptor {
  class plStateDescriptor * fStateDesc; //this+0x38

public:
  plSDVarDescriptor(const class plSDVarDescriptor &){}
  plSDVarDescriptor::plSDVarDescriptor(class plStateDescriptor *){}
  const plSimpleVarDescriptor * plSDVarDescriptor::GetAsSimpleVarDescriptor(){}
  const plSDVarDescriptor * plSDVarDescriptor::GetAsSDVarDescriptor(){}
  plStateDescriptor * plSDVarDescriptor::GetStateDescriptor(){}
  void plSDVarDescriptor::SetStateDesc(class plStateDescriptor *){}
  void plSDVarDescriptor::CopyFrom(const class plVarDescriptor *){}
  void plSDVarDescriptor::CopyFrom(const class plSDVarDescriptor *){}
  bool plSDVarDescriptor::Read(class hsStream *){}
  void plSDVarDescriptor::Write(class hsStream *){}
  plSDVarDescriptor::~plSDVarDescriptor(){}
};


#endif

