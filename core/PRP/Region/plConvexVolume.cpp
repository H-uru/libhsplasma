#include "plConvexVolume.h"

void plConvexVolume::read(hsStream* S, plResManager* mgr) {
    fLocalPlanes.setSize(S->readInt());
    for (size_t i=0; i<fLocalPlanes.getSize(); i++)
        fLocalPlanes[i].read(S);
}

void plConvexVolume::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fLocalPlanes.getSize());
    for (size_t i=0; i<fLocalPlanes.getSize(); i++)
        fLocalPlanes[i].write(S);
}

void plConvexVolume::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fLocalPlanes.getSize(); i++)
        fLocalPlanes[i].prcWrite(prc);
    prc->closeTag();
}

void plConvexVolume::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Planes") {
        fLocalPlanes.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLocalPlanes.getSize(); i++) {
            fLocalPlanes[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
