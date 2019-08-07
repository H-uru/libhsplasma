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

#include "plVehicleModifier.h"

void plVehicleModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fRoot = mgr->readKey(S);
    for (size_t i=0; i<4; i++) {
        fWheels[i].fWheelObj = mgr->readKey(S);
        fWheels[i].fPosition.read(S);
        fWheels[i].fDirection.read(S);
        fWheels[i].fRadius = S->readFloat();
    }
}

void plVehicleModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fRoot);
    for (size_t i=0; i<4; i++) {
        mgr->writeKey(S, fWheels[i].fWheelObj);
        fWheels[i].fPosition.write(S);
        fWheels[i].fDirection.write(S);
        S->writeFloat(fWheels[i].fRadius);
    }
}

void plVehicleModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Root");
    plResManager::PrcWriteKey(prc, fRoot);
    prc->closeTag();

    prc->writeSimpleTag("Wheels");
    for (size_t i=0; i<4; i++) {
        prc->startTag("Wheel");
        prc->writeParam("Radius", fWheels[i].fRadius);
        prc->endTag();
          plResManager::PrcWriteKey(prc, fWheels[i].fWheelObj);
          prc->writeSimpleTag("Position");
          fWheels[i].fPosition.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Direction");
          fWheels[i].fDirection.prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();
}

void plVehicleModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Root") {
        fRoot = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Wheels") {
        if (tag->countChildren() != 4)
            throw pfPrcParseException(__FILE__, __LINE__, "Wheels should contain 4 children");
        const pfPrcTag* wheel = tag->getFirstChild();
        for (size_t i=0; i<4; i++) {
            if (wheel->getName() != "Wheel")
                throw pfPrcTagException(__FILE__, __LINE__, wheel->getName());
            fWheels[i].fRadius = wheel->getParam("Radius", "0").to_float();
            const pfPrcTag* wchild = wheel->getFirstChild();
            while (wchild) {
                if (wchild->getName() == "plKey")
                    fWheels[i].fWheelObj = mgr->prcParseKey(wchild);
                else if (wchild->getName() == "Position")
                    fWheels[i].fPosition.prcParse(wchild->getFirstChild());
                else if (wchild->getName() == "Direction")
                    fWheels[i].fDirection.prcParse(wchild->getFirstChild());
                else
                    throw pfPrcTagException(__FILE__, __LINE__, wchild->getName());
                wchild = wchild->getNextSibling();
            }
            wheel = wheel->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
