#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "../pnNetCommon/plSynchedObject.h"

class plSceneObject : public plSynchedObject {
public:
    plKey * DrawIntf;
    plKey * SimIntf;
    plKey * CoordIntf;
    plKey * AudioIntf;

    hsTArray<plKeyRef> Interfaces;
    hsTArray<plKeyRef> Modifiers;

    plKey * SceneNode;

public:
    plSceneObject();
    ~plSceneObject();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

