#ifndef _PLOCCLUDER_H
#define _PLOCCLUDER_H

#include "PRP/Object/plObjInterface.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
#include "plCullPoly.h"

DllClass plOccluder : public plObjInterface {
protected:
    hsTArray<plCullPoly> fPolys;
    hsBitVector fVisSet;
    hsTArray<plKey> fVisRegions;
    hsBitVector fVisNot;
    float fPriority;
    hsBounds3Ext fWorldBounds;
    plWeakKey fSceneNode;

public:
    plOccluder();
    virtual ~plOccluder();

    DECLARE_CREATABLE(plOccluder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plMobileOccluder : public plOccluder {
protected:
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    hsBounds3Ext fLocalBounds;
    hsTArray<plCullPoly> fOrigPolys;

public:
    plMobileOccluder();
    virtual ~plMobileOccluder();

    DECLARE_CREATABLE(plMobileOccluder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
