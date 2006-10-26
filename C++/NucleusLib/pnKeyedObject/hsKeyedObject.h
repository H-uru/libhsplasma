#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "../../plReceiver.h"

class hsKeyedObject : public plReceiver {
public:
    hsKeyedObject();
    ~hsKeyedObject();

    const char* getTypeName();
    const int getTypeNum();

    void read(hsStream * S);
    void write(hsStream * S);
};

#endif

