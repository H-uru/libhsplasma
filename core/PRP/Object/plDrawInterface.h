#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

DllClass plDrawInterface : public plObjInterface {
public:
    hsTArray<plKey> fDrawables;
    hsTArray<plKey> fObjects;
    hsTArray<int> fDrawableKeys;

public:
    plDrawInterface();
    virtual ~plDrawInterface();

    DECLARE_CREATABLE(plDrawInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    size_t getNumDrawables() const;
    plKey getDrawable(size_t idx) const;
    int getDrawableKey(size_t idx) const;

    size_t getNumObjects() const;
    plKey getObject(size_t idx) const;
};

#endif

