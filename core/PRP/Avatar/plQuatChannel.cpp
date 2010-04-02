#include "plQuatChannel.h"

/* plQuatConstant */
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
