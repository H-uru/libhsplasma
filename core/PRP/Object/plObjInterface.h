#ifndef _PLOBJINTERFACE_H
#define _PLOBJINTERFACE_H

#include "Util/hsBitVector.h"
#include "plSynchedObject.h"

DllClass plObjInterface : public plSynchedObject {
public:
    enum { kDisable };

protected:
    plKey fOwner;
    hsBitVector fProps;

public:
    plObjInterface();
    virtual ~plObjInterface();

    DECLARE_CREATABLE(plObjInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsBitVector& getProperties();
    bool getProperty(size_t prop) const;
    void setProperty(size_t prop, bool value);
    plKey getOwner() const;
    void setOwner(plKey owner);
};

#endif
