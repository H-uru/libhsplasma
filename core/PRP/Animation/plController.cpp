#include "plTMController.h"

/* plController */
plController::plController() { }
plController::~plController() { }

IMPLEMENT_CREATABLE(plController, kController, plCreatable)


/* plCompoundController */
plCompoundController::plCompoundController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundController::~plCompoundController() {
    if (fXController) delete fXController;
    if (fYController) delete fYController;
    if (fZController) delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundController, kCompoundController, plController)

void plCompoundController::read(hsStream* S, plResManager* mgr) {
    fXController = plController::Convert(mgr->ReadCreatable(S));
    fYController = plController::Convert(mgr->ReadCreatable(S));
    fZController = plController::Convert(mgr->ReadCreatable(S));
}

void plCompoundController::write(hsStream* S, plResManager* mgr) {
    mgr->WriteCreatable(S, fXController);
    mgr->WriteCreatable(S, fYController);
    mgr->WriteCreatable(S, fZController);
}

void plCompoundController::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("X");
    if (fXController != NULL) {
        fXController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Y");
    if (fYController != NULL) {
        fYController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Z");
    if (fZController != NULL) {
        fZController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plCompoundController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "X") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            fXController = plController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            fYController = plController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            fZController = plController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plTMController* plCompoundController::convertToTMController() {
    return NULL;
}
