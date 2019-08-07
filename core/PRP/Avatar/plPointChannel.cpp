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

#include "plPointChannel.h"

/* plPointConstant */
void plPointConstant::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);
    fResult.read(S);
}

void plPointConstant::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);
    fResult.write(S);
}

void plPointConstant::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Result");
    fResult.prcWrite(prc);
    prc->closeTag();
}

void plPointConstant::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Result") {
        if (tag->hasChildren())
            fResult.prcParse(tag->getFirstChild());
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}


/* plPointControllerChannel */
plPointControllerChannel::~plPointControllerChannel()
{
    delete fController;
}

void plPointControllerChannel::read(hsStream* S, plResManager* mgr)
{
    plAGChannel::read(S, mgr);
    setController(mgr->ReadCreatableC<plController>(S));
}

void plPointControllerChannel::write(hsStream* S, plResManager* mgr)
{
    plAGChannel::write(S, mgr);
    plController::WriteController(S, mgr, fController);
}

void plPointControllerChannel::IPrcWrite(pfPrcHelper* prc)
{
    plAGChannel::IPrcWrite(prc);

    prc->writeSimpleTag("Controller");
    if (fController)
        fController->prcWrite(prc);
    prc->closeTag();
}

void plPointControllerChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Controller") {
        if (tag->hasChildren())
            setController(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else {
        plAGChannel::IPrcParse(tag, mgr);
    }
}

void plPointControllerChannel::setController(plController* controller)
{
    delete fController;
    fController = controller;
}
