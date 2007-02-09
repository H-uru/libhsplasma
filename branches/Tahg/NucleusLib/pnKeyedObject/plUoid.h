#ifndef PLUOID_H
#define PLUOID_H

#include "../../CoreLib/plLoadMask.h"

class plLocation {
  unsigned long fSequenceNumber; //this+0x0
  unsigned long fFlags; //this+0x4

public:
  plLocation::~plLocation(){}
  void plLocation::Invalidate(){}
  int plLocation::IsValid(){}
  int plLocation::IsReserved(){}
  int plLocation::IsItinerant(){}
  void plLocation::Set(unsigned long){}
  unsigned long plLocation::GetSequenceNumber(){}
  int plLocation::IsVirtual(){}
  void plLocation::SetFlags(unsigned long){}
  unsigned long plLocation::GetFlags(){}
  void plLocation::Read(class hsStream *){}
  void plLocation::Write(class hsStream *){}
  bool plLocation::operator==(const class plLocation &){}
  bool plLocation::operator!=(const class plLocation &){}
  bool plLocation::operator<(const class plLocation &){}
  char * plLocation::StringIze(char *){}
  static class plLocation plLocation::MakeReserved(unsigned long){}
  static class plLocation plLocation::MakeNormal(unsigned long){}

protected:
  plLocation::plLocation(const class plLocation &){}
  plLocation::plLocation(){}
  plLocation::plLocation(unsigned long, unsigned long){}

  friend plUoid;
};

class plUoid {
  class plLocation fLocation; //this+0x0
  class plLoadMask fLoadMask; //this+0x8
  unsigned short fClassType; //this+0xa
  char * fObjectName; //this+0xc
  unsigned long fObjectID; //this+0x10
  unsigned long fClonePlayerID; //this+0x14
  unsigned long fCloneID; //this+0x18

public:
  plUoid::plUoid(const class plUoid &){}
  plUoid::plUoid(enum plFixedKeyId){}
  plUoid::plUoid(){}
  plUoid::plUoid(const class plLocation &, unsigned short, const char *, const class plLoadMask &){}
  plUoid::~plUoid(){}
  const class plLocation & plUoid::GetLocation(){}
  unsigned short plUoid::GetClassType(){}
  const char * plUoid::GetObjectName(){}
  const class plLoadMask & plUoid::GetLoadMask(){}
  void plUoid::Read(class hsStream *){}
  void plUoid::Write(class hsStream *){}
  void plUoid::Invalidate(){}
  int plUoid::IsValid(){}
  bool plUoid::operator==(const class plUoid &){}
  bool plUoid::operator!=(const class plUoid &){}
  bool plUoid::IsClone(){}
  unsigned long plUoid::GetClonePlayerID(){}
  unsigned long plUoid::GetCloneID(){}
  void plUoid::SetClone(unsigned long, unsigned long){}
  unsigned long plUoid::GetObjectID(){}
  void plUoid::SetObjectID(unsigned long){}
  char * plUoid::StringIze(char *){}
};

#endif
