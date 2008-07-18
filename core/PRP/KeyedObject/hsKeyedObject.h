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
    plWeakKey myKey;
    unsigned int koFlags;

public:
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    
    const plWeakKey& getKey() const;
};

DllClass hsKeyedObjectStub : public hsKeyedObject {
protected:
    plCreatableStub* fStub;

public:
    hsKeyedObjectStub();
    virtual ~hsKeyedObjectStub();

    virtual short ClassIndex() const;
    virtual const char* ClassName() const;

    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    const plCreatableStub* getStub() const;
    void setStub(plCreatableStub* stub);
};

#endif
