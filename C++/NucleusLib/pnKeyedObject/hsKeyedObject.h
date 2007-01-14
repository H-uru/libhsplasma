#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

class hsKeyedObject : public plReceiver {
public:
    hsKeyedObject(PlasmaVer pv = pvUnknown);
    ~hsKeyedObject();

    void read(hsStream * S);
    void write(hsStream * S);
};

#endif

