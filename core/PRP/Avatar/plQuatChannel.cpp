#include "plQuatChannel.h"

/* plQuatChannel */
plQuatChannel::plQuatChannel() { }
plQuatChannel::~plQuatChannel() { }

IMPLEMENT_CREATABLE(plQuatChannel, kQuatChannel, plAGChannel)

hsQuat plQuatChannel::getResult() const { return fResult; }
void plQuatChannel::setResult(const hsQuat& result) { fResult = result; }


/* plQuatBlend */
plQuatBlend::plQuatBlend() { }
plQuatBlend::~plQuatBlend() { }

IMPLEMENT_CREATABLE(plQuatBlend, kQuatBlend, plQuatChannel)


/* plQuatConstant */
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

void plQuatConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Result") {
        if (tag->hasChildren())
            fResult.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plQuatTimeScale */
plQuatTimeScale::plQuatTimeScale() { }
plQuatTimeScale::~plQuatTimeScale() { }

IMPLEMENT_CREATABLE(plQuatTimeScale, kQuatTimeScale, plQuatChannel)


/* plQuatChannelApplicator */
plQuatChannelApplicator::plQuatChannelApplicator() { }
plQuatChannelApplicator::~plQuatChannelApplicator() { }

IMPLEMENT_CREATABLE(plQuatChannelApplicator, kQuatChannelApplicator,
                    plAGApplicator)
