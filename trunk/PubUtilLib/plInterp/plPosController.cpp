#include "plPosController.h"

/* plPosController */
IMPLEMENT_CREATABLE(plPosController, kPosController, plController)


/* plSimplePosController */
plSimplePosController::plSimplePosController()
                     : fPosition(NULL) { }

plSimplePosController::~plSimplePosController() {
    if (fPosition) delete fPosition;
}

IMPLEMENT_CREATABLE(plSimplePosController, kSimplePosController, plPosController)

void plSimplePosController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        if (fPosition) delete fPosition;
        fPosition = new plPoint3Controller();
        fPosition->read(S, mgr);
    }
}

void plSimplePosController::write(hsStream* S, plResManager* mgr) {
    if (fPosition != NULL) {
        S->writeInt(1);
        fPosition->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plSimplePosController::IPrcWrite(pfPrcHelper* prc) {
    if (fPosition != NULL) {
        fPosition->prcWrite(prc);
    } else {
        prc->startTag("plPoint3Controller");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimplePosController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plPoint3Controller") {
        if (!tag->getParam("NULL", "false").toBool()) {
            fPosition = new plPoint3Controller();
            fPosition->prcParse(tag, mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimplePosController::getType() const { return kSimple; }


/* plCompoundPosController */
plCompoundPosController::plCompoundPosController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundPosController::~plCompoundPosController() {
    if (fXController) delete fXController;
    if (fYController) delete fYController;
    if (fZController) delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundPosController, kCompoundPosController, plPosController)

void plCompoundPosController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        if (fXController != NULL) delete fXController;
        fXController = new plScalarController();
        fXController->read(S, mgr);
    }
    if (S->readInt() != 0) {
        if (fYController != NULL) delete fYController;
        fYController = new plScalarController();
        fYController->read(S, mgr);
    }
    if (S->readInt() != 0) {
        if (fZController != NULL) delete fZController;
        fZController = new plScalarController();
        fZController->read(S, mgr);
    }
}

void plCompoundPosController::write(hsStream* S, plResManager* mgr) {
    if (fXController != NULL) {
        S->writeInt(1);
        fXController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
    if (fYController != NULL) {
        S->writeInt(1);
        fYController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
    if (fZController != NULL) {
        S->writeInt(1);
        fZController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plCompoundPosController::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("X");
    if (fXController != NULL) {
        fXController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Y");
    if (fYController != NULL) {
        fYController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Z");
    if (fZController != NULL) {
        fZController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plCompoundPosController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "X") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fXController = new plScalarController();
            fXController->prcParse(tag, mgr);
        }
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fYController = new plScalarController();
            fYController->prcParse(tag, mgr);
        }
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fZController = new plScalarController();
            fZController->prcParse(tag, mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plCompoundPosController::getType() const { return kCompound; }
