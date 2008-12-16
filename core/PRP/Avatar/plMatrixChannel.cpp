#include "plMatrixChannel.h"

/* plMatrixChannel */
plMatrixChannel::plMatrixChannel() { }
plMatrixChannel::~plMatrixChannel() { }

IMPLEMENT_CREATABLE(plMatrixChannel, kMatrixChannel, plAGChannel)

hsAffineParts plMatrixChannel::getAffine() const { return fAP; }
void plMatrixChannel::setAffine(const hsAffineParts& ap) { fAP = ap; }


/* plMatrixBlend */
plMatrixBlend::plMatrixBlend() { }
plMatrixBlend::~plMatrixBlend() { }

IMPLEMENT_CREATABLE(plMatrixBlend, kMatrixBlend, plMatrixChannel)


/* plMatrixConstant */
plMatrixConstant::plMatrixConstant() { }
plMatrixConstant::~plMatrixConstant() { }

IMPLEMENT_CREATABLE(plMatrixConstant, kMatrixConstant, plMatrixChannel)

void plMatrixConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fAP.read(S);
}

void plMatrixConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    fAP.write(S);
}

void plMatrixConstant::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}

void plMatrixConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AffineParts") {
        if (tag->hasChildren())
            fAP.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plMatrixControllerCacheChannel */
plMatrixControllerCacheChannel::plMatrixControllerCacheChannel() { }
plMatrixControllerCacheChannel::~plMatrixControllerCacheChannel() { }

IMPLEMENT_CREATABLE(plMatrixControllerCacheChannel,
                    kMatrixControllerCacheChannel,
                    plMatrixChannel)


/* plMatrixControllerChannel */
plMatrixControllerChannel::plMatrixControllerChannel() : fController(NULL) { }

plMatrixControllerChannel::~plMatrixControllerChannel() {
    if (fController != NULL)
        delete fController;
}

IMPLEMENT_CREATABLE(plMatrixControllerChannel, kMatrixControllerChannel,
                    plMatrixChannel)

void plMatrixControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fController = plController::Convert(mgr->ReadCreatable(S));
    fAP.read(S);
}

void plMatrixControllerChannel::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    mgr->WriteCreatable(S, fController);
    fAP.write(S);
}

void plMatrixControllerChannel::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}

void plMatrixControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            fController = plController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "AffineParts") {
        if (tag->hasChildren())
            fAP.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

plController* plMatrixControllerChannel::getController() const { return fController; }

void plMatrixControllerChannel::setController(plController* controller) {
    if (fController != NULL)
        delete fController;
    fController = controller;
}


/* plMatrixTimeScale */
plMatrixTimeScale::plMatrixTimeScale() { }
plMatrixTimeScale::~plMatrixTimeScale() { }

IMPLEMENT_CREATABLE(plMatrixTimeScale, kMatrixTimeScale, plMatrixChannel)


/* plQuatPointCombine */
plQuatPointCombine::plQuatPointCombine() { }
plQuatPointCombine::~plQuatPointCombine() { }

IMPLEMENT_CREATABLE(plQuatPointCombine, kQuatPointCombine, plMatrixChannel)


/* plMatrixChannelApplicator */
plMatrixChannelApplicator::plMatrixChannelApplicator() { }
plMatrixChannelApplicator::~plMatrixChannelApplicator() { }

IMPLEMENT_CREATABLE(plMatrixChannelApplicator, kMatrixChannelApplicator,
                    plAGApplicator)


/* plIK2Applicator */
/* Doesn't have unique Creatable Index
plIK2Applicator::plIK2Applicator() { }
plIK2Applicator::~plIK2Applicator() { }

IMPLEMENT_CREATABLE(plIK2Applicator, kIK2Applicator, plMatrixChannelApplicator)
*/


/* plMatrixDelayedCorrectionApplicator */
plMatrixDelayedCorrectionApplicator::plMatrixDelayedCorrectionApplicator() { }
plMatrixDelayedCorrectionApplicator::~plMatrixDelayedCorrectionApplicator() { }

IMPLEMENT_CREATABLE(plMatrixDelayedCorrectionApplicator,
                    kMatrixDelayedCorrectionApplicator,
                    plMatrixChannelApplicator)


/* plMatrixDifferenceApp */
plMatrixDifferenceApp::plMatrixDifferenceApp() { }
plMatrixDifferenceApp::~plMatrixDifferenceApp() { }

IMPLEMENT_CREATABLE(plMatrixDifferenceApp, kMatrixDifferenceApp,
                    plMatrixChannelApplicator)


/* plRelativeMatrixChannelApplicator */
plRelativeMatrixChannelApplicator::plRelativeMatrixChannelApplicator() { }
plRelativeMatrixChannelApplicator::~plRelativeMatrixChannelApplicator() { }

IMPLEMENT_CREATABLE(plRelativeMatrixChannelApplicator,
                    kRelativeMatrixChannelApplicator,
                    plAGApplicator)
