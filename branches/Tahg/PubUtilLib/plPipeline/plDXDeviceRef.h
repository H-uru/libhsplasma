#ifndef PLDXDEVICEREF_H
#define PLDXDEVICEREF_H

#include "hsGDeviceRef.h"

class plDXDeviceRef : public hsGDeviceRef {
  class plDXDeviceRef * fNext; //this+0x10
  class plDXDeviceRef * * fBack; //this+0x14

public:
  void plDXDeviceRef::Unlink(){}
  void plDXDeviceRef::Link(class plDXDeviceRef * *){}
  class plDXDeviceRef * GetNext(){}
  int plDXDeviceRef::IsLinked(){}
  void plDXDeviceRef::Release(){}
  plDXDeviceRef(const class plDXDeviceRef &){}
  plDXDeviceRef::plDXDeviceRef(){}
  plDXDeviceRef::~plDXDeviceRef(){}
};

#endif
