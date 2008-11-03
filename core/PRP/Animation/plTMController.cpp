#include "plTMController.h"

plTMController::plTMController()
              : fPosController(NULL), fRotController(NULL),
                fScaleController(NULL) { }

plTMController::~plTMController() {
    if (fPosController) delete fPosController;
    if (fRotController) delete fRotController;
    if (fScaleController) delete fScaleController;
}

IMPLEMENT_CREATABLE(plTMController, kTMController, plController)

void plTMController::read(hsStream* S, plResManager* mgr) {
    int type = S->readInt();
    if (type == plPosController::kCompound) {
        if (fPosController != NULL) delete fPosController;
        fPosController = new plCompoundPosController();
    } else if (type == plPosController::kSimple) {
        if (fPosController != NULL) delete fPosController;
        fPosController = new plSimplePosController();
    }
    if (fPosController != NULL)
        fPosController->read(S, mgr);

    type = S->readInt();
    if (type == plRotController::kCompound) {
        if (fRotController != NULL) delete fRotController;
        fRotController = new plCompoundRotController();
    } else if (type == plRotController::kSimple) {
        if (fRotController != NULL) delete fRotController;
        fRotController = new plSimpleRotController();
    }
    if (fRotController != NULL)
        fRotController->read(S, mgr);

    type = S->readInt();
    if (type == plScaleController::kSimple) {
        if (fScaleController != NULL) delete fScaleController;
        fScaleController = new plSimpleScaleController();
    }
    if (fScaleController != NULL)
        fScaleController->read(S, mgr);
}

void plTMController::write(hsStream* S, plResManager* mgr) {
    if (fPosController != NULL) {
        S->writeInt(fPosController->getType());
        fPosController->write(S, mgr);
    } else {
        S->writeInt(0);
    }

    if (fRotController != NULL) {
        S->writeInt(fRotController->getType());
        fRotController->write(S, mgr);
    } else {
        S->writeInt(0);
    }

    if (fScaleController != NULL) {
        S->writeInt(fScaleController->getType());
        fScaleController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plTMController::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Position");
    if (fPosController != NULL) {
        fPosController->prcWrite(prc);
    } else {
        prc->startTag("plPosController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Rotation");
    if (fRotController != NULL) {
        fRotController->prcWrite(prc);
    } else {
        prc->startTag("plRotController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Scale");
    if (fScaleController != NULL) {
        fScaleController->prcWrite(prc);
    } else {
        prc->startTag("plScaleController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plTMController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Position") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            if (tag->getFirstChild()->getName() == "plSimplePosController")
                fPosController = new plSimplePosController();
            else if (tag->getFirstChild()->getName() == "plCompoundPosController")
                fPosController = new plCompoundPosController();
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fPosController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Rotation") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            if (tag->getFirstChild()->getName() == "plSimpleRotController")
                fRotController = new plSimpleRotController();
            else if (tag->getFirstChild()->getName() == "plCompoundRotController")
                fRotController = new plCompoundRotController();
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fRotController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Scale") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            if (tag->getFirstChild()->getName() == "plSimpleScaleController")
                fScaleController = new plSimpleScaleController();
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fScaleController->prcParse(tag->getFirstChild(), mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plCompoundController* plTMController::convertToCompoundController() {
    return NULL;
}

plPosController* plTMController::getPosController() const { return fPosController; }
plRotController* plTMController::getRotController() const { return fRotController; }
plScaleController* plTMController::getScaleController() const { return fScaleController; }

void plTMController::setPosController(plPosController* controller) {
    if (fPosController != NULL)
        delete fPosController;
    fPosController = controller;
}

void plTMController::setRotController(plRotController* controller) {
    if (fRotController != NULL)
        delete fRotController;
    fRotController = controller;
}

void plTMController::setScaleController(plScaleController* controller) {
    if (fScaleController != NULL)
        delete fScaleController;
    fScaleController = controller;
}
