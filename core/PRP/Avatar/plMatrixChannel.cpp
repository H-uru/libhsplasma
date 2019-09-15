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

#include "plMatrixChannel.h"

/* plMatrixConstant */
void plMatrixConstant::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);

    if (!S->getVer().isUruSP())
        fAP.read(S);
    else
        fAP.reset();
}

void plMatrixConstant::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);

    if (!S->getVer().isUruSP())
        fAP.write(S);
}

void plMatrixConstant::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}

void plMatrixConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AffineParts") {
        if (tag->hasChildren())
            fAP.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plMatrixControllerChannel */
plMatrixControllerChannel::~plMatrixControllerChannel()
{
    delete fController;
}

void plMatrixControllerChannel::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);
    fController = mgr->ReadCreatableC<plController>(S);
    fAP.read(S);
}

void plMatrixControllerChannel::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);
    plController::WriteController(S, mgr, fController);
    fAP.write(S);
}

void plMatrixControllerChannel::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    if (fController)
        fController->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("AffineParts");
    fAP.prcWrite(prc);
    prc->closeTag();
}

void plMatrixControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            fController = mgr->prcParseCreatableC<plController>(tag->getFirstChild());
    } else if (tag->getName() == "AffineParts") {
        if (tag->hasChildren())
            fAP.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

void plMatrixControllerChannel::setController(plController* controller)
{
    delete fController;
    fController = controller;
}
