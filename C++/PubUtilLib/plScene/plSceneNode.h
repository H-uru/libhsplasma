#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsTArray.hpp"

class plSceneNode : public hsKeyedObject {
public:
    hsTArray<plKey> SceneObjects;
    hsTArray<plKey> OtherObjects;

public:
    plSceneNode(PlasmaVer pv = pvUnknown);
    virtual ~plSceneNode();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

