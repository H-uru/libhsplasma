#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "plSynchedObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneObject : public plSynchedObject {
public:
    plKey fDrawIntf, fSimIntf, fCoordIntf, fAudioIntf;
    hsTArray<plKey> fInterfaces, fModifiers;
    plWeakKey fSceneNode;

public:
    plSceneObject();
    virtual ~plSceneObject();

    DECLARE_CREATABLE(plSceneObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
