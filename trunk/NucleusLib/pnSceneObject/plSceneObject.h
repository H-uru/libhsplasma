#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "../pnNetCommon/plSynchedObject.h"

class plSceneObject : public plSynchedObject {
public:
    plKey * DrawIntf;
    plKey * SimIntf;
    plKey * CoordIntf;
    plKey * AudioIntf;

    hsTArray<plKey*> Interfaces;
    hsTArray<plKey*> Modifiers;

    plKey * SceneNode;

public:
    plSceneObject(PlasmaVer pv = pvUnknown);
    virtual ~plSceneObject();

    virtual unsigned short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

