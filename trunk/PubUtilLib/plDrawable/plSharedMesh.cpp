#include "plSharedMesh.h"
#include "../plResMgr/plResManager.h"

plSharedMesh::plSharedMesh(PlasmaVer pv) { 
	fFlags = 1;
}

unsigned short plSharedMesh::ClassIndex() { return 0x00CC; }
const char* plSharedMesh::ClassName() { return "plSharedMesh"; }

int plSharedMesh::MsgReceive(plMessage *msg)
{
	return 4;// hsKeyedObject::MsgReceive(msg);
}