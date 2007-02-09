#ifndef HSGDEVICEREF_H
#define HSGDEVICEREF_H

#include "../../CoreLib/hsRefCnt.h"

class hsGDeviceRef : public hsRefCnt {
  unsigned long fFlags; //this+0x8
  unsigned long fUseTime; //this+0xc

public:
  unsigned long hsGDeviceRef::IsDirty(){}
  void hsGDeviceRef::SetDirty(unsigned long){}
  hsGDeviceRef(const class hsGDeviceRef &){}
  hsGDeviceRef::hsGDeviceRef(){}
  hsGDeviceRef::~hsGDeviceRef(){}
};

#endif
