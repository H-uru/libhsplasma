#include "plMatrixChannel.h"

// plMatrixChannel //
plMatrixChannel::plMatrixChannel() { }
plMatrixChannel::~plMatrixChannel() { }

IMPLEMENT_CREATABLE(plMatrixChannel, kMatrixChannel, plAGChannel)


// plMatrixBlend //
plMatrixBlend::plMatrixBlend() { }
plMatrixBlend::~plMatrixBlend() { }

IMPLEMENT_CREATABLE(plMatrixBlend, kMatrixBlend, plMatrixChannel)


// plMatrixConstant //
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

void plMatrixConstant::prcWrite(pfPrcHelper* prc) {
    plAGChannel::prcWrite(prc);

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}


// plMatrixControllerCacheChannel //
plMatrixControllerCacheChannel::plMatrixControllerCacheChannel() { }
plMatrixControllerCacheChannel::~plMatrixControllerCacheChannel() { }

IMPLEMENT_CREATABLE(plMatrixControllerCacheChannel,
                    kMatrixControllerCacheChannel,
                    plMatrixChannel)


// plMatrixControllerChannel //
plMatrixControllerChannel::plMatrixControllerChannel() { }
plMatrixControllerChannel::~plMatrixControllerChannel() { }

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

void plMatrixControllerChannel::prcWrite(pfPrcHelper* prc) {
    plAGChannel::prcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc); prc->closeTag();
    prc->closeTag();

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}


// plMatrixTimeScale //
plMatrixTimeScale::plMatrixTimeScale() { }
plMatrixTimeScale::~plMatrixTimeScale() { }

IMPLEMENT_CREATABLE(plMatrixTimeScale, kMatrixTimeScale, plMatrixChannel)


// plQuatPointCombine //
plQuatPointCombine::plQuatPointCombine() { }
plQuatPointCombine::~plQuatPointCombine() { }

IMPLEMENT_CREATABLE(plQuatPointCombine, kQuatPointCombine, plMatrixChannel)


// plMatrixChannelApplicator //
plMatrixChannelApplicator::plMatrixChannelApplicator() { }
plMatrixChannelApplicator::~plMatrixChannelApplicator() { }

IMPLEMENT_CREATABLE(plMatrixChannelApplicator, kMatrixChannelApplicator,
                    plAGApplicator)


/* Doesn't have unique Creatable Index
// plIK2Applicator //
plIK2Applicator::plIK2Applicator() { }
plIK2Applicator::~plIK2Applicator() { }

IMPLEMENT_CREATABLE(plIK2Applicator, kIK2Applicator, plMatrixChannelApplicator)
*/


// plMatrixDelayedCorrectionApplicator //
plMatrixDelayedCorrectionApplicator::plMatrixDelayedCorrectionApplicator() { }
plMatrixDelayedCorrectionApplicator::~plMatrixDelayedCorrectionApplicator() { }

IMPLEMENT_CREATABLE(plMatrixDelayedCorrectionApplicator,
                    kMatrixDelayedCorrectionApplicator,
                    plMatrixChannelApplicator)


// plMatrixDifferenceApp //
plMatrixDifferenceApp::plMatrixDifferenceApp() { }
plMatrixDifferenceApp::~plMatrixDifferenceApp() { }

IMPLEMENT_CREATABLE(plMatrixDifferenceApp, kMatrixDifferenceApp,
                    plMatrixChannelApplicator)
