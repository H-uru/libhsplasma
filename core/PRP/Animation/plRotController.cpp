#include "plRotController.h"

/* plRotController */
IMPLEMENT_CREATABLE(plRotController, kRotController, plController)


/* plSimpleRotController */
plSimpleRotController::plSimpleRotController() : fRot(NULL) { }

plSimpleRotController::~plSimpleRotController() {
    if (fRot) delete fRot;
}

IMPLEMENT_CREATABLE(plSimpleRotController, kSimpleRotController, plRotController)

void plSimpleRotController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        if (fRot) delete fRot;
        fRot = new plQuatController();
        fRot->read(S, mgr);
    }
}

void plSimpleRotController::write(hsStream* S, plResManager* mgr) {
    if (fRot != NULL) {
        S->writeInt(1);
        fRot->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plSimpleRotController::IPrcWrite(pfPrcHelper* prc) {
    if (fRot != NULL) {
        fRot->prcWrite(prc);
    } else {
        prc->startTag("plQuatController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimpleRotController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plQuatController") {
        if (!tag->getParam("NULL", "false").toBool()) {
            fRot = new plQuatController();
            fRot->prcParse(tag, mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimpleRotController::getType() const { return kSimple; }


/* plCompoundRotController */
plCompoundRotController::plCompoundRotController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundRotController::~plCompoundRotController() {
    if (fXController) delete fXController;
    if (fYController) delete fYController;
    if (fZController) delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundRotController, kCompoundRotController, plRotController)

void plCompoundRotController::read(hsStream* S, plResManager* mgr) {
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

void plCompoundRotController::write(hsStream* S, plResManager* mgr) {
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

void plCompoundRotController::IPrcWrite(pfPrcHelper* prc) {
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

void plCompoundRotController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "X") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fXController = new plScalarController();
            fXController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fYController = new plScalarController();
            fYController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            fZController = new plScalarController();
            fZController->prcParse(tag->getFirstChild(), mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plCompoundRotController::getType() const { return kCompound; }
