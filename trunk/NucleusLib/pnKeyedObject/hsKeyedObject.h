#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

class hsKeyedObject : public plReceiver {
public:
    enum {
        kFlagPreventLoad = 0x1,
        kFlagPreventReset = 0x2,
        kFlagPreventInit = 0x4
    };

protected:
    plKey* myKey;
    unsigned int koFlags;

public:
    hsKeyedObject(PlasmaVer pv = pvUnknown);
    //virtual ~hsKeyedObject();

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);
#ifdef Tahg
public:
protected:
  plKey fpKey; //this+0x8
  unsigned long fKeyedObjectFlags; //this+0xc
public:
  hsKeyedObject::hsKeyedObject(const class hsKeyedObject &);
  //hsKeyedObject::hsKeyedObject();
  hsKeyedObject::~hsKeyedObject();
  const char * hsKeyedObject::ClassName();
  virtual unsigned short hsKeyedObject::ClassIndex();
  static unsigned short Index();
  static class hsKeyedObject * Create();
  static const class hsKeyedObject * ConvertNoRef(const class plCreatable *);
  static class hsKeyedObject * hsKeyedObject::ConvertNoRef(class plCreatable *);
  static class hsKeyedObject * Convert(class plCreatable *);
  static int HasDerivedClass(unsigned short);
  static int HasBaseClass(unsigned short);
  class plCreatable * hsKeyedObject::GetInterface(unsigned short);
  const class plCreatable * hsKeyedObject::GetConstInterface(unsigned short);
  const class plKey & hsKeyedObject::GetKey();
  const char * hsKeyedObject::GetKeyName();
  void hsKeyedObject::Validate();
  int hsKeyedObject::IsFinal();
  void hsKeyedObject::Read(class hsStream *, class hsResMgr *){}
  void hsKeyedObject::Write(class hsStream *, class hsResMgr *){}
  int hsKeyedObject::MsgReceive(class plMessage *);
  int hsKeyedObject::SendRef(class plRefMsg *, enum plRefFlags::Type);
  class plKey hsKeyedObject::RegisterAs(enum plFixedKeyId);
  void hsKeyedObject::UnRegisterAs(enum plFixedKeyId);
  class plKey hsKeyedObject::RegisterAsManual(class plUoid &, const char *);
  void hsKeyedObject::UnRegisterAsManual(class plUoid &);
  class hsKeyedObject * hsKeyedObject::GetSharedObject();

private:
  static void hsKeyedObject::SetClassIndex(unsigned short);

protected:
  void hsKeyedObject::SetKey(class plKey);
  void hsKeyedObject::UnRegister();
  static unsigned short hsKeyedObject::hsKeyedObjectClassIndex;
#endif
};

#endif

