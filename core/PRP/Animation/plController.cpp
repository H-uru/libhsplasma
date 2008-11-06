#include "plTMController.h"
#include "plLeafController.h"

/* plController */
plController::plController() { }
plController::~plController() { }

IMPLEMENT_CREATABLE(plController, kController, plCreatable)

void plController::WriteController(hsStream* S, plResManager* mgr, plController* controller) {
    switch (controller->ClassIndex()) {
    case kLeafController:
        if (S->getVer() <= pvPots) {
            plLeafController* toWrite = ((plLeafController*)controller)->ExpandToKeyController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        } else {
            mgr->WriteCreatable(S, controller);
        }
        break;
    case kEaseController:
    case kMatrix33Controller:
    case kMatrix44Controller:
    case kPoint3Controller:
    case kQuatController:
    case kScalarController:
    case kScaleValueController:
        if (S->getVer() <= pvPots) {
            mgr->WriteCreatable(S, controller);
        } else {
            plLeafController* toWrite = ((plLeafController*)controller)->CompactToLeafController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        }
        break;
    default:
        mgr->WriteCreatable(S, controller);
    }
}


/* plCompoundController */
plCompoundController::plCompoundController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundController::~plCompoundController() {
    if (fXController != NULL)
        delete fXController;
    if (fYController != NULL)
        delete fYController;
    if (fZController != NULL)
        delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundController, kCompoundController, plController)

void plCompoundController::read(hsStream* S, plResManager* mgr) {
    setXController(plController::Convert(mgr->ReadCreatable(S)));
    setYController(plController::Convert(mgr->ReadCreatable(S)));
    setZController(plController::Convert(mgr->ReadCreatable(S)));
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
            setXController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            setYController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            setZController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plTMController* plCompoundController::convertToTMController() {
    return NULL;
}

plController* plCompoundController::getXController() const { return fXController; }
plController* plCompoundController::getYController() const { return fYController; }
plController* plCompoundController::getZController() const { return fZController; }

void plCompoundController::setXController(plController* controller) {
    if (fXController != NULL)
        delete fXController;
    fXController = controller;
}

void plCompoundController::setYController(plController* controller) {
    if (fYController != NULL)
        delete fYController;
    fYController = controller;
}

void plCompoundController::setZController(plController* controller) {
    if (fZController != NULL)
        delete fZController;
    fZController = controller;
}
