#include "plFilterCoordInterface.h"

plFilterCoordInterface::plFilterCoordInterface() : fFilterMask(0) { }

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

void plFilterCoordInterface::IPrcWrite(pfPrcHelper* prc) {
    plCoordinateInterface::IPrcWrite(prc);

    prc->startTag("FilterParams");
    prc->writeParamHex("Mask", fFilterMask);
    prc->endTag(true);

    prc->writeSimpleTag("RefParentLocalToWorld");
    fRefParentLocalToWorld.prcWrite(prc);
    prc->closeTag();
}

void plFilterCoordInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FilterParams") {
        fFilterMask = tag->getParam("Mask", "0").toUint();
    } else if (tag->getName() == "RefParentLocalToWorld") {
        if (tag->hasChildren())
            fRefParentLocalToWorld.prcParse(tag->getFirstChild());
    } else {
        plCoordinateInterface::IPrcParse(tag, mgr);
    }
}
