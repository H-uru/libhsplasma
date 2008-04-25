#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"
#include "CoreLib/hsTArray.hpp"

DllClass plSceneObject : public plSynchedObject {
public:
    plKey fDrawIntf;
    plKey fSimIntf;
    plKey fCoordIntf;
    plKey fAudioIntf;

    hsTArray<plKey> fInterfaces;
    hsTArray<plKey> fModifiers;

    plKey fSceneNode;

public:
    plSceneObject();
    virtual ~plSceneObject();

    DECLARE_CREATABLE(plSceneObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
