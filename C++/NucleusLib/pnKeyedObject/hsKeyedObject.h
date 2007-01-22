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
    plKey myKey;
    unsigned int koFlags;

public:
    hsKeyedObject(PlasmaVer pv = pvUnknown);
    virtual ~hsKeyedObject();

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);
};

#endif

