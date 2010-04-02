#ifndef _HSGDEVICEREF_H
#define _HSGDEVICEREF_H

#include "PlasmaDefs.h"

DllClass hsGDeviceRef /*: public hsRefCnt*/ {
public:
    enum { kNone, kDirty };

protected:
    unsigned int flags, useTime;

public:
    hsGDeviceRef();

    bool IsDirty();
    void SetDirty(bool dirty);
};

#endif
