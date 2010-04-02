#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "Util/hsBitVector.h"
#include "plSynchedObject.h"

DllClass plObjInterface : public plSynchedObject {
    CREATABLE(plObjInterface, kObjInterface, plSynchedObject)

public:
    enum { kDisable };

protected:
    plKey fOwner;
    hsBitVector fProps;

public:
    plObjInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getProperty(size_t prop) const { return fProps.get(prop); }
    void setProperty(size_t prop, bool value) { fProps.set(prop, value); }

    plKey getOwner() const { return fOwner; }
    void setOwner(plKey owner) { fOwner = owner; }
};

#endif
