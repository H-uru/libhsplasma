#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

DllClass hsKeyedObject : public plReceiver {
private:
    plKey myKey;

public:
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)

    /**
     * Initializes the key for this KeyedObject with the specified
     * object name.  You will need to either set the location manually
     * or add it to the ResManager for the key's location to be valid.
     * \sa plResManager::AddKey(), plResManager::AddObject()
     */
    void init(const plString& name);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    
public:
    /** Returns the key that describes this object */
    plKey getKey() const;

    /**
     * Set the object's key.  Most of the time, you will never need to
     * use this directly; you should use init() instead
     * \sa init(), plResManager::AddKey(), plResManager::AddObject()
     */
    void setKey(plKey key);
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plCreatableStub* getStub() const;
    void setStub(plCreatableStub* stub);
};

#endif
