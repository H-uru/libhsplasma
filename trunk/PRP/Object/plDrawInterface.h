#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"
#include "PRP/Geometry/plDrawableSpans.h"

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
    void VertexWrite(hsStream* S);
};

#endif

