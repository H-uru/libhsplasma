#include "plCollisionDetector.h"

/* plCollisionDetector */
plCollisionDetector::plCollisionDetector() : fType(0) { }
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

void plCollisionDetector::IPrcWrite(pfPrcHelper* prc) {
    plDetectorModifier::IPrcWrite(prc);

    prc->startTag("CollisionType");
    prc->writeParam("value", fType);
    prc->endTag(true);
}

void plCollisionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CollisionType") {
        fType = tag->getParam("value", "0").toUint();
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);
    }
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

void plSubworldRegionDetector::IPrcWrite(pfPrcHelper* prc) {
    plDetectorModifier::IPrcWrite(prc);

    prc->startTag("SubworldParams");
    prc->writeParam("OnExit", fOnExit);
    prc->endTag(true);

    prc->writeSimpleTag("Subworld");
    fSub->prcWrite(prc);
    prc->closeTag();
}

void plSubworldRegionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SubworldParams") {
        fOnExit = tag->getParam("OnExit", "false").toBool();
    } else if (tag->getName() == "Subworld") {
        if (tag->hasChildren())
            fSub = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);
    }
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

void plPanicLinkRegion::IPrcWrite(pfPrcHelper* prc) {
    plCollisionDetector::IPrcWrite(prc);

    prc->startTag("PanicLinkParams");
    prc->writeParam("PlayLinkOutAnim", fPlayLinkOutAnim);
    prc->endTag(true);
}

void plPanicLinkRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "PanicLinkParams") {
        fPlayLinkOutAnim = tag->getParam("PlayLinkOutAnim", "true").toBool();
    } else {
        plCollisionDetector::IPrcParse(tag, mgr);
    }
}
