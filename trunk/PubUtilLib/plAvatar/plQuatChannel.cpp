#include "plQuatChannel.h"

// plQuatChannel //
plQuatChannel::plQuatChannel() { }
plQuatChannel::~plQuatChannel() { }

IMPLEMENT_CREATABLE(plQuatChannel, kQuatChannel, plAGChannel)


// plQuatBlend //
plQuatBlend::plQuatBlend() { }
plQuatBlend::~plQuatBlend() { }

IMPLEMENT_CREATABLE(plQuatBlend, kQuatBlend, plQuatChannel)


// plQuatConstant //
plQuatConstant::plQuatConstant() { }
plQuatConstant::~plQuatConstant() { }

IMPLEMENT_CREATABLE(plQuatConstant, kQuatConstant, plQuatChannel)

void plQuatConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fResult.read(S);
}

void plQuatConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    fResult.write(S);
}

void plQuatConstant::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Result");
    fResult.prcWrite(prc);
    prc->closeTag();
}


// plQuatTimeScale //
plQuatTimeScale::plQuatTimeScale() { }
plQuatTimeScale::~plQuatTimeScale() { }

IMPLEMENT_CREATABLE(plQuatTimeScale, kQuatTimeScale, plQuatChannel)


// plQuatChannelApplicator //
plQuatChannelApplicator::plQuatChannelApplicator() { }
plQuatChannelApplicator::~plQuatChannelApplicator() { }

IMPLEMENT_CREATABLE(plQuatChannelApplicator, kQuatChannelApplicator,
                    plAGApplicator)
