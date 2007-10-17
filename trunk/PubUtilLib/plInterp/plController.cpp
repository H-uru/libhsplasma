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
    printf("Reading X controller\n");
    fXController = plController::Convert(mgr->ReadCreatable(S));
    printf("Reading Y controller\n");
    fYController = plController::Convert(mgr->ReadCreatable(S));
    printf("Reading Z controller\n");
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
    fXController->prcWrite(prc); prc->closeTag();
    fYController->prcWrite(prc); prc->closeTag();
    fZController->prcWrite(prc); prc->closeTag();
}

plTMController* plCompoundController::convertToTMController() {
    return NULL;
}
