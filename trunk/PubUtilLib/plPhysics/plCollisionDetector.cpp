#include "plCollisionDetector.h"

/* plCollisionDetector */
plCollisionDetector::plCollisionDetector()
                   : fType(0), fBumped(false), fTriggered(false) { }
plCollisionDetector::~plCollisionDetector() { }

IMPLEMENT_CREATABLE(plCollisionDetector, kCollisionDetector, plDetectorModifier)

void plCollisionDetector::read(hsStream* S, plResManager* mgr) {
    plDetectorModifier::read(S, mgr);
    fType = S->readByte();
}

void plCollisionDetector::write(hsStream* S, plResManager* mgr) {
    plDetectorModifier::write(S, mgr);
    S->writeByte(fType);
}

void plCollisionDetector::prcWrite(pfPrcHelper* prc) {
    plDetectorModifier::prcWrite(prc);

    prc->startTag("CollisionType");
    prc->writeParam("value", fType);
    prc->endTag(true);
}


/* plSubworldRegionDetector */
plSubworldRegionDetector::plSubworldRegionDetector() : fOnExit(false) { }
plSubworldRegionDetector::~plSubworldRegionDetector() { }

IMPLEMENT_CREATABLE(plSubworldRegionDetector, kSubworldRegionDetector, plCollisionDetector)

void plSubworldRegionDetector::read(hsStream* S, plResManager* mgr) {
    plDetectorModifier::read(S, mgr);
    fSub = mgr->readKey(S);
    fOnExit = S->readBool();
}

void plSubworldRegionDetector::write(hsStream* S, plResManager* mgr) {
    plDetectorModifier::write(S, mgr);
    mgr->writeKey(S, fSub);
    S->writeBool(fOnExit);
}

void plSubworldRegionDetector::prcWrite(pfPrcHelper* prc) {
    plDetectorModifier::prcWrite(prc);

    prc->startTag("SubworldParams");
    prc->writeParam("OnExit", fOnExit);
    prc->endTag(true);

    prc->writeSimpleTag("Subworld");
    fSub->prcWrite(prc);
    prc->closeTag();
}


/* plPanicLinkRegion */
plPanicLinkRegion::plPanicLinkRegion() : fPlayLinkOutAnim(true) { }
plPanicLinkRegion::~plPanicLinkRegion() { }

IMPLEMENT_CREATABLE(plPanicLinkRegion, kPanicLinkRegion, plCollisionDetector)

void plPanicLinkRegion::read(hsStream* S, plResManager* mgr) {
    plCollisionDetector::read(S, mgr);
    fPlayLinkOutAnim = S->readBool();
}

void plPanicLinkRegion::write(hsStream* S, plResManager* mgr) {
    plCollisionDetector::write(S, mgr);
    S->writeBool(fPlayLinkOutAnim);
}

void plPanicLinkRegion::prcWrite(pfPrcHelper* prc) {
    plCollisionDetector::prcWrite(prc);

    prc->startTag("PanicLinkParams");
    prc->writeParam("PlayLinkOutAnim", fPlayLinkOutAnim);
    prc->endTag(true);
}
