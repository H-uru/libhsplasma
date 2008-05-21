#include "plBoundInterface.h"

plBoundInterface::plBoundInterface() : fBounds(NULL) { }

plBoundInterface::~plBoundInterface() {
    if (fBounds) delete fBounds;
}

IMPLEMENT_CREATABLE(plBoundInterface, kBoundInterface, plObjInterface)

void plBoundInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    fBounds = plConvexVolume::Convert(mgr->ReadCreatable(S));
}

void plBoundInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    mgr->WriteCreatable(S, fBounds);
}

void plBoundInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Bounds");
    fBounds->prcWrite(prc);
    prc->closeTag();
}

void plBoundInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Bounds") {
        if (tag->hasChildren())
            fBounds = plConvexVolume::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
