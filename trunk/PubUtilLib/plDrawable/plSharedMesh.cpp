#include "plSharedMesh.h"
#include "../plResMgr/plResManager.h"

plSharedMesh::plSharedMesh() : fFlags(1) { }
plSharedMesh::~plSharedMesh() { }

short plSharedMesh::ClassIndex() { return kSharedMesh; }
short plSharedMesh::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kSharedMesh, ver);
}

void plSharedMesh::read(hsStream *S) {
    //
}

void plSharedMesh::write(hsStream *S) {
    //
}
