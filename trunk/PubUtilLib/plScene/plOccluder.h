#ifndef _PLOCCLUDER_H
#define _PLOCCLUDER_H

#include "NucleusLib/pnSceneObject/plObjInterface.h"
#include "CoreLib/hsBounds.h"
#include "CoreLib/hsMatrix44.h"
#include "plCullPoly.h"

DllClass plOccluder : public plObjInterface {
protected:
    hsTArray<plCullPoly> fPolys;
    hsBitVector fVisSet;
    hsTArray<plKey> fVisRegions;
    hsBitVector fVisNot;
    float fPriority;
    hsBounds3Ext fWorldBounds;
    plKey fSceneNode;

public:
    plOccluder();
    virtual ~plOccluder();

    DECLARE_CREATABLE(plOccluder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
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
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
