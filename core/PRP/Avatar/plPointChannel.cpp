#include "plPointChannel.h"

/* plPointConstant */
void plPointConstant::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    fResult.read(S);
}

void plPointConstant::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    fResult.write(S);
}

void plPointConstant::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Result");
    fResult.prcWrite(prc);
    prc->closeTag();
}

void plPointConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Result") {
        if (tag->hasChildren())
            fResult.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plPointControllerChannel */
plPointControllerChannel::plPointControllerChannel() : fController(NULL) { }

plPointControllerChannel::~plPointControllerChannel() {
    delete fController;
}

void plPointControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    setController(plController::Convert(mgr->ReadCreatable(S)));
}

void plPointControllerChannel::write(hsStream* S, plResManager* mgr) {
    plAGChannel::write(S, mgr);
    mgr->WriteCreatable(S, fController);
}

void plPointControllerChannel::IPrcWrite(pfPrcHelper* prc) {
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    fController->prcWrite(prc);
    prc->closeTag();
}

void plPointControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            setController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

void plPointControllerChannel::setController(plController* controller) {
    delete fController;
    fController = controller;
}
