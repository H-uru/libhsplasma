#ifndef _PLCOORDINATEINTERFACE_H
#define _PLCOORDINATEINTERFACE_H

#include "plObjInterface.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../hsMatrix44.h"

class plCoordinateInterface : public plObjInterface {
public: // Might as well make 'em public...
    hsMatrix44 LocalToParent;
    hsMatrix44 ParentToLocal;
    hsMatrix44 LocalToWorld;
    hsMatrix44 WorldToLocal;
    hsTArray<plKeyRef> SceneObjects;

    //short Member60;
    //hsTArray<plSceneObject> Children;
    plCoordinateInterface * Parent;

public:
    plCoordinateInterface();
    ~plCoordinateInterface();

    plCoordinateInterface * getRoot();

    // More to do later...

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

