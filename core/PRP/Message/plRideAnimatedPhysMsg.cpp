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

#include "plRideAnimatedPhysMsg.h"

void plRideAnimatedPhysMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fEntering = S->readBool();
    fRegion = mgr->readKey(S);
}

void plRideAnimatedPhysMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeBool(fEntering);
    mgr->writeKey(S, fRegion);
}

void plRideAnimatedPhysMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("Region");
    prc->writeParam("Entering", fEntering);
    prc->endTag();
    plResManager::PrcWriteKey(prc, fRegion);
    prc->closeTag();
}

void plRideAnimatedPhysMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Region") {
        fEntering = tag->getParam("Entering", "False").to_bool();
        if (tag->hasChildren())
            fRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
