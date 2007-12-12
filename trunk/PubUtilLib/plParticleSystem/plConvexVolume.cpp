#include "plConvexVolume.h"

plConvexVolume::plConvexVolume()
              : fLocalPlanes(NULL), fWorldPlanes(NULL), fNumPlanes(0) { }

plConvexVolume::~plConvexVolume() {
    if (fLocalPlanes)
        delete[] fLocalPlanes;
    if (fWorldPlanes)
        delete[] fWorldPlanes;
}

IMPLEMENT_CREATABLE(plConvexVolume, kConvexVolume, plCreatable)

void plConvexVolume::read(hsStream* S, plResManager* mgr) {
    if (fLocalPlanes)
        delete[] fLocalPlanes;
    if (fWorldPlanes)
        delete[] fWorldPlanes;

    fNumPlanes = S->readInt();
    fLocalPlanes = new hsPlane3[fNumPlanes];
    fWorldPlanes = new hsPlane3[fNumPlanes];
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].read(S);
}

void plConvexVolume::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fNumPlanes);
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].write(S);
}

void plConvexVolume::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);
    prc->writeSimpleTag("Planes");
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].prcWrite(prc);
    prc->closeTag();
}
