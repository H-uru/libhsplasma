#include "plRotController.h"

/* plRotController */
IMPLEMENT_CREATABLE(plRotController, kRotController, plController)


/* plSimpleRotController */
plSimpleRotController::plSimpleRotController() : fRot(NULL) { }

plSimpleRotController::~plSimpleRotController() {
    if (fRot != NULL)
        delete fRot;
}

IMPLEMENT_CREATABLE(plSimpleRotController, kSimpleRotController, plRotController)

void plSimpleRotController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        setRot(new plQuatController());
        fRot->read(S, mgr);
    } else {
        setRot(NULL);
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
            setRot(new plQuatController());
            fRot->prcParse(tag, mgr);
        } else {
            setRot(NULL);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimpleRotController::getType() const { return kSimple; }
plQuatController* plSimpleRotController::getRot() const { return fRot; }

void plSimpleRotController::setRot(plQuatController* rot) {
    if (fRot != NULL)
        delete fRot;
    fRot = rot;
}


/* plCompoundRotController */
plCompoundRotController::plCompoundRotController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundRotController::~plCompoundRotController() {
    if (fXController != NULL)
        delete fXController;
    if (fYController != NULL)
        delete fYController;
    if (fZController != NULL)
        delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundRotController, kCompoundRotController, plRotController)

void plCompoundRotController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        setX(new plScalarController());
        fXController->read(S, mgr);
    } else {
        setX(NULL);
    }
    if (S->readInt() != 0) {
        setY(new plScalarController());
        fYController->read(S, mgr);
    } else {
        setY(NULL);
    }
    if (S->readInt() != 0) {
        setZ(new plScalarController());
        fZController->read(S, mgr);
    } else {
        setZ(NULL);
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
            setX(new plScalarController());
            fXController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setX(NULL);
        }
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            setY(new plScalarController());
            fYController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setY(NULL);
        }
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool()) {
            setZ(new plScalarController());
            fZController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setZ(NULL);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plCompoundRotController::getType() const { return kCompound; }

plScalarController* plCompoundRotController::getX() const { return fXController; }
plScalarController* plCompoundRotController::getY() const { return fYController; }
plScalarController* plCompoundRotController::getZ() const { return fZController; }

void plCompoundRotController::setX(plScalarController* controller) {
    if (fXController != NULL)
        delete fXController;
    fXController = controller;
}

void plCompoundRotController::setY(plScalarController* controller) {
    if (fYController != NULL)
        delete fYController;
    fYController = controller;
}

void plCompoundRotController::setZ(plScalarController* controller) {
    if (fZController != NULL)
        delete fZController;
    fZController = controller;
}
