#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

DllClass hsKeyedObject : public plReceiver {
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
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
    
    plKey* getKey();
};

#endif

