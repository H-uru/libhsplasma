#include "plTMController.h"
#include "CoreLib/plDebug.h"

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

void plCompoundController::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->writeComment("X, Y, Z");
    if (fXController != NULL) {
        fXController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fYController != NULL) {
        fYController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fZController != NULL) {
        fZController->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

plTMController* plCompoundController::convertToTMController() {
    return NULL;
}
