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
#include "plLeafController.h"

/* plController */
void plController::WriteController(hsStream* S, plResManager* mgr, plController* controller) {
    if (controller == NULL) {
        mgr->WriteCreatable(S, NULL);
        return;
    }

    switch (controller->ClassIndex()) {
    case kLeafController:
        if (S->getVer().isUruSP()) {
            plLeafController* toWrite = ((plLeafController*)controller)->ExpandToKeyController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        } else {
            mgr->WriteCreatable(S, controller);
        }
        break;
    case kEaseController:
    case kMatrix33Controller:
    case kMatrix44Controller:
    case kPoint3Controller:
    case kQuatController:
    case kScalarController:
    case kScaleValueController:
        if (S->getVer().isUruSP() || S->getVer().isUniversal()) {
            mgr->WriteCreatable(S, controller);
        } else {
            plLeafController* toWrite = ((plLeafController*)controller)->CompactToLeafController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        }
        break;
    case kCompoundController:
        if (S->getVer().isUruSP()) {
            plTMController* toWrite = ((plCompoundController*)controller)->convertToTMController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        } else {
            mgr->WriteCreatable(S, controller);
        }
        break;
    case kTMController:
        if (S->getVer().isUruSP() || S->getVer().isUniversal()) {
            mgr->WriteCreatable(S, controller);
        } else {
            plCompoundController* toWrite = ((plTMController*)controller)->convertToCompoundController();
            mgr->WriteCreatable(S, toWrite);
            delete toWrite;
        }
        break;
    default:
        mgr->WriteCreatable(S, controller);
    }
}


/* plCompoundController */
plCompoundController::~plCompoundController() {
    delete fXController;
    delete fYController;
    delete fZController;
}

void plCompoundController::read(hsStream* S, plResManager* mgr) {
    setXController(plController::Convert(mgr->ReadCreatable(S)));
    setYController(plController::Convert(mgr->ReadCreatable(S)));
    setZController(plController::Convert(mgr->ReadCreatable(S)));
}

void plCompoundController::write(hsStream* S, plResManager* mgr) {
    mgr->WriteCreatable(S, fXController);
    mgr->WriteCreatable(S, fYController);
    mgr->WriteCreatable(S, fZController);
}

void plCompoundController::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("X");
    if (fXController != NULL) {
        fXController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Y");
    if (fYController != NULL) {
        fYController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
    prc->writeSimpleTag("Z");
    if (fZController != NULL) {
        fZController->prcWrite(prc);
    } else {
        prc->startTag("plController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plCompoundController::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "X") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            setXController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Y") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            setYController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Z") {
        if (tag->hasChildren() && !tag->getFirstChild()->getParam("NULL", "false").toBool())
            setZController(plController::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

plTMController* plCompoundController::convertToTMController() {
    plTMController* tm = new plTMController();

    // Position
    if (plLeafController* leaf = plLeafController::Convert(fXController, false)) {
        plLeafController* expanded = leaf->ExpandToKeyController();
        plSimplePosController* pos = new plSimplePosController();
        pos->setPosition(plPoint3Controller::Convert(expanded));
        tm->setPosController(pos);
    } else if (plCompoundController* subctrl = plCompoundController::Convert(fXController, false)) {
        plCompoundPosController* tmPos = new plCompoundPosController();
        for (unsigned int i = 0; i < kNumControllers; ++i) {
            plLeafController* leaf = plLeafController::Convert(subctrl->getController(i));
            if (leaf) {
                plScalarController* tmPosScalar = plScalarController::Convert(leaf->ExpandToKeyController());
                tmPos->setController(i, tmPosScalar);
            }
        }
        tm->setPosController(tmPos);
    }

    // Rotation
    if (plLeafController* leaf = plLeafController::Convert(fYController, false)) {
        plLeafController* expanded = leaf->ExpandToKeyController();
        plSimpleRotController* rot = new plSimpleRotController();
        rot->setRot(plQuatController::Convert(expanded));
        tm->setRotController(rot);
    } else if (plCompoundController* subctrl =  plCompoundController::Convert(fYController, false)) {
        plCompoundRotController* tmRot = new plCompoundRotController();
        for (unsigned int i = 0; i < kNumControllers; ++i) {
            plLeafController* leaf = plLeafController::Convert(subctrl->getController(i));
            if (leaf) {
                plScalarController* tmRotScalar = plScalarController::Convert(leaf->ExpandToKeyController());
                tmRot->setController(i, tmRotScalar);
            }
        }
        tm->setRotController(tmRot);
    }

    // Scale (only simple)
    if (plLeafController* scale = plLeafController::Convert(fZController)) {
        plScaleValueController* expanded = plScaleValueController::Convert(scale->ExpandToKeyController());
        plSimpleScaleController* tmScale = new plSimpleScaleController();
        tmScale->setValue(expanded);
    }

    return tm;
}

void plCompoundController::setXController(plController* controller) {
    delete fXController;
    fXController = controller;
}

void plCompoundController::setYController(plController* controller) {
    delete fYController;
    fYController = controller;
}

void plCompoundController::setZController(plController* controller) {
    delete fZController;
    fZController = controller;
}
