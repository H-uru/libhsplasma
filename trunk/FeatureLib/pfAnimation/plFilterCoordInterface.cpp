#include "plFilterCoordInterface.h"

plFilterCoordInterface::plFilterCoordInterface() : fFilterMask(0) { }
plFilterCoordInterface::~plFilterCoordInterface() { }

IMPLEMENT_CREATABLE(plFilterCoordInterface, kFilterCoordInterface,
                    plCoordinateInterface)

void plFilterCoordInterface::read(hsStream* S, plResManager* mgr) {
    plCoordinateInterface::read(S, mgr);
    fFilterMask = S->readInt();
    fRefParentLocalToWorld.read(S);
}

void plFilterCoordInterface::write(hsStream* S, plResManager* mgr) {
    plCoordinateInterface::write(S, mgr);
    S->writeInt(fFilterMask);
    fRefParentLocalToWorld.write(S);
}

void plFilterCoordInterface::prcWrite(pfPrcHelper* prc) {
    plCoordinateInterface::prcWrite(prc);

    prc->startTag("FilterParams");
    prc->writeParam("Mask", fFilterMask);
    prc->endTag(true);

    prc->writeSimpleTag("RefParentLocalToWorld");
    fRefParentLocalToWorld.prcWrite(prc);
    prc->closeTag();
}
