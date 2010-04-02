#include "plScalarChannel.h"

/* plScalarConstant */
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

void plScalarConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Result") {
        fResult = tag->getParam("value", "0").toFloat();
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plScalarControllerChannel */
plScalarControllerChannel::plScalarControllerChannel() : fController(NULL) { }

plScalarControllerChannel::~plScalarControllerChannel() {
    if (fController != NULL)
        delete fController;
}

void plScalarControllerChannel::read(hsStream* S, plResManager* mgr) {
    plAGChannel::read(S, mgr);
    setController(plController::Convert(mgr->ReadCreatable(S)));
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

void plScalarControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            setController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

void plScalarControllerChannel::setController(plController* controller) {
    if (fController != NULL)
        delete fController;
    fController = controller;
}
