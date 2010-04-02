#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

DllClass plDrawInterface : public plObjInterface {
    CREATABLE(plDrawInterface, kDrawInterface, plObjInterface)

protected:
    hsTArray<plKey> fDrawables;
    hsTArray<plKey> fRegions;
    hsTArray<int> fDrawableKeys;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumDrawables() const { return fDrawables.getSize(); }
    plKey getDrawable(size_t idx) const { return fDrawables[idx]; }
    int getDrawableKey(size_t idx) const { return fDrawableKeys[idx]; }
    void clearDrawables();
    void addDrawable(plKey draw, int key);
    void delDrawable(size_t idx);

    const hsTArray<plKey>& getRegions() const { return fRegions; }
    hsTArray<plKey>& getRegions() { return fRegions; }
    void addRegion(plKey obj) { fRegions.append(obj); }
    void delRegion(size_t idx) { fRegions.remove(idx); }
    void clearRegions() { fRegions.clear(); }
};


DllClass plInstanceDrawInterface : public plDrawInterface {
    CREATABLE(plInstanceDrawInterface, kInstanceDrawInterface, plDrawInterface)

protected:
    unsigned int fTargetID;
    plKey fDrawable;

public:
    plInstanceDrawInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
