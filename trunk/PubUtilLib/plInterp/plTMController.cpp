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

void plTMController::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    if (fPosController != NULL) {
        fPosController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plPosController");
        prc->writeParam("present", false);
        prc->endTag(true);
    }

    if (fRotController != NULL) {
        fRotController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plRotController");
        prc->writeParam("present", false);
        prc->endTag(true);
    }

    if (fScaleController != NULL) {
        fScaleController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plScaleController");
        prc->writeParam("present", false);
        prc->endTag(true);
    }
}

plCompoundController* plTMController::convertToCompoundController() {
    return NULL;
}
