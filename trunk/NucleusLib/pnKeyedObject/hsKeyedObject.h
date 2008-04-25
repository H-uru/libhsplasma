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
    plKey myKey;
    unsigned int koFlags;

public:
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    
    const plKey& getKey() const;
};

#endif
