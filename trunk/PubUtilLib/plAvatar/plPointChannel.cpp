#include "plPointChannel.h"

// plPointChannel //
plPointChannel::plPointChannel() { }
plPointChannel::~plPointChannel() { }

IMPLEMENT_CREATABLE(plPointChannel, kPointChannel, plAGChannel)


// plPointBlend //
plPointBlend::plPointBlend() { }
plPointBlend::~plPointBlend() { }

IMPLEMENT_CREATABLE(plPointBlend, kPointBlend, plPointChannel)


// plPointConstant //
plPointConstant::plPointConstant() { }
plPointConstant::~plPointConstant() { }

IMPLEMENT_CREATABLE(plPointConstant, kPointConstant, plPointChannel)

void plPointConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fResult.read(S);
}

void plPointConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    fResult.write(S);
}

void plPointConstant::prcWrite(pfPrcHelper* prc) {
    plAGChannel::prcWrite(prc);

    prc->writeSimpleTag("Result");
    fResult.prcWrite(prc);
    prc->closeTag();
}


// plPointControllerCacheChannel //
plPointControllerCacheChannel::plPointControllerCacheChannel() { }
plPointControllerCacheChannel::~plPointControllerCacheChannel() { }

IMPLEMENT_CREATABLE(plPointControllerCacheChannel,
                    kPointControllerCacheChannel,
                    plPointChannel)


// plPointControllerChannel //
plPointControllerChannel::plPointControllerChannel() { }
plPointControllerChannel::~plPointControllerChannel() { }

IMPLEMENT_CREATABLE(plPointControllerChannel, kPointControllerChannel,
                    plPointChannel)

void plPointControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fController = plController::Convert(mgr->ReadCreatable(S));
}

void plPointControllerChannel::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    mgr->WriteCreatable(S, fController);
}

void plPointControllerChannel::prcWrite(pfPrcHelper* prc) {
    plAGChannel::prcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc); prc->closeTag();
    prc->closeTag();
}


// plPointTimeScale //
plPointTimeScale::plPointTimeScale() { }
plPointTimeScale::~plPointTimeScale() { }

IMPLEMENT_CREATABLE(plPointTimeScale, kPointTimeScale, plPointChannel)


// plPointChannelApplicator //
plPointChannelApplicator::plPointChannelApplicator() { }
plPointChannelApplicator::~plPointChannelApplicator() { }

IMPLEMENT_CREATABLE(plPointChannelApplicator, kPointChannelApplicator,
                    plAGApplicator)
