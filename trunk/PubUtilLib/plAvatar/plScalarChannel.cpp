#include "plScalarChannel.h"

// plScalarChannel //
plScalarChannel::plScalarChannel() { }
plScalarChannel::~plScalarChannel() { }

IMPLEMENT_CREATABLE(plScalarChannel, kScalarChannel, plAGChannel)


// plScalarBlend //
plScalarBlend::plScalarBlend() { }
plScalarBlend::~plScalarBlend() { }

IMPLEMENT_CREATABLE(plScalarBlend, kScalarBlend, plScalarChannel)


// plScalarConstant //
plScalarConstant::plScalarConstant() { }
plScalarConstant::~plScalarConstant() { }

IMPLEMENT_CREATABLE(plScalarConstant, kScalarConstant, plScalarChannel)

void plScalarConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fResult = S->readFloat();
}

void plScalarConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    S->writeFloat(fResult);
}

void plScalarConstant::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->startTag("Result");
    prc->writeParam("value", fResult);
    prc->endTag(true);
}


// plScalarControllerCacheChannel //
plScalarControllerCacheChannel::plScalarControllerCacheChannel() { }
plScalarControllerCacheChannel::~plScalarControllerCacheChannel() { }

IMPLEMENT_CREATABLE(plScalarControllerCacheChannel,
                    kScalarControllerCacheChannel,
                    plScalarChannel)


// plScalarControllerChannel //
plScalarControllerChannel::plScalarControllerChannel()
: fController(NULL) { }
plScalarControllerChannel::~plScalarControllerChannel() {
	if(fController != NULL)
		delete fController;
}

IMPLEMENT_CREATABLE(plScalarControllerChannel, kScalarControllerChannel,
                    plScalarChannel)

void plScalarControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fController = plController::Convert(mgr->ReadCreatable(S));
}

void plScalarControllerChannel::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    mgr->WriteCreatable(S, fController);
}

void plScalarControllerChannel::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc);
    prc->closeTag();
}


// plScalarTimeScale //
plScalarTimeScale::plScalarTimeScale() { }
plScalarTimeScale::~plScalarTimeScale() { }

IMPLEMENT_CREATABLE(plScalarTimeScale, kScalarTimeScale, plScalarChannel)


// plScalarSDLChannel //
plScalarSDLChannel::plScalarSDLChannel() { }
plScalarSDLChannel::~plScalarSDLChannel() { }

IMPLEMENT_CREATABLE(plScalarSDLChannel, kScalarSDLChannel, plScalarChannel)


// plATCChannel //
plATCChannel::plATCChannel() { }
plATCChannel::~plATCChannel() { }

IMPLEMENT_CREATABLE(plATCChannel, kATCChannel, plScalarChannel)


// plScalarChannelApplicator //
plScalarChannelApplicator::plScalarChannelApplicator() { }
plScalarChannelApplicator::~plScalarChannelApplicator() { }

IMPLEMENT_CREATABLE(plScalarChannelApplicator, kScalarChannelApplicator,
                    plAGApplicator)
