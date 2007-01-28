#ifndef PLSHAREDMESH_H
#define PLSHAREDMESH_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"

class plSharedMesh : public hsKeyedObject {

public:
	hsTArray<plSceneObject const*> fActiveInstances; //this+0x18
    unsigned char fFlags; //this+0x24

public:
	plSharedMesh(PlasmaVer pv = pvUnknown);
   // virtual ~plSharedMesh();

    virtual unsigned short ClassIndex();
	virtual const char* ClassName();

    /*virtual void read(hsStream *S);
    virtual void write(hsStream *S);*/
	virtual int MsgReceive(plMessage *msg);
};

#endif
