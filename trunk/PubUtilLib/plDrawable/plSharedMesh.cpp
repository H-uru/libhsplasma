#include "plSharedMesh.h"
#include "../plResMgr/plResManager.h"

plSharedMesh::plSharedMesh(PlasmaVer pv) : fFlags(1) { }
plSharedMesh::~plSharedMesh() { }

short plSharedMesh::ClassIndex() {
    return (ver == pvEoa ? -1 : 0x00CC);
}

void plSharedMesh::read(hsStream *S) {
    //
}

void plSharedMesh::write(hsStream *S) {
    //
}
