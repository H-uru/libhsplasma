#include "plScaleController.h"

/* plScaleController */
IMPLEMENT_CREATABLE(plScaleController, kScaleController, plController)


/* plSimpleScaleController */
plSimpleScaleController::plSimpleScaleController() : fValue(NULL) { }

plSimpleScaleController::~plSimpleScaleController() {
    if (fValue) delete fValue;
}

IMPLEMENT_CREATABLE(plSimpleScaleController, kSimpleScaleController, plScaleController)

void plSimpleScaleController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        if (fValue) delete fValue;
        fValue = new plScaleValueController();
        fValue->read(S, mgr);
    }
}

void plSimpleScaleController::write(hsStream* S, plResManager* mgr) {
    if (fValue != NULL) {
        S->writeInt(1);
        fValue->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plSimpleScaleController::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    if (fValue != NULL) {
        fValue->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("plScaleValueController");
        prc->writeParam("present", false);
        prc->endTag(true);
    }
}

int plSimpleScaleController::getType() const { return kSimple; }
