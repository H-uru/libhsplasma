#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

class hsKeyedObject : public plReceiver {
public:
    hsKeyedObject(PlasmaVer pv = pvUnknown);
    virtual ~hsKeyedObject();

    virtual void read(hsStream * S);
    virtual void write(hsStream * S);
};

#endif

