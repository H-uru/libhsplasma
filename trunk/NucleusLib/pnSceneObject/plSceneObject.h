#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "CoreLib/hsTArray.hpp"

DllClass plSceneObject : public plSynchedObject {
public:
    plKey DrawIntf;
    plKey SimIntf;
    plKey CoordIntf;
    plKey AudioIntf;

    hsTArray<plKey> Interfaces;
    hsTArray<plKey> Modifiers;

    plKey SceneNode;

public:
    plSceneObject();
    virtual ~plSceneObject();

    DECLARE_CREATABLE(plSceneObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
