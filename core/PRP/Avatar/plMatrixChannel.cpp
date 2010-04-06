#include "plMatrixChannel.h"

/* plMatrixConstant */
void plMatrixConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);

    if (S->getVer() >= pvLive)
        fAP.read(S);
    else
        fAP.reset();
}

void plMatrixConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);

    if (S->getVer() >= pvLive)
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


/* plMatrixControllerChannel */
plMatrixControllerChannel::plMatrixControllerChannel() : fController(NULL) { }

plMatrixControllerChannel::~plMatrixControllerChannel() {
    delete fController;
}

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

void plMatrixControllerChannel::setController(plController* controller) {
    delete fController;
    fController = controller;
}
