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
plSimplePosController::~plSimplePosController()
{
    delete fPosition;
}

void plSimplePosController::read(hsStream* S, plResManager* mgr)
{
    if (S->readInt() != 0) {
        setPosition(new plPoint3Controller());
        fPosition->read(S, mgr);
    } else {
        setPosition(nullptr);
    }
}

void plSimplePosController::write(hsStream* S, plResManager* mgr)
{
    if (fPosition) {
        S->writeInt(1);
        fPosition->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plSimplePosController::IPrcWrite(pfPrcHelper* prc)
{
    if (fPosition) {
        fPosition->prcWrite(prc);
    } else {
        prc->startTag("plPoint3Controller");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimplePosController::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plPoint3Controller") {
        if (!tag->getParam("NULL", "false").to_bool()) {
            setPosition(new plPoint3Controller());
            fPosition->prcParse(tag, mgr);
        } else {
            setPosition(nullptr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plSimplePosController::setPosition(plPoint3Controller* pos)
{
    delete fPosition;
    fPosition = pos;
}


/* plCompoundPosController */
plCompoundPosController::~plCompoundPosController()
{
    delete fXController;
    delete fYController;
    delete fZController;
}

void plCompoundPosController::read(hsStream* S, plResManager* mgr)
{
    if (S->readInt() != 0) {
        setX(new plScalarController());
        fXController->read(S, mgr);
    } else {
        setX(nullptr);
    }
    if (S->readInt() != 0) {
        setY(new plScalarController());
        fYController->read(S, mgr);
    } else {
        setY(nullptr);
    }
    if (S->readInt() != 0) {
        setZ(new plScalarController());
        fZController->read(S, mgr);
    } else {
        setZ(nullptr);
    }
}

void plCompoundPosController::write(hsStream* S, plResManager* mgr)
{
    if (fXController) {
        S->writeInt(1);
        fXController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
    if (fYController) {
        S->writeInt(1);
        fYController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
    if (fZController) {
        S->writeInt(1);
        fZController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plCompoundPosController::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("X");
    if (fXController) {
        fXController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Y");
    if (fYController) {
        fYController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Z");
    if (fZController) {
        fZController->prcWrite(prc);
    } else {
        prc->startTag("plScalarController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plCompoundPosController::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "X") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            setX(new plScalarController());
            fXController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setX(nullptr);
        }
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            setY(new plScalarController());
            fYController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setY(nullptr);
        }
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            setZ(new plScalarController());
            fZController->prcParse(tag->getFirstChild(), mgr);
        } else {
            setZ(nullptr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plCompoundPosController::setController(unsigned int index, plScalarController* controller)
{
    switch (index) {
    case kX:
        delete fXController;
        fXController = controller;
        break;
    case kY:
        delete fYController;
        fYController = controller;
        break;
    case kZ:
        delete fZController;
        fZController = controller;
        break;
    }
}

void plCompoundPosController::setX(plScalarController* controller)
{
    delete fXController;
    fXController = controller;
}

void plCompoundPosController::setY(plScalarController* controller)
{
    delete fYController;
    fYController = controller;
}

void plCompoundPosController::setZ(plScalarController* controller)
{
    delete fZController;
    fZController = controller;
}
