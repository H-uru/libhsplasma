#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

DllClass plDrawInterface : public plObjInterface {
public:
    hsTArray<plKey> fDrawables;
    hsTArray<plKey> fRegions;
    hsTArray<int> fDrawableKeys;

public:
    plDrawInterface();
    virtual ~plDrawInterface();

    DECLARE_CREATABLE(plDrawInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumDrawables() const;
    plKey getDrawable(size_t idx) const;
    int getDrawableKey(size_t idx) const;
    void clearDrawables();
    void addDrawable(plKey draw, int key);

    size_t getNumRegions() const;
    plKey getRegion(size_t idx) const;
    void clearRegions();
    void addRegion(plKey obj);
};

#endif
