#include "plConvexVolume.h"

plConvexVolume::plConvexVolume()
              : fLocalPlanes(NULL), fNumPlanes(0) { }

plConvexVolume::~plConvexVolume() {
    if (fLocalPlanes)
        delete[] fLocalPlanes;
}

IMPLEMENT_CREATABLE(plConvexVolume, kConvexVolume, plCreatable)

void plConvexVolume::read(hsStream* S, plResManager* mgr) {
    if (fLocalPlanes)
        delete[] fLocalPlanes;

    fNumPlanes = S->readInt();
    fLocalPlanes = new hsPlane3[fNumPlanes];
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].read(S);
}

void plConvexVolume::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fNumPlanes);
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].write(S);
}

void plConvexVolume::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Planes");
    for (unsigned int i=0; i<fNumPlanes; i++)
        fLocalPlanes[i].prcWrite(prc);
    prc->closeTag();
}

void plConvexVolume::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Planes") {
        fNumPlanes = tag->countChildren();
        fLocalPlanes = new hsPlane3[fNumPlanes];
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumPlanes; i++) {
            fLocalPlanes[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
