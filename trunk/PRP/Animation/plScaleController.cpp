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

void plSimpleScaleController::IPrcWrite(pfPrcHelper* prc) {
    if (fValue != NULL) {
        fValue->prcWrite(prc);
    } else {
        prc->startTag("plScaleValueController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimpleScaleController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plScaleValueController") {
        if (!tag->getParam("NULL", "false").toBool()) {
            fValue = new plScaleValueController();
            fValue->prcParse(tag, mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimpleScaleController::getType() const { return kSimple; }
