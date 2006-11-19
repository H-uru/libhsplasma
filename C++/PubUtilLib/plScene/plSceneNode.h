#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsTArray.hpp"

class plSceneNode : public hsKeyedObject {
public:
    hsTArray<plKeyRef> SceneObjects;
    hsTArray<plKeyRef> OtherObjects;

public:
    plSceneNode();
    ~plSceneNode();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

