#include "plTMController.h"

plTMController::plTMController()
              : fPosController(NULL), fRotController(NULL),
                fScaleController(NULL) { }

plTMController::~plTMController() {
    delete fPosController;
    delete fRotController;
    delete fScaleController;
}

void plTMController::read(hsStream* S, plResManager* mgr) {
    int type = S->readInt();
    if (type == plPosController::kCompound)
        setPosController(new plCompoundPosController());
    else if (type == plPosController::kSimple)
        setPosController(new plSimplePosController());
    if (fPosController != NULL)
        fPosController->read(S, mgr);

    type = S->readInt();
    if (type == plRotController::kCompound)
        setRotController(new plCompoundRotController());
    else if (type == plRotController::kSimple)
        setRotController(new plSimpleRotController());
    if (fRotController != NULL)
        fRotController->read(S, mgr);

    type = S->readInt();
    if (type == plScaleController::kSimple)
        setScaleController(new plSimpleScaleController());
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
                setPosController(new plSimplePosController());
            else if (tag->getFirstChild()->getName() == "plCompoundPosController")
                setPosController(new plCompoundPosController());
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fPosController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Rotation") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            if (tag->getFirstChild()->getName() == "plSimpleRotController")
                setRotController(new plSimpleRotController());
            else if (tag->getFirstChild()->getName() == "plCompoundRotController")
                setRotController(new plCompoundRotController());
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fRotController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Scale") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            if (tag->getFirstChild()->getName() == "plSimpleScaleController")
                setScaleController(new plSimpleScaleController());
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

void plTMController::setPosController(plPosController* controller) {
    delete fPosController;
    fPosController = controller;
}

void plTMController::setRotController(plRotController* controller) {
    delete fRotController;
    fRotController = controller;
}

void plTMController::setScaleController(plScaleController* controller) {
    delete fScaleController;
    fScaleController = controller;
}
