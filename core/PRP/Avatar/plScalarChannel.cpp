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

#include "plScalarChannel.h"

/* plScalarConstant */
void plScalarConstant::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);
    fResult = S->readFloat();
}

void plScalarConstant::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);
    S->writeFloat(fResult);
}

void plScalarConstant::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->startTag("Result");
    prc->writeParam("value", fResult);
    prc->endTag(true);
}

void plScalarConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Result") {
        fResult = tag->getParam("value", "0").to_float();
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plScalarControllerChannel */
plScalarControllerChannel::~plScalarControllerChannel()
{
    delete fController;
}

void plScalarControllerChannel::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);
    setController(mgr->ReadCreatableC<plController>(S));
}

void plScalarControllerChannel::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);
    plController::WriteController(S, mgr, fController);
}

void plScalarControllerChannel::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    if (fController)
        fController->prcWrite(prc);
    prc->closeTag();
}

void plScalarControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            setController(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

void plScalarControllerChannel::setController(plController* controller)
{
    delete fController;
    fController = controller;
}
