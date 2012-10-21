/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plPosController.h"

/* plSimplePosController */
plSimplePosController::~plSimplePosController() {
    delete fPosition;
}

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

void plSimplePosController::setPosition(plPoint3Controller* pos) {
    delete fPosition;
    fPosition = pos;
}


/* plCompoundPosController */
plCompoundPosController::~plCompoundPosController() {
    delete fXController;
    delete fYController;
    delete fZController;
}

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

void plCompoundPosController::setX(plScalarController* controller) {
    delete fXController;
    fXController = controller;
}

void plCompoundPosController::setY(plScalarController* controller) {
    delete fYController;
    fYController = controller;
}

void plCompoundPosController::setZ(plScalarController* controller) {
    delete fZController;
    fZController = controller;
}
