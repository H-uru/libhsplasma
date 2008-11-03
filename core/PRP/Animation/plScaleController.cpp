#include "plScaleController.h"

/* plScaleController */
IMPLEMENT_CREATABLE(plScaleController, kScaleController, plController)


/* plSimpleScaleController */
plSimpleScaleController::plSimpleScaleController() : fValue(NULL) { }

plSimpleScaleController::~plSimpleScaleController() {
    if (fValue != NULL)
        delete fValue;
}

IMPLEMENT_CREATABLE(plSimpleScaleController, kSimpleScaleController, plScaleController)

void plSimpleScaleController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        setValue(new plScaleValueController());
        fValue->read(S, mgr);
    } else {
        setValue(NULL);
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
            setValue(new plScaleValueController());
            fValue->prcParse(tag, mgr);
        } else {
            setValue(NULL);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimpleScaleController::getType() const { return kSimple; }
plScaleValueController* plSimpleScaleController::getValue() const { return fValue; }

void plSimpleScaleController::setValue(plScaleValueController* value) {
    if (fValue != NULL)
        delete fValue;
    fValue = value;
}
