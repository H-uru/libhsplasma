#include "plHardRegion.h"

// plHardRegion //
plHardRegion::plHardRegion() : fState(kDirty) { }
plHardRegion::~plHardRegion() { }

IMPLEMENT_CREATABLE(plHardRegion, kHardRegion, plRegionBase)


// plHardRegionComplex //
plHardRegionComplex::plHardRegionComplex() { }
plHardRegionComplex::~plHardRegionComplex() { }

IMPLEMENT_CREATABLE(plHardRegionComplex, kHardRegionComplex, plHardRegion)

void plHardRegionComplex::read(hsStream* S, plResManager* mgr) {
    plHardRegion::read(S, mgr);

    fSubRegions.setSize(S->readInt());
    for (size_t i=0; i<fSubRegions.getSize(); i++)
        fSubRegions[i] = mgr->readKey(S);
}

void plHardRegionComplex::write(hsStream* S, plResManager* mgr) {
    plHardRegion::write(S, mgr);

    S->writeInt(fSubRegions.getSize());
    for (size_t i=0; i<fSubRegions.getSize(); i++)
        mgr->writeKey(S, fSubRegions[i]);
}

void plHardRegionComplex::IPrcWrite(pfPrcHelper* prc) {
    plHardRegion::IPrcWrite(prc);

    prc->writeSimpleTag("SubRegions");
    for (size_t i=0; i<fSubRegions.getSize(); i++)
        fSubRegions[i]->prcWrite(prc);
    prc->closeTag();
}

void plHardRegionComplex::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SubRegions") {
        fSubRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSubRegions.getSize(); i++) {
            fSubRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plHardRegion::IPrcParse(tag, mgr);
    }
}


// plHardRegionIntersect //
plHardRegionIntersect::plHardRegionIntersect() { }
plHardRegionIntersect::~plHardRegionIntersect() { }

IMPLEMENT_CREATABLE(plHardRegionIntersect, kHardRegionIntersect,
                    plHardRegionComplex)


// plHardRegionInvert //
plHardRegionInvert::plHardRegionInvert() { }
plHardRegionInvert::~plHardRegionInvert() { }

IMPLEMENT_CREATABLE(plHardRegionInvert, kHardRegionInvert, plHardRegionComplex)


// plHardRegionUnion //
plHardRegionUnion::plHardRegionUnion() { }
plHardRegionUnion::~plHardRegionUnion() { }

IMPLEMENT_CREATABLE(plHardRegionUnion, kHardRegionUnion, plHardRegionComplex)
