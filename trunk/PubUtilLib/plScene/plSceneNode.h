#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsTArray.hpp"

class plSceneNode : public hsKeyedObject {
protected:
    bool filterGenerics;
    short depth;

public:
    hsTArray<plKey*> SceneObjects;
    hsTArray<plKey*> OtherObjects;
    //class hsTArray<plDrawable *> drawPool;
    //class hsTArray<plPhysical *> simulationPool;
    //class hsTArray<plAudible *> audioPool;
    //class hsTArray<plOccluder *> occluders;
    //class hsTArray<plLightInfo *> lightPool;
    //class plSpaceTree * spaceTree;

public:
    plSceneNode();
    virtual ~plSceneNode();

    DECLARE_CREATABLE(plSceneNode)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);

};

#endif

