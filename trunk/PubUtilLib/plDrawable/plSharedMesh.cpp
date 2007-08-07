#include "plSharedMesh.h"
#include "../plResMgr/plResManager.h"

plSharedMesh::plSharedMesh() : fFlags(1) { }
plSharedMesh::~plSharedMesh() { }

IMPLEMENT_CREATABLE(plSharedMesh, kSharedMesh, hsKeyedObject)

void plSharedMesh::read(hsStream* S) {
    //
}

void plSharedMesh::write(hsStream* S) {
    //
}
