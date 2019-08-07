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

#include "plTMController.h"

plTMController::~plTMController()
{
    delete fPosController;
    delete fRotController;
    delete fScaleController;
}

void plTMController::read(hsStream* S, plResManager* mgr)
{
    int type = S->readInt();
    if (type == plPosController::kCompound)
        setPosController(new plCompoundPosController());
    else if (type == plPosController::kSimple)
        setPosController(new plSimplePosController());
    if (fPosController)
        fPosController->read(S, mgr);

    type = S->readInt();
    if (type == plRotController::kCompound)
        setRotController(new plCompoundRotController());
    else if (type == plRotController::kSimple)
        setRotController(new plSimpleRotController());
    if (fRotController)
        fRotController->read(S, mgr);

    type = S->readInt();
    if (type == plScaleController::kSimple)
        setScaleController(new plSimpleScaleController());
    if (fScaleController)
        fScaleController->read(S, mgr);
}

void plTMController::write(hsStream* S, plResManager* mgr)
{
    if (fPosController) {
        S->writeInt(fPosController->getType());
        fPosController->write(S, mgr);
    } else {
        S->writeInt(0);
    }

    if (fRotController) {
        S->writeInt(fRotController->getType());
        fRotController->write(S, mgr);
    } else {
        S->writeInt(0);
    }

    if (fScaleController) {
        S->writeInt(fScaleController->getType());
        fScaleController->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plTMController::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Position");
    if (fPosController) {
        fPosController->prcWrite(prc);
    } else {
        prc->startTag("plPosController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Rotation");
    if (fRotController) {
        fRotController->prcWrite(prc);
    } else {
        prc->startTag("plRotController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Scale");
    if (fScaleController) {
        fScaleController->prcWrite(prc);
    } else {
        prc->startTag("plScaleController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plTMController::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Position") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            if (tag->getFirstChild()->getName() == "plSimplePosController")
                setPosController(new plSimplePosController());
            else if (tag->getFirstChild()->getName() == "plCompoundPosController")
                setPosController(new plCompoundPosController());
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fPosController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Rotation") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            if (tag->getFirstChild()->getName() == "plSimpleRotController")
                setRotController(new plSimpleRotController());
            else if (tag->getFirstChild()->getName() == "plCompoundRotController")
                setRotController(new plCompoundRotController());
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fRotController->prcParse(tag->getFirstChild(), mgr);
        }
    } else if (tag->getName() == "Scale") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").to_bool()) {
            if (tag->getFirstChild()->getName() == "plSimpleScaleController")
                setScaleController(new plSimpleScaleController());
            else
                throw pfPrcTagException(__FILE__, __LINE__, tag->getFirstChild()->getName());
            fScaleController->prcParse(tag->getFirstChild(), mgr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plCompoundController* plTMController::convertToCompoundController()
{
    plCompoundController* compound = new plCompoundController();

    // Position
    if (plSimplePosController* pos = plSimplePosController::Convert(fPosController, false)) {
        plPoint3Controller* point = pos->getPosition();
        compound->setXController(point->CompactToLeafController());
    } else if (plCompoundPosController* pos = plCompoundPosController::Convert(fPosController, false)) {
        plCompoundController* subctrl = new plCompoundController();
        for (unsigned int i = 0; i < plCompoundController::kNumControllers; ++i) {
            plScalarController* convert = pos->getController(i);
            if (convert)
                subctrl->setController(i, convert->CompactToLeafController());
        }
        compound->setXController(subctrl);
    }

    // Rotation
    if (plSimpleRotController* rot = plSimpleRotController::Convert(fRotController, false)) {
        plQuatController* quat = rot->getRot();
        compound->setYController(quat->CompactToLeafController());
    } else if (plCompoundRotController* rot = plCompoundRotController::Convert(fRotController, false)) {
        plCompoundController* subctrl = new plCompoundController();
        for (unsigned int i = 0; i < plCompoundController::kNumControllers; ++i) {
            plScalarController* convert = rot->getController(i);
            if (convert)
                subctrl->setController(i, convert->CompactToLeafController());
        }
        compound->setYController(subctrl);
    }

    // Scale (always simple)
    if (plSimpleScaleController* scale = plSimpleScaleController::Convert(fScaleController)) {
        if (scale->getValue())
            compound->setZController(scale->getValue()->CompactToLeafController());
    }

    return compound;
}

void plTMController::setPosController(plPosController* controller)
{
    delete fPosController;
    fPosController = controller;
}

void plTMController::setRotController(plRotController* controller)
{
    delete fRotController;
    fRotController = controller;
}

void plTMController::setScaleController(plScaleController* controller)
{
    delete fScaleController;
    fScaleController = controller;
}
