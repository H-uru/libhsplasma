#include "plObjectInVolumeDetector.h"

/* plObjectInVolumeDetector */
plObjectInVolumeDetector::plObjectInVolumeDetector() { }
plObjectInVolumeDetector::~plObjectInVolumeDetector() { }

IMPLEMENT_CREATABLE(plObjectInVolumeDetector, kObjectInVolumeDetector,
                    plCollisionDetector)


/* plCameraRegionDetector */
plCameraRegionDetector::plCameraRegionDetector() { }

plCameraRegionDetector::~plCameraRegionDetector() {
    for (size_t i=0; i<fMessages.getSize(); i++)
        delete fMessages[i];
}

IMPLEMENT_CREATABLE(plCameraRegionDetector, kCameraRegionDetector,
                    plObjectInVolumeDetector)

void plCameraRegionDetector::read(hsStream* S, plResManager* mgr) {
    plDetectorModifier::read(S, mgr);

    clearMessages();
    fMessages.setSizeNull(S->readInt());
    for (size_t i=0; i<fMessages.getSize(); i++)
        fMessages[i] = plCameraMsg::Convert(mgr->ReadCreatable(S));
}

void plCameraRegionDetector::write(hsStream* S, plResManager* mgr) {
    plDetectorModifier::write(S, mgr);

    S->writeInt(fMessages.getSize());
    for (size_t i=0; i<fMessages.getSize(); i++)
        mgr->WriteCreatable(S, fMessages[i]);
}

void plCameraRegionDetector::IPrcWrite(pfPrcHelper* prc) {
    plDetectorModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Messages");
    for (size_t i=0; i<fMessages.getSize(); i++)
        fMessages[i]->prcWrite(prc);
    prc->closeTag();
}

void plCameraRegionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Messages") {
        clearMessages();
        fMessages.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMessages.getSize(); i++) {
            fMessages[i] = plCameraMsg::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);
    }
}

void plCameraRegionDetector::clearMessages() {
    for (size_t i=0; i<fMessages.getSize(); i++)
        delete fMessages[i];
    fMessages.clear();
}


/* plObjectInVolumeAndFacingDetector */
plObjectInVolumeAndFacingDetector::plObjectInVolumeAndFacingDetector()
    : fFacingTolerance(0.0f), fNeedWalkingForward(false) { }

plObjectInVolumeAndFacingDetector::~plObjectInVolumeAndFacingDetector() { }

IMPLEMENT_CREATABLE(plObjectInVolumeAndFacingDetector,
                    kObjectInVolumeAndFacingDetector,
                    plObjectInVolumeDetector)

void plObjectInVolumeAndFacingDetector::read(hsStream* S, plResManager* mgr) {
    plObjectInVolumeDetector::read(S, mgr);
    fFacingTolerance = S->readFloat();
    fNeedWalkingForward = S->readBool();
}

void plObjectInVolumeAndFacingDetector::write(hsStream* S, plResManager* mgr) {
    plObjectInVolumeDetector::write(S, mgr);
    S->writeFloat(fFacingTolerance);
    S->writeBool(fNeedWalkingForward);
}

void plObjectInVolumeAndFacingDetector::IPrcWrite(pfPrcHelper* prc) {
    plObjectInVolumeDetector::IPrcWrite(prc);

    prc->startTag("FacingParams");
    prc->writeParam("Tolerance", fFacingTolerance);
    prc->writeParam("NeedWalkingForward", fNeedWalkingForward);
    prc->endTag(true);
}

void plObjectInVolumeAndFacingDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FacingParams") {
        fFacingTolerance = tag->getParam("Tolerance", "0").toFloat();
        fNeedWalkingForward = tag->getParam("NeedWalkingForward", "false").toBool();
    } else {
        plObjectInVolumeDetector::IPrcParse(tag, mgr);
    }
}
