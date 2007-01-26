#ifndef _PLCOORDINATEINTERFACE_H
#define _PLCOORDINATEINTERFACE_H

#include "plObjInterface.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsMatrix44.h"

class plCoordinateInterface : public plObjInterface {
public: // Might as well make 'em public...
    hsMatrix44 LocalToParent;
    hsMatrix44 ParentToLocal;
    hsMatrix44 LocalToWorld;
    hsMatrix44 WorldToLocal;
    hsTArray<plKey*> SceneObjects;

    //short Member60;
    //hsTArray<plSceneObject> Children;
    plCoordinateInterface * Parent;

public:
    plCoordinateInterface(PlasmaVer pv = pvUnknown);
    virtual ~plCoordinateInterface();

    virtual short ClassIndex();

    plCoordinateInterface * getRoot();

    // More to do later...

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

