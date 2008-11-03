#include "plPosController.h"

/* plPosController */
IMPLEMENT_CREATABLE(plPosController, kPosController, plController)


/* plSimplePosController */
plSimplePosController::plSimplePosController()
                     : fPosition(NULL) { }

plSimplePosController::~plSimplePosController() {
    if (fPosition != NULL)
        delete fPosition;
}

IMPLEMENT_CREATABLE(plSimplePosController, kSimplePosController, plPosController)

void plSimplePosController::read(hsStream* S, plResManager* mgr) {
    if (S->readInt() != 0) {
        setPosition(new plPoint3Controller());
        fPosition->read(S, mgr);
    } else {
        setPosition(NULL);
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
            setPosition(new plPoint3Controller());
            fPosition->prcParse(tag, mgr);
        } else {
            setPosition(NULL);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

int plSimplePosController::getType() const { return kSimple; }
plPoint3Controller* plSimplePosController::getPosition() const { return fPosition; }

void plSimplePosController::setPosition(plPoint3Controller* pos) {
    if (fPosition != NULL)
        delete fPosition;
    fPosition = pos;
}


/* plCompoundPosController */
plCompoundPosController::plCompoundPosController()
    : fXController(NULL), fYController(NULL), fZController(NULL) { }

plCompoundPosController::~plCompoundPosController() {
    if (fXController != NULL)
        delete fXController;
    if (fYController != NULL)
        delete fYController;
    if (fZController != NULL)
        delete fZController;
}

IMPLEMENT_CREATABLE(plCompoundPosController, kCompoundPosController, plPosController)

void plCompoundPosController::read(hsStream* S, plResManager* mgr) {
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

int plCompoundPosController::getType() const { return kCompound; }

plScalarController* plCompoundPosController::getX() const { return fXController; }
plScalarController* plCompoundPosController::getY() const { return fYController; }
plScalarController* plCompoundPosController::getZ() const { return fZController; }

void plCompoundPosController::setX(plScalarController* controller) {
    if (fXController != NULL)
        delete fXController;
    fXController = controller;
}

void plCompoundPosController::setY(plScalarController* controller) {
    if (fYController != NULL)
        delete fYController;
    fYController = controller;
}

void plCompoundPosController::setZ(plScalarController* controller) {
    if (fZController != NULL)
        delete fZController;
    fZController = controller;
}
